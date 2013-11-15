/*
 * @file    main_loop.c
 * @brief   Main logic code
 *
 *
 *
 *  Created on: Feb 7, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "main_loop.h"
#include "engine_controller.h"
#include "settings.h"
#include "shaft_position_input.h"
#include "rpm_reporter.h"
#include "ckp_events.h"
#include "signal_executor.h"
#include "rficonsole.h"
#include "engine_math.h"
#include "injector_central.h"
#include "output_pins.h"
#include "engine_configuration.h"
#include "interpolation_3d.h"
#include "advance_map.h"

// todo: move this to EngineConfiguration2 for now
#define RPM_HARD_LIMIT 8000

extern EngineConfiguration *engineConfiguration;

extern int isInjectionEnabled;

static InjectionConfiguration injectionConfiguration;

extern myfloat globalFuelCorrection;

static Logging log;

static OutputSignal injectors[MAX_INJECTOR_COUNT];

/**
 * This method schedules asynchronous fuel squirt
 */
static void scheduleFuelInjection(int offsetSysTicks, int lengthSysTicks, int cylinderId) {
	assertCylinderId(cylinderId, "scheduleFuelInjection");

	if (!isInjectorEnabled(cylinderId))
		return;

	OutputSignal *injector = &injectors[cylinderId - 1];

	scheduleOutput(injector, offsetSysTicks, lengthSysTicks);
}

static void handleFuel(ShaftEvents ckpSignalType, int eventIndex) {

	if (!isInjectionEnabled)
		return;

	if (eventIndex < 0 || eventIndex >= SHAFT_POSITION_EVENT_COUNT) {
		scheduleSimpleMsg(&log, "ERROR: eventIndex ", eventIndex);
		return;
	}

	int cylinderId = injectionConfiguration.fireAtEventIndex[eventIndex];
	if (cylinderId == 0)
		return; // no cylinder should be fired at this event
	assertCylinderId(cylinderId, "onShaftSignal");

	int rpm = getCurrentRpm();
	if (rpm > RPM_HARD_LIMIT) {
		scheduleSimpleMsg(&log, "RPM above hard limit ", rpm);
		return;
	}

	scheduleSimpleMsg(&log, "eventId ", eventIndex);

	int fuelTicks = getFuelMs(rpm) * globalFuelCorrection * TICKS_IN_MS;
	if (fuelTicks < 0) {
		scheduleSimpleMsg(&log, "ERROR: negative injectionPeriod ", fuelTicks);
		return;
	}

	if (isCranking())
		scheduleSimpleMsg(&log, "crankingFuel=", fuelTicks);

	scheduleFuelInjection(0, fuelTicks, cylinderId);
}

static int getSparkDwell(int rpm) {
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

static void handleSpark(ShaftEvents ckpSignalType, int eventIndex) {
	int rpm = getCurrentRpm();

	int timeTillNextRise = convertAngleToSysticks(rpm, 90);

	float advance = getAdvance(rpm, getMaf());

	int sparkAdvance = convertAngleToSysticks(rpm, advance);

	int dwell = getSparkDwell(rpm);
//todo	chDbgCheck(dwell > 0, "invalid dwell");

	int sparkDelay = timeTillNextRise + sparkAdvance - dwell;
	if (sparkDelay < 0) {
		scheduleSimpleMsg(&log, "Negative spark delay", sparkDelay);
		return;
	}
//	scheduleSparkOut(sparkDelay, dwell);


}

/**
 * This is the main entry point into the primary shaft signal handler signal. Both injection and ignition are controlled from this method.
 */
static void onShaftSignal(ShaftEvents ckpSignalType, int eventIndex) {
	handleFuel(ckpSignalType, eventIndex);
	handleSpark(ckpSignalType, eventIndex);
}

void initMainEventListener() {
	initLogging(&log, "main event handler", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));
	printSimpleMsg(&log, "initMainLoop: ", chTimeNow());

	if (!isInjectionEnabled)
		printSimpleMsg(&log, "!!!!!!!!!!!!!!!!!!! injection disabled", 0);

	configureInjection(&injectionConfiguration);

	initOutputSignal("Injector 1", &injectors[0], INJECTOR_1_OUTPUT, 0);
	initOutputSignal("Injector 2", &injectors[1], INJECTOR_2_OUTPUT, 0);
	initOutputSignal("Injector 3", &injectors[2], INJECTOR_3_OUTPUT, 0);
	initOutputSignal("Injector 4", &injectors[3], INJECTOR_4_OUTPUT, 0);

	registerShaftPositionListener(&onShaftSignal, "main loop");
}
