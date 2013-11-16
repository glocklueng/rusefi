/*
 * @file	ignition_central.c
 * @brirf	TODO
 *
 *  Created on: Nov 15, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "output_pins.h"
#include "signal_executor.h"
#include "main_loop.h"

static Logging log;

static OutputSignal igniters[MAX_IGNITER_COUNT];

void initIgnitionCentral(void) {
	initLogging(&log, "IgnitionCentral", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));

	initOutputSignal("Spark 1", &igniters[0], SPARKOUT_1_OUTPUT, 0);
}

void scheduleSparkOut(int igniterId, int offsetSysTicks, int lengthSysTicks) {
	OutputSignal *igniter = &igniters[igniterId - 1];

	scheduleOutput(igniter, offsetSysTicks, lengthSysTicks);
}
