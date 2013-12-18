/**
 * @file    main_loop.c
 * @brief   Main logic code
 *
 *
 * @date Feb 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "main_loop.h"
#include "engine_controller.h"
#include "settings.h"
#include "shaft_position_input.h"
#include "rpm_calculator.h"
#include "ckp_events.h"
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

// todo: move this to EngineConfiguration2 for now

extern EngineConfiguration *engineConfiguration;
extern EngineConfiguration2 engineConfiguration2;

static cyclic_buffer ignitionErrorDetection;

extern int isInjectionEnabled;

static EventHandlerConfiguration engineEventConfiguration;

extern myfloat globalFuelCorrection;

static Logging logger;

/**
 * this field is accessed only from shaft sensor event handler.
 * This is not a method variable just to save us from stack overflow.
 */
static ActuatorEventList events;

static void handleFuelInjectionEvent(ActuatorEvent *event, int rpm) {
	int cylinderId = event->actuatorId;
	if (cylinderId == 0)
		return; // no cylinder should be fired at this event
	assertCylinderId(cylinderId, "onShaftSignal");

	if (rpm > engineConfiguration->rpmHardLimit) {
		scheduleSimpleMsg(&logger, "RPM above hard limit ", rpm);
		return;
	}

	int fuelTicks = getFuelMs(rpm) * globalFuelCorrection * TICKS_IN_MS;
	if (fuelTicks < 0) {
		scheduleSimpleMsg(&logger, "ERROR: negative injectionPeriod ", fuelTicks);
		return;
	}

	if (isCranking())
		scheduleSimpleMsg(&logger, "crankingFuel=", fuelTicks);

	scheduleFuelInjection(0, fuelTicks, cylinderId);
}

static void handleFuel(ShaftEvents ckpSignalType, int eventIndex) {
	if (!isInjectionEnabled)
		return;

	if (eventIndex < 0 || eventIndex >= engineConfiguration2.shaftPositionEventCount) {
		scheduleSimpleMsg(&logger, "ERROR: eventIndex ", eventIndex);
		return;
	}

	ActuatorEventList *source =
			isCranking() ?
					&engineEventConfiguration.crankingInjectionEvents : &engineEventConfiguration.injectionEvents;
	findEvents(eventIndex, source, &events);

	if (events.size == 0)
		return;

	scheduleSimpleMsg(&logger, "eventId size=", events.size);

	int rpm = getCurrentRpm();

	for (int i = 0; i < events.size; i++) {
		ActuatorEvent *event = &events.events[i];
		handleFuelInjectionEvent(event, rpm);
	}
}

static int getSparkDwell(int rpm) {
	if (isCrankingR(rpm)) {
		int angle = engineConfiguration->crankingChargeAngle;
		return convertAngleToSysticks(rpm, angle);;
	}

	if (rpm > engineConfiguration->rpmHardLimit) {
		warning("skipping spark due to rpm=", rpm);
		return 0;
	}
	int defaultDwell = TICKS_IN_MS * 4;
	if (rpm <= 4500)
		return defaultDwell;
	rpm -= 4500;
	/**
	 * at higher RPM we simply do not have enough time to charge the coil completely
	 */
	// for each 2000 rpm above 4500 rom we reduce dwell by 1 ms
	int dec = rpm * TICKS_IN_MS / 2000;
	return defaultDwell - dec;
}

static void handleSparkEvent(ActuatorEvent *event, int rpm) {
	int igniterId = event->actuatorId;
	chDbgAssert(igniterId > 0, "act id", NULL);

	float advance = getAdvance(rpm, getMaf());

	int sparkAdvance = convertAngleToSysticks(rpm, advance);

	int dwell = getSparkDwell(rpm);
	chDbgCheck(dwell >= 0, "invalid dwell");

	if (dwell == 0)
		return; // hard RPM limit was hit



	int sparkDelay = convertAngleToSysticks(rpm, event->angleOffset) + sparkAdvance - dwell;
	int isIgnitionError = sparkDelay < 0;
	cbAdd(&ignitionErrorDetection, isIgnitionError);
	if (isIgnitionError) {
		scheduleSimpleMsg(&logger, "Negative spark delay", sparkDelay);
		sparkDelay = 0;
		//return;
	}

	scheduleSparkOut(igniterId, sparkDelay, dwell);
}

static void handleSpark(ShaftEvents ckpSignalType, int eventIndex) {
	int rpm = getCurrentRpm();

	findEvents(eventIndex, &engineEventConfiguration.ignitionEvents, &events);
	if (events.size == 0)
		return;

	scheduleSimpleMsg(&logger, "eventId spark ", eventIndex);

	for (int i = 0; i < events.size; i++) {
		ActuatorEvent *event = &events.events[i];
		handleSparkEvent(event, rpm);
	}
}

/**
 * This is the main entry point into the primary shaft signal handler signal. Both injection and ignition are controlled from this method.
 */
static void onShaftSignal(ShaftEvents ckpSignalType, int eventIndex) {
	if (eventIndex >= engineConfiguration2.shaftPositionEventCount) {
		warning("unexpected eventIndex=", eventIndex);
		return;
	}
	handleFuel(ckpSignalType, eventIndex);
	handleSpark(ckpSignalType, eventIndex);
}

void initMainEventListener() {
	initLogging(&logger, "main event handler");
	printSimpleMsg(&logger, "initMainLoop: ", chTimeNow());
	cbInit(&ignitionErrorDetection);

	if (!isInjectionEnabled)
		printSimpleMsg(&logger, "!!!!!!!!!!!!!!!!!!! injection disabled", 0);

	configureEngineEventHandler(&engineEventConfiguration);

	registerShaftPositionListener(&onShaftSignal, "main loop");
}

int isIgnitionTimingError(void) {
	return cbSum(&ignitionErrorDetection, 6) > 4;
}
