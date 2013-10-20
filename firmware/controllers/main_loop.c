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

#define RPM_HARD_LIMIT 8000

extern int isInjectionEnabled;

static InjectionConfiguration injectionConfiguration;

extern myfloat globalFuelCorrection;

static Logging log;

/**
 * This is the main entry point into the primary shaft signal handler signal. Both injection and ignition are controlled from this method.
 */
static void onShaftSignal(ShaftEvents ckpSignalType, int eventIndex) {
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

void initMainEventListener() {
	initLogging(&log, "main event handler", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));
	printSimpleMsg(&log, "initMainLoop: ", chTimeNow());

	if (!isInjectionEnabled)
		printSimpleMsg(&log, "!!!!!!!!!!!!!!!!!!! injection disabled", 0);

	configureInjection(&injectionConfiguration);

	registerShaftPositionListener(&onShaftSignal, "main loop");
}
