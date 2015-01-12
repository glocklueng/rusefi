/**
 * @file    main_trigger_callback.cpp
 * @brief   Main logic is here!
 *
 * See http://rusefi.com/docs/html/
 *
 * @date Feb 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
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

#if EFI_ENGINE_CONTROL || defined(__DOXYGEN__)

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
#include "efilib2.h"

EXTERN_ENGINE
;
extern bool hasFirmwareErrorFlag;

static LocalVersionHolder localVersion;

static MainTriggerCallback mainTriggerCallbackInstance;

/**
 * That's the list of pending spark firing events
 */
static IgnitionEvent *iHead = NULL;

/**
 * In order to archive higher event precision, we are using a hybrid approach
 * where we are scheduling events based on the closest trigger event with a time offset.
 *
 * This queue is using global trigger event index as 'time'
 */
//static EventQueue triggerEventsQueue;

static cyclic_buffer ignitionErrorDetection;

static Logging logger;

// todo: figure out if this even helps?
//#if defined __GNUC__
//#define RAM_METHOD_PREFIX __attribute__((section(".ram")))
//#else
//#define RAM_METHOD_PREFIX
//#endif

static void startSimultaniousInjection(Engine *engine) {
	for (int i = 0; i < engine->engineConfiguration->cylindersCount; i++) {
		turnPinHigh(INJECTOR_PIN_BY_INDEX(i));
	}
}

static void endSimultaniousInjection(Engine *engine) {
	for (int i = 0; i < engine->engineConfiguration->cylindersCount; i++) {
		turnPinLow(INJECTOR_PIN_BY_INDEX(i));
	}
}

static ALWAYS_INLINE void handleFuelInjectionEvent(InjectionEvent *event, int rpm DECLARE_ENGINE_PARAMETER_S) {
	/**
	 * todo: we do not really need to calculate fuel for each individual cylinder
	 */
	float fuelMs = getFuelMs(rpm PASS_ENGINE_PARAMETER) * engineConfiguration->globalFuelCorrection;
	if (cisnan(fuelMs)) {
		warning(OBD_PCM_Processor_Fault, "NaN injection pulse");
		return;
	}
	if (fuelMs < 0) {
		warning(OBD_PCM_Processor_Fault, "Negative injection pulse %f", fuelMs);
		return;
	}

	if (engine->isCylinderCleanupMode)
		return;

	float delayMs = getOneDegreeTimeMs(rpm) * event->position.angleOffset;

	if (event->isSimultanious) {
		if (fuelMs < 0) {
			firmwareError("duration cannot be negative: %d", fuelMs);
			return;
		}
		if (cisnan(fuelMs)) {
			firmwareError("NaN in scheduleOutput", fuelMs);
			return;
		}
		/**
		 * this is pretty much copy-paste of 'scheduleOutput'
		 * 'scheduleOutput' is currently only used for injection, so maybe it should be
		 * changed into 'scheduleInjection' and unified? todo: think about it.
		 */
		OutputSignal *signal = event->actuator;
		efiAssertVoid(signal!=NULL, "signal is NULL");
		int index = getRevolutionCounter() % 2;
		scheduling_s * sUp = &signal->signalTimerUp[index];
		scheduling_s * sDown = &signal->signalTimerDown[index];

		scheduleTask("out up", sUp, (int) MS2US(delayMs), (schfunc_t) &startSimultaniousInjection, engine);
		scheduleTask("out down", sDown, (int) MS2US(delayMs) + MS2US(fuelMs), (schfunc_t) &endSimultaniousInjection, engine);

	} else {
		scheduleOutput(event->actuator, delayMs, fuelMs);
	}
}

