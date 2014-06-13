/**
 * @file    main_trigger_callback.cpp
 * @brief   Main logic is here!
 *
 * See http://rusefi.com/docs/html/
 *
 * @date Feb 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 *
 * This file is part of rusEfi - see http://rusefi.com
 *
 * rusEfi is free software; you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * rusEfi is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "main.h"

#if !EFI_PROD_CODE && !EFI_SIMULATOR

#define chThdSelf() 0
#define getRemainingStack(x) (999999)

#endif

#if EFI_ENGINE_CONTROL

#include "main_trigger_callback.h"
#include "ec2.h"

#include "engine_math.h"
#include "trigger_central.h"
#include "rpm_calculator.h"
#include "signal_executor.h"
#include "engine_configuration.h"
#include "interpolation.h"
#include "advance_map.h"
#include "allsensors.h"
#include "cyclic_buffer.h"
#include "histogram.h"
#include "fuel_math.h"
#include "histogram.h"
#if EFI_PROD_CODE
#include "rfiutil.h"
#endif /* EFI_HISTOGRAMS */
#include "LocalVersionHolder.h"
#include "event_queue.h"
#include "engine.h"

static LocalVersionHolder localVersion;

extern Engine engine;

static MainTriggerCallback mainTriggerCallbackInstance;

/**
 * In order to archive higher event precision, we are using a hybrid approach
 * where we are scheduling events based on the closest trigger event with a time offset.
 *
 * This queue is using global trigger event index as 'time'
 */
static EventQueue triggerEventsQueue;

static cyclic_buffer ignitionErrorDetection;

static Logging logger;

static void handleFuelInjectionEvent(MainTriggerCallback *mainTriggerCallback, ActuatorEvent *event, int rpm) {
	float fuelMs = getFuelMs(rpm) * mainTriggerCallback->engineConfiguration->globalFuelCorrection;
	if (fuelMs < 0) {
#if EFI_PROD_CODE
		scheduleMsg(&logger, "ERROR: negative injectionPeriod %f", fuelMs);
#endif
		return;
	}

	float delay = getOneDegreeTimeMs(rpm) * event->position.angleOffset;

//	if (isCranking())
//		scheduleMsg(&logger, "crankingFuel=%f for CLT=%fC", fuelMs, getCoolantTemperature());

	scheduleOutput(event->actuator, delay, fuelMs);
}

static void handleFuel(MainTriggerCallback *mainTriggerCallback, int eventIndex, int rpm) {
	if (!isInjectionEnabled(mainTriggerCallback->engineConfiguration2))
		return;
	efiAssertVoid(getRemainingStack(chThdSelf()) > 16, "stack#3");
	efiAssertVoid(eventIndex < mainTriggerCallback->engineConfiguration2->triggerShape.shaftPositionEventCount,
			"event index");

	/**
	 * Ignition events are defined by addFuelEvents() according to selected
	 * fueling strategy
	 */
	ActuatorEventList *source =
			isCranking() ?
					&mainTriggerCallback->engineConfiguration2->engineEventConfiguration.crankingInjectionEvents :
					&mainTriggerCallback->engineConfiguration2->engineEventConfiguration.injectionEvents;

	for (int i = 0; i < source->size; i++) {
		ActuatorEvent *event = &source->events[i];
		if (event->position.eventIndex != eventIndex)
			continue;
		handleFuelInjectionEvent(mainTriggerCallback, event, rpm);
	}
}

