/**
 * @file    main_trigger_callback.c
 * @brief   Main logic is here!
 *
 * See http://rusefi.com/docs/html/
 *
 * @date Feb 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "main_trigger_callback.h"
#include "engine_controller.h"
#include "settings.h"
#include "trigger_input.h"
#include "rpm_calculator.h"
#include "signal_executor.h"
#include "rficonsole.h"
#include "engine_math.h"
#include "injector_central.h"
#include "ignition_central.h"
#include "engine_configuration.h"
#include "interpolation.h"
#include "advance_map.h"
#include "allsensors.h"
#include "cyclic_buffer.h"

// todo: move this to engine_configuration2_s for now

extern engine_configuration_s *engineConfiguration;
extern engine_configuration2_s *engineConfiguration2;

static cyclic_buffer ignitionErrorDetection;

extern int isInjectionEnabled;

extern myfloat globalFuelCorrection;

static Logging logger;

/**
 * this field is accessed only from shaft sensor event handler.
 * This is not a method variable just to save us from stack overflow.
 */
static ActuatorEventList events;

static void handleFuelInjectionEvent(ActuatorEvent *event, int rpm) {
//	int cylinderId = event->actuatorId;
//	if (cylinderId == 0)
//		return; // no cylinder should be fired at this event
//	assertCylinderId(cylinderId, "onShaftSignal");

	if (rpm > engineConfiguration->rpmHardLimit) {
		scheduleSimpleMsg(&logger, "RPM above hard limit ", rpm);
		return;
	}

	int fuelTicks = (int)(getFuelMs(rpm) * globalFuelCorrection * TICKS_IN_MS);
	if (fuelTicks < 0) {
		scheduleSimpleMsg(&logger, "ERROR: negative injectionPeriod ", fuelTicks);
		return;
	}

	int delay = (int)(getOneDegreeTime(rpm) * event->angleOffset);

	if (isCranking())
		scheduleSimpleMsg(&logger, "crankingFuel=", fuelTicks);

	scheduleFuelInjection(delay, fuelTicks, event->actuator);
}

static void handleFuel(ShaftEvents ckpSignalType, int eventIndex) {
	if (!isInjectionEnabled)
		return;

	if (eventIndex < 0 || eventIndex >= engineConfiguration2->triggerShape.shaftPositionEventCount) {
		scheduleSimpleMsg(&logger, "ERROR: eventIndex ", eventIndex);
		return;
	}

	ActuatorEventList *source =
			isCranking() ?
					&engineConfiguration2->engineEventConfiguration.crankingInjectionEvents : &engineConfiguration2->engineEventConfiguration.injectionEvents;
	findEvents(eventIndex, source, &events);

	if (events.size == 0)
		return;

//	scheduleSimpleMsg(&logger, "eventId size=", events.size);

	int rpm = getRpm();

	for (int i = 0; i < events.size; i++) {
		ActuatorEvent *event = &events.events[i];
		handleFuelInjectionEvent(event, rpm);
	}
}

static void handleSparkEvent(ActuatorEvent *event, int rpm) {
	float advance = getAdvance(rpm, getEngineLoad());

	float sparkAdvanceMs = getOneDegreeTimeMs(rpm) * advance;

	float dwellMs = getSparkDwellMs(rpm);
	chDbgCheck(dwellMs >= 0, "invalid dwell");

	if (dwellMs == 0)
		return; // hard RPM limit was hit

	float sparkDelay = (int)(getOneDegreeTimeMs(rpm) * event->angleOffset + sparkAdvanceMs - dwellMs);
	int isIgnitionError = sparkDelay < 0;
	cbAdd(&ignitionErrorDetection, isIgnitionError);
	if (isIgnitionError) {
		scheduleMsg(&logger, "Negative spark delay=%f", sparkDelay);
		sparkDelay = 0;
		//return;
	}

	scheduleSparkOut(event->actuator, sparkDelay * TICKS_IN_MS, dwellMs * TICKS_IN_MS);
}

static void handleSpark(ShaftEvents ckpSignalType, int eventIndex) {
	int rpm = getRpm();

	findEvents(eventIndex, &engineConfiguration2->engineEventConfiguration.ignitionEvents, &events);
	if (events.size == 0)
		return;

//	scheduleSimpleMsg(&logger, "eventId spark ", eventIndex);

	for (int i = 0; i < events.size; i++) {
		ActuatorEvent *event = &events.events[i];
		handleSparkEvent(event, rpm);
	}
}

static histogram_s mainLoopHisto;

void showMainHistogram(void) {
	printHistogram(&logger, &mainLoopHisto);
}

/**
 * This is the main entry point into the primary shaft signal handler signal. Both injection and ignition are controlled from this method.
 */
static void onShaftSignal(ShaftEvents ckpSignalType, int eventIndex) {
	int beforeCallback = hal_lld_get_counter_value();
	if (eventIndex >= engineConfiguration2->triggerShape.shaftPositionEventCount) {
		warning("unexpected eventIndex=", eventIndex);
	} else {
		handleFuel(ckpSignalType, eventIndex);
		handleSpark(ckpSignalType, eventIndex);
	}
	int diff = hal_lld_get_counter_value() - beforeCallback;
	if (diff > 0)
		hsAdd(&mainLoopHisto, diff);
}

void initMainEventListener() {
	initLogging(&logger, "main event handler");
	printSimpleMsg(&logger, "initMainLoop: ", chTimeNow());
	cbInit(&ignitionErrorDetection);
	resetHistogram(&mainLoopHisto, "main");

	if (!isInjectionEnabled)
		printSimpleMsg(&logger, "!!!!!!!!!!!!!!!!!!! injection disabled", 0);

	registerShaftPositionListener(&onShaftSignal, "main loop");
}

int isIgnitionTimingError(void) {
	return cbSum(&ignitionErrorDetection, 6) > 4;
}
