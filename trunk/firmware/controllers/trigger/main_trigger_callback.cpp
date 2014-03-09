/**
 * @file    main_trigger_callback.c
 * @brief   Main logic is here!
 *
 * See http://rusefi.com/docs/html/
 *
 * @date Feb 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "main_trigger_callback.h"

extern "C"
{
//#include "settings.h"
#include "trigger_central.h"
#include "rpm_calculator.h"
#include "signal_executor.h"
#include "eficonsole.h"
#include "engine_math.h"
//#include "injector_central.h"
//#include "ignition_central.h"
#include "engine_configuration.h"
#include "interpolation.h"
#include "advance_map.h"
#include "allsensors.h"
#include "cyclic_buffer.h"
#include "histogram.h"
#include "fuel_math.h"
#include "histogram.h"
#include "rfiutil.h"

int isInjectionEnabled(void);

}

// todo: move this to engine_configuration2_s for now

extern engine_configuration_s *engineConfiguration;
extern engine_configuration2_s *engineConfiguration2;

static cyclic_buffer ignitionErrorDetection;

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
		scheduleMsg(&logger, "RPM above hard limit %d", rpm);
		return;
	}

	int fuelTicks = (int) (getFuelMs(rpm) * engineConfiguration->globalFuelCorrection * TICKS_IN_MS);
	if (fuelTicks < 0) {
		scheduleMsg(&logger, "ERROR: negative injectionPeriod %d", fuelTicks);
		return;
	}

	int delay = (int) (getOneDegreeTime(rpm) * event->angleOffset);

	if (isCranking())
		scheduleMsg(&logger, "crankingFuel=%d", fuelTicks);

	scheduleOutput(event->actuator, delay, fuelTicks, chTimeNow());
}

static void handleFuel(ShaftEvents ckpSignalType, int eventIndex) {
	if (!isInjectionEnabled())
		return;
	chDbgCheck(eventIndex < engineConfiguration2->triggerShape.shaftPositionEventCount, "event index");

	ActuatorEventList *source =
			isCranking() ?
					&engineConfiguration2->engineEventConfiguration.crankingInjectionEvents :
					&engineConfiguration2->engineEventConfiguration.injectionEvents;
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
	if (rpm == 0)
		return;
	float advance = getAdvance(rpm, getEngineLoad());

	float sparkAdvanceMs = getOneDegreeTimeMs(rpm) * advance;

	float dwellMs = getSparkDwellMs(rpm);
	if (dwellMs < 0)
		firmwareError("invalid dwell: %f at %d", dwellMs, rpm);

	if (dwellMs <= 0)
		return; // hard RPM limit was hit

	float sparkDelay = (int) (getOneDegreeTimeMs(rpm) * event->angleOffset + sparkAdvanceMs - dwellMs);
	int isIgnitionError = sparkDelay < 0;
	ignitionErrorDetection.add(isIgnitionError);
	if (isIgnitionError) {
		scheduleMsg(&logger, "Negative spark delay=%f", sparkDelay);
		sparkDelay = 0;
		//return;
	}

	scheduleOutput(event->actuator, sparkDelay * TICKS_IN_MS, dwellMs * TICKS_IN_MS, chTimeNow());
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
	chDbgCheck(eventIndex < engineConfiguration2->triggerShape.shaftPositionEventCount, "event index");
	int beforeCallback = hal_lld_get_counter_value();
	handleFuel(ckpSignalType, eventIndex);
	handleSpark(ckpSignalType, eventIndex);
	int diff = hal_lld_get_counter_value() - beforeCallback;
	if (diff > 0)
		hsAdd(&mainLoopHisto, diff);
}

static void showTriggerHistogram(void) {
	printAllCallbacksHistogram();
	showMainHistogram();
}

void initMainEventListener() {
	addConsoleAction("trigger_hist", showTriggerHistogram);

	initLogging(&logger, "main event handler");
	printMsg(&logger, "initMainLoop: %d", chTimeNow());
	resetHistogram(&mainLoopHisto, "main");

	if (!isInjectionEnabled())
		printMsg(&logger, "!!!!!!!!!!!!!!!!!!! injection disabled");

	registerShaftPositionListener(&onShaftSignal, "main loop");
}

int isIgnitionTimingError(void) {
	return ignitionErrorDetection.sum(6) > 4;
}
