/*
 * engine_status.c
 *
 *  Created on: Feb 7, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "rpm_reporter.h"
#include "idle_thread.h"
#include "injector_control.h"
#include "rpm_reporter.h"
#include "sparkout.h"
#include "main_loop.h"
#include "map_multiplier_thread.h"
#include "timers.h"

int isCranking() {
	int rpm = getCurrentRpm();
	return rpm > 0 && rpm < 400;
}

void initEngineContoller() {
	initOutputSignals();

	initInjectorsControl();

	/**
	 * there is an implicit dependency on the fact that 'tachomenter' listener is the 1st listener - this case
	 * other listeners can access current RPM value
	 */
	initTachometer();

	initMapAdjusterThread();
	initTimers();
	initMainLoop();

	startIdleThread();
}
