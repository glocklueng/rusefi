/**
 * @file	electronic_throttle.c
 *
 * @date Dec 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "electronic_throttle.h"
#include "boards.h"
#include "output_pins.h"
#include "rficonsole_logic.h"

static Logging logger;

static void setThrottleConsole(int level) {
	scheduleSimpleMsg(&logger, "setting throttle %d\r\n", level);
}

void initElectronicThrottle(void) {
	initLogging(&logger, "Electronic Throttle");


	outputPinRegister("etb1", ELECTRONIC_THROTTLE_CONTROL_1, ETB_CONTROL_LINE_1_PORT, ETB_CONTROL_LINE_1_PIN);
	outputPinRegister("etb2", ELECTRONIC_THROTTLE_CONTROL_2, ETB_CONTROL_LINE_2_PORT, ETB_CONTROL_LINE_2_PIN);

	addConsoleActionI("e", setThrottleConsole);
}