static void handleSparkEvent(MainTriggerCallback *mainTriggerCallback, int eventIndex, IgnitionEvent *iEvent, int rpm) {
	engine_configuration_s *engineConfiguration = mainTriggerCallback->engineConfiguration;
	engine_configuration2_s *engineConfiguration2 = mainTriggerCallback->engineConfiguration2;

	float dwellMs = getSparkDwellMsT(engineConfiguration, rpm);
	if (cisnan(dwellMs) || dwellMs < 0) {
		firmwareError("invalid dwell: %f at %d", dwellMs, rpm);
		return;
	}

	ActuatorEvent *event = &iEvent->actuator;
	float sparkDelay = getOneDegreeTimeMs(rpm) * event->position.angleOffset;
	int isIgnitionError = sparkDelay < 0;
	ignitionErrorDetection.add(isIgnitionError);
	if (isIgnitionError) {
#if EFI_PROD_CODE
		scheduleMsg(&logger, "Negative spark delay=%f", sparkDelay);
#endif
		sparkDelay = 0;
		return;
	}

	OutputSignal *signal = event->actuator;
	//scheduleOutput(event->actuator, sparkDelay, dwellMs);

	if (cisnan(dwellMs)) {
		firmwareError("NaN in scheduleOutput", dwellMs);
		return;
	}

	/**
	 * We are alternating two event lists in order to avoid a potential issue around revolution boundary
	 * when an event is scheduled within the next revolution.
	 */
	scheduling_s * sUp = &signal->signalTimerUp[0];
	scheduling_s * sDown = &signal->signalTimerDown[0];

	/**
	 * The start of charge is always within the current trigger event range, so just plain time-based scheduling
	 */
	scheduleTask(sUp, (int) MS2US(sparkDelay), (schfunc_t) &turnPinHigh, (void *) signal);
	/**
	 * Spark event is often happening during a later trigger event timeframe
	 * TODO: improve precision
	 */

	event_trigger_position_s position;
	findTriggerPosition(engineConfiguration, &engineConfiguration2->triggerShape, &position, iEvent->advance);

	if (position.eventIndex == eventIndex) {
		float timeTillIgnition = getOneDegreeTimeMs(rpm) * position.angleOffset;

		scheduleTask(sDown, (int) MS2US(timeTillIgnition), (schfunc_t) &turnPinLow, (void*) signal);
	} else {
		scheduleTask(sDown, (int) MS2US(sparkDelay + dwellMs), (schfunc_t) &turnPinLow, (void*) signal);
	}
}

static void handleSpark(MainTriggerCallback *mainTriggerCallback, int eventIndex, int rpm, IgnitionEventList *list) {
	if (!isValidRpm(rpm))
		return; // this might happen for instance in case of a single trigger event after a pause

	/**
	 * Ignition schedule is defined once per revolution
	 * See initializeIgnitionActions()
	 */

//	scheduleSimpleMsg(&logger, "eventId spark ", eventIndex);
	for (int i = 0; i < list->size; i++) {
		IgnitionEvent *event = &list->events[i];
		if (event->actuator.position.eventIndex != eventIndex)
			continue;
		handleSparkEvent(mainTriggerCallback, eventIndex, event, rpm);
	}
}

static histogram_s mainLoopHisto;

void showMainHistogram(void) {
#if EFI_PROD_CODE
	printHistogram(&logger, &mainLoopHisto);
#endif
}

/**
 * This is the main trigger event handler.
 * Both injection and ignition are controlled from this method.
 */