static ALWAYS_INLINE void handleFuel(uint32_t eventIndex, int rpm DECLARE_ENGINE_PARAMETER_S) {
	if (!isInjectionEnabled(engine->engineConfiguration))
		return;
	efiAssertVoid(getRemainingStack(chThdSelf()) > 128, "lowstck#3");
	efiAssertVoid(eventIndex < engine->triggerShape.getLength(), "event index");

	/**
	 * Ignition events are defined by addFuelEvents() according to selected
	 * fueling strategy
	 */
	FuelSchedule *fs =
	isCrankingR(rpm) ?
			&engine->engineConfiguration2->crankingInjectionEvents : &engine->engineConfiguration2->injectionEvents;

	ActuatorEventList *source = &fs->events;

	/**
	 * This is a performance optimization for https://sourceforge.net/p/rusefi/tickets/64/
	 * TODO: better data structure? better algorithm?
	 */
	if (!fs->hasEvents[eventIndex])
		return;

	for (int i = 0; i < source->size; i++) {
		InjectionEvent *event = &source->elements[i];
		if (event->position.eventIndex != eventIndex)
			continue;
		handleFuelInjectionEvent(event, rpm PASS_ENGINE_PARAMETER);
	}
}

static ALWAYS_INLINE void handleSparkEvent(uint32_t eventIndex, IgnitionEvent *iEvent,
		int rpm DECLARE_ENGINE_PARAMETER_S) {

	float dwellMs = getSparkDwellMsT(rpm PASS_ENGINE_PARAMETER);
	if (cisnan(dwellMs) || dwellMs < 0) {
		firmwareError("invalid dwell: %f at %d", dwellMs, rpm);
		return;
	}

	float sparkDelayUs = engine->rpmCalculator.oneDegreeUs * iEvent->dwellPosition.angleOffset;
	int isIgnitionError = sparkDelayUs < 0;
	ignitionErrorDetection.add(isIgnitionError);
	if (isIgnitionError) {
#if EFI_PROD_CODE
		scheduleMsg(&logger, "Negative spark delay=%f", sparkDelayUs);
#endif
		sparkDelayUs = 0;
		return;
	}

	if (cisnan(dwellMs)) {
		firmwareError("NaN in scheduleOutput", dwellMs);
		return;
	}

	/**
	 * We are alternating two event lists in order to avoid a potential issue around revolution boundary
	 * when an event is scheduled within the next revolution.
	 */
	scheduling_s * sUp = &iEvent->signalTimerUp;
	scheduling_s * sDown = &iEvent->signalTimerDown;

	/**
	 * The start of charge is always within the current trigger event range, so just plain time-based scheduling
	 */
	scheduleTask("spark up", sUp, sparkDelayUs, (schfunc_t) &turnPinHigh, (void *) iEvent->io_pin);
	/**
	 * Spark event is often happening during a later trigger event timeframe
	 * TODO: improve precision
	 */

	findTriggerPosition(&iEvent->sparkPosition, iEvent->advance PASS_ENGINE_PARAMETER);

	if (iEvent->sparkPosition.eventIndex == eventIndex) {
		/**
		 * Spark should be fired before the next trigger event - time-based delay is best precision possible
		 */
		float timeTillIgnitionUs = engine->rpmCalculator.oneDegreeUs * iEvent->sparkPosition.angleOffset;

		scheduleTask("spark 1down", sDown, (int) timeTillIgnitionUs, (schfunc_t) &turnPinLow, (void*) iEvent->io_pin);
	} else {
		/**
		 * Spark should be scheduled in relation to some future trigger event, this way we get better firing precision
		 */
		bool isPending = assertNotInList<IgnitionEvent>(iHead, iEvent);
		if (isPending)
			return;

		LL_APPEND(iHead, iEvent);
	}
}

