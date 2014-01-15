/**
 * @file	ignition_central.c
 * @brief	TODO
 *
 * @date Nov 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "ignition_central.h"
#include "io_pins.h"
#include "signal_executor.h"
#include "main_trigger_callback.h"

static Logging logger;

void initIgnitionCentral(void) {
	initLogging(&logger, "IgnitionCentral");

	setDefaultPinState(SPARKOUT_1_OUTPUT, OM_INVERTED);
	setDefaultPinState(SPARKOUT_2_OUTPUT, OM_INVERTED);
	setDefaultPinState(SPARKOUT_3_OUTPUT, OM_INVERTED);
	setDefaultPinState(SPARKOUT_4_OUTPUT, OM_INVERTED);
	setDefaultPinState(SPARKOUT_5_OUTPUT, OM_INVERTED);
}

void scheduleSparkOut(OutputSignal *igniter, int offsetSysTicks, int lengthSysTicks) {
//	chDbgAssert(igniterId >= 1 && igniterId <= MAX_IGNITER_COUNT, "igniter ID", null);

//	OutputSignal *igniter = &igniters[igniterId - 1];

	scheduleOutput(igniter, offsetSysTicks, lengthSysTicks, chTimeNow());
}
