/*
 *  Created on: Feb 7, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    engine_controller.c
 * @brief   Controllers package entry point code
 */

#include "main.h"
#include "rpm_reporter.h"
#include "idle_thread.h"
#include "settings.h"
#include "rpm_reporter.h"
#include "signal_executor.h"
#include "main_loop.h"
#include "map_multiplier_thread.h"
#include "output_pins.h"

#define _10_MILLISECONDS (10 * TICKS_IN_MS)

static VirtualTimer everyMsTimer;

int isCranking() {
	int rpm = getCurrentRpm();
	return rpm > 0 && rpm < 400;
}

int systicks2ms(int systicks) {
	return systicks / TICKS_IN_MS;
}

static void updateStatusLeds() {
	int is_cranking = isCranking();
	setOutputPinValue(LED_RUNNING, getCurrentRpm() > 0 && !is_cranking);
	setOutputPinValue(LED_CRANKING, is_cranking);
}

static void onEveny10Milliseconds() {
	updateStatusLeds();

	// schedule next invocation
	chSysLockFromIsr()
	;
	chVTSetI(&everyMsTimer, _10_MILLISECONDS, &onEveny10Milliseconds, 0);
	chSysUnlockFromIsr()
	;
}

static void initPeriodicEvents() {
	// schedule first invocation
	chVTSet(&everyMsTimer, _10_MILLISECONDS, &onEveny10Milliseconds, 0);
}

void initEngineContoller() {
	initOutputSignals();

	initSettings();

	/**
	 * there is an implicit dependency on the fact that 'tachometer' listener is the 1st listener - this case
	 * other listeners can access current RPM value
	 */
	initTachometer();

	initMapAdjusterThread();
	initPeriodicEvents();
	/**
	 * This method initialized the main listener which actually runs injectors & ignition
	 */
	initMainEventListener();

	startIdleThread();
}