static ALWAYS_INLINE void handleSpark(uint32_t eventIndex, int rpm,
		IgnitionEventList *list DECLARE_ENGINE_PARAMETER_S) {
	if (!isValidRpm(rpm) || !engineConfiguration->isIgnitionEnabled)
		return; // this might happen for instance in case of a single trigger event after a pause

	/**
	 * Ignition schedule is defined once per revolution
	 * See initializeIgnitionActions()
	 */

	IgnitionEvent *current, *tmp;

	LL_FOREACH_SAFE(iHead, current, tmp)
	{
		if (current->sparkPosition.eventIndex == eventIndex) {
			// time to fire a spark which was scheduled previously
			LL_DELETE(iHead, current);

			scheduling_s * sDown = &current->signalTimerDown;

			float timeTillIgnitionUs = engine->rpmCalculator.oneDegreeUs * current->sparkPosition.angleOffset;
			scheduleTask("spark 2down", sDown, (int) timeTillIgnitionUs, (schfunc_t) &turnPinLow,
					(void*) current->io_pin);
		}
	}

//	scheduleSimpleMsg(&logger, "eventId spark ", eventIndex);
	for (int i = 0; i < list->size; i++) {
		IgnitionEvent *event = &list->elements[i];
		if (event->dwellPosition.eventIndex != eventIndex)
			continue;
		handleSparkEvent(eventIndex, event, rpm PASS_ENGINE_PARAMETER);
	}
}

static histogram_s mainLoopHisto;

void showMainHistogram(void) {
#if EFI_PROD_CODE
	printHistogram(&logger, &mainLoopHisto);
#endif
}

static void doSomeCalc(int rpm DECLARE_ENGINE_PARAMETER_S) {
	/**
	 * Within one engine cycle all cylinders are fired with same timing advance.
	 * todo: one day we can control cylinders individually
	 */
	float dwellMs = getSparkDwellMsT(rpm PASS_ENGINE_PARAMETER);

	if (cisnan(dwellMs) || dwellMs < 0) {
		firmwareError("invalid dwell: %f at %d", dwellMs, rpm);
		return;
	}
	float el = getEngineLoadT(PASS_ENGINE_PARAMETER_F);
	engine->advance = -getAdvance(rpm, el PASS_ENGINE_PARAMETER);

	engine->dwellAngle = dwellMs / getOneDegreeTimeMs(rpm);
}

/**
 * This is the main trigger event handler.
 * Both injection and ignition are controlled from this method.
 */
void mainTriggerCallback(trigger_event_e ckpSignalType, uint32_t eventIndex DECLARE_ENGINE_PARAMETER_S) {
	if (hasFirmwareError()) {
		/**
		 * In case on a major error we should not process any more events.
		 * TODO: add 'pin shutdown' invocation somewhere
		 */
		return;
	}

	(void) ckpSignalType;
	efiAssertVoid(eventIndex < 2 * engine->triggerShape.getSize(), "event index");
	efiAssertVoid(getRemainingStack(chThdSelf()) > 128, "lowstck#2");

	int rpm = getRpmE(engine);
	if (rpm == 0) {
		// this happens while we just start cranking
		// todo: check for 'trigger->is_synchnonized?'
		return;
	}
	if (rpm == NOISY_RPM) {
		warning(OBD_Camshaft_Position_Sensor_Circuit_Range_Performance, "noisy trigger");
		return;
	}
	if (rpm > engineConfiguration->rpmHardLimit) {
		warning(OBD_PCM_Processor_Fault, "skipping stroke due to rpm=%d", rpm);
		return;
	}

#if EFI_HISTOGRAMS && EFI_PROD_CODE
	int beforeCallback = hal_lld_get_counter_value();
#endif

	int revolutionIndex = engine->rpmCalculator.getRevolutionCounter() % 2;

	if (eventIndex == 0) {
		if (localVersion.isOld())
			prepareOutputSignals(PASS_ENGINE_PARAMETER_F);
	}

	if (eventIndex == engineConfiguration->ignMathCalculateAtIndex) {
		engine->beforeIgnitionMath = GET_TIMESTAMP();
		doSomeCalc(rpm PASS_ENGINE_PARAMETER);
		engine->ignitionMathTime = GET_TIMESTAMP() - engine->beforeIgnitionMath;
	}

	if (eventIndex == 0) {

		engine->beforeIgnitionSch = GET_TIMESTAMP();
		/**
		 * TODO: warning. there is a bit of a hack here, todo: improve.
		 * currently output signals/times signalTimerUp from the previous revolutions could be
		 * still used because they have crossed the revolution boundary
		 * but we are already repurposing the output signals, but everything works because we
		 * are not affecting that space in memory. todo: use two instances of 'ignitionSignals'
		 */
		float maxAllowedDwellAngle = (int)(engineConfiguration->engineCycle / 2); // the cast is about making Coverity happy

		if (engineConfiguration->ignitionMode == IM_ONE_COIL) {
			maxAllowedDwellAngle = engineConfiguration->engineCycle / engineConfiguration->cylindersCount / 1.1;
		}

		if (engine->dwellAngle > maxAllowedDwellAngle) {
			warning(OBD_PCM_Processor_Fault, "dwell angle too long: %f", engine->dwellAngle);
		}

		// todo: add some check for dwell overflow? like 4 times 6 ms while engine cycle is less then that

		if (cisnan(engine->advance)) {
			// error should already be reported
			return;
		}
		initializeIgnitionActions(engine->advance, engine->dwellAngle,
				&engine->engineConfiguration2->ignitionEvents[revolutionIndex] PASS_ENGINE_PARAMETER);
		engine->ignitionSchTime = GET_TIMESTAMP() - engine->beforeIgnitionSch;
	}

//	triggerEventsQueue.executeAll(getCrankEventCounter());

	handleFuel(eventIndex, rpm PASS_ENGINE_PARAMETER);
	handleSpark(eventIndex, rpm, &engine->engineConfiguration2->ignitionEvents[revolutionIndex] PASS_ENGINE_PARAMETER);
#if EFI_HISTOGRAMS && EFI_PROD_CODE
	int diff = hal_lld_get_counter_value() - beforeCallback;
	if (diff > 0)
	hsAdd(&mainLoopHisto, diff);
#endif /* EFI_HISTOGRAMS */
}

