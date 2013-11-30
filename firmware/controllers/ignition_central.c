/**
 * @file	ignition_central.c
 * @brirf	TODO
 *
 * @date Nov 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "ignition_central.h"
#include "output_pins.h"
#include "signal_executor.h"
#include "main_loop.h"

static Logging logger;

static OutputSignal igniters[MAX_IGNITER_COUNT];

void initIgnitionCentral(void) {
	initLogging(&logger, "IgnitionCentral", logger.DEFAULT_BUFFER, sizeof(logger.DEFAULT_BUFFER));

	initOutputSignal("Spark 1", &igniters[0], SPARKOUT_1_OUTPUT, 1);
	initOutputSignal("Spark 2", &igniters[1], SPARKOUT_2_OUTPUT, 1);
}

void scheduleSparkOut(int igniterId, int offsetSysTicks, int lengthSysTicks) {
	chDbgAssert(igniterId >= 1 && igniterId <= MAX_IGNITER_COUNT, "igniter ID", null);

	OutputSignal *igniter = &igniters[igniterId - 1];

	scheduleOutput(igniter, offsetSysTicks, lengthSysTicks);
}