void onTriggerEvent(ShaftEvents ckpSignalType, int eventIndex, MainTriggerCallback *mainTriggerCallback) {
	efiAssertVoid(eventIndex < mainTriggerCallback->engineConfiguration2->triggerShape.shaftPositionEventCount,
			"event index");
	efiAssertVoid(getRemainingStack(chThdSelf()) > 16, "stack#3");

	int rpm = getRpm();
	if (rpm == 0) {
		// this happens while we just start cranking
		// todo: check for 'trigger->is_synchnonized?'
		return;
	}
	if (rpm == NOISY_RPM) {
		warning(OBD_Camshaft_Position_Sensor_Circuit_Range_Performance, "noisy trigger");
		return;
	}
	if (rpm > mainTriggerCallback->engineConfiguration->rpmHardLimit) {
		warning(OBD_PCM_Processor_Fault, "skipping stroke due to rpm=%d", rpm);
		return;
	}

#if EFI_HISTOGRAMS && EFI_PROD_CODE
	int beforeCallback = hal_lld_get_counter_value();
#endif

	int revolutionIndex = getRevolutionCounter() % 2;

	if (eventIndex == 0) {
		if (localVersion.isOld())
			prepareOutputSignals(mainTriggerCallback->engineConfiguration, mainTriggerCallback->engineConfiguration2);

		/**
		 * TODO: warning. there is a bit of a hack here, todo: improve.
		 * currently output signals/times signalTimerUp from the previous revolutions could be
		 * still used because they have crossed the revolution boundary
		 * but we are already repurposing the output signals, but everything works because we
		 * are not affecting that space in memory. todo: use two instances of 'ignitionSignals'
		 */

		/**
		 * Within one engine cycle all cylinders are fired with same timing advance.
		 * todo: one day we can control cylinders individually
		 */
		float dwellMs = getSparkDwellMsT(mainTriggerCallback->engineConfiguration, rpm);
		if (cisnan(dwellMs) || dwellMs < 0) {
			firmwareError("invalid dwell: %f at %d", dwellMs, rpm);
			return;
		}
		float advance = getAdvance(rpm, getEngineLoadT(mainTriggerCallback->engineConfiguration));

		float dwellAngle = dwellMs / getOneDegreeTimeMs(rpm);

		initializeIgnitionActions(advance, dwellAngle, mainTriggerCallback->engineConfiguration,
				mainTriggerCallback->engineConfiguration2,
				&mainTriggerCallback->engineConfiguration2->engineEventConfiguration.ignitionEvents[revolutionIndex]);
	}

	triggerEventsQueue.executeAll(getCrankEventCounter());

	handleFuel(mainTriggerCallback, eventIndex, rpm);
	handleSpark(mainTriggerCallback, eventIndex, rpm,
			&mainTriggerCallback->engineConfiguration2->engineEventConfiguration.ignitionEvents[revolutionIndex]);
#if EFI_HISTOGRAMS && EFI_PROD_CODE
	int diff = hal_lld_get_counter_value() - beforeCallback;
	if (diff > 0)
	hsAdd(&mainLoopHisto, diff);
#endif /* EFI_HISTOGRAMS */
}

static void showTriggerHistogram(void) {
	printAllCallbacksHistogram();
	showMainHistogram();
}

static void showMainInfo(void) {
	int rpm = getRpm();
	float el = getEngineLoadT(mainTriggerCallbackInstance.engineConfiguration);
#if EFI_PROD_CODE
	scheduleMsg(&logger, "rpm %d engine_load %f", rpm, el);
	scheduleMsg(&logger, "fuel %fms timing %f", getFuelMs(rpm), getAdvance(rpm, el));
#endif
}

void MainTriggerCallback::init(engine_configuration_s *engineConfiguration,
		engine_configuration2_s *engineConfiguration2) {
	this->engineConfiguration = engineConfiguration;
	this->engineConfiguration2 = engineConfiguration2;
}

void initMainEventListener(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2) {
	mainTriggerCallbackInstance.init(engineConfiguration, engineConfiguration2);

#if EFI_PROD_CODE
	addConsoleAction("performanceinfo", showTriggerHistogram);
	addConsoleAction("maininfo", showMainInfo);

	initLogging(&logger, "main event handler");
	printMsg(&logger, "initMainLoop: %d", currentTimeMillis());
	if (!isInjectionEnabled(mainTriggerCallbackInstance.engineConfiguration2))
		printMsg(&logger, "!!!!!!!!!!!!!!!!!!! injection disabled");
#endif

#if EFI_HISTOGRAMS
	initHistogram(&mainLoopHisto, "main callback");
#endif /* EFI_HISTOGRAMS */

	addTriggerEventListener((ShaftPositionListener) &onTriggerEvent, "main loop", &mainTriggerCallbackInstance);
}

int isIgnitionTimingError(void) {
	return ignitionErrorDetection.sum(6) > 4;
}

#endif /* EFI_ENGINE_CONTROL */