#if EFI_PROD_CODE
#include "wave_chart.h"
#endif

static void showTriggerHistogram(void) {
	printAllCallbacksHistogram();
	showMainHistogram();
#if EFI_PROD_CODE
	showWaveChartHistogram();
#endif
}

void MainTriggerCallback::init(Engine *engine) {
	efiAssertVoid(engine!=NULL, "engine NULL");
	this->engine = engine;
}

static void showMainInfo(Engine *engine) {
#if EFI_PROD_CODE
	int rpm = engine->rpmCalculator.rpm(PASS_ENGINE_PARAMETER_F);
	float el = getEngineLoadT(PASS_ENGINE_PARAMETER);
	scheduleMsg(&logger, "rpm %d engine_load %f", rpm, el);
	scheduleMsg(&logger, "fuel %fms timing %f", getFuelMs(rpm PASS_ENGINE_PARAMETER),
			getAdvance(rpm, el PASS_ENGINE_PARAMETER));
#endif
}

void initMainEventListener(Engine *engine) {
	efiAssertVoid(engine!=NULL, "null engine");

	mainTriggerCallbackInstance.init(engine);

#if EFI_PROD_CODE || defined(__DOXYGEN__)
	addConsoleAction("performanceinfo", showTriggerHistogram);
	addConsoleActionP("maininfo", (VoidPtr) showMainInfo, engine);

	initLogging(&logger, "main event handler");
	printMsg(&logger, "initMainLoop: %d", currentTimeMillis());
	if (!isInjectionEnabled(mainTriggerCallbackInstance.engine->engineConfiguration))
		printMsg(&logger, "!!!!!!!!!!!!!!!!!!! injection disabled");
#endif

#if EFI_HISTOGRAMS
	initHistogram(&mainLoopHisto, "main callback");
#endif /* EFI_HISTOGRAMS */

	addTriggerEventListener(mainTriggerCallback, "main loop", engine);
}

int isIgnitionTimingError(void) {
	return ignitionErrorDetection.sum(6) > 4;
}

#endif /* EFI_ENGINE_CONTROL */
