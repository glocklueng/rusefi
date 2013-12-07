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
#include "idle_controller.h"

static Logging logger;

static PwmConfig etbPwm;

static void setThrottleConsole(int level) {
	scheduleSimpleMsg(&logger, "setting throttle=", level);

	etbPwm.switchTimes[0] = 0.01 + (min(level, 98)) / 100.0;
	print("st = %f\r\n", etbPwm.switchTimes[0]);
}

void initElectronicThrottle(void) {
	initLogging(&logger, "Electronic Throttle");

	// these two lines are controlling direction
	outputPinRegister("etb1", ELECTRONIC_THROTTLE_CONTROL_1, ETB_CONTROL_LINE_1_PORT, ETB_CONTROL_LINE_1_PIN);
	outputPinRegister("etb2", ELECTRONIC_THROTTLE_CONTROL_2, ETB_CONTROL_LINE_2_PORT, ETB_CONTROL_LINE_2_PIN);

	// this line used for PWM
	wePlainInit("etb", &etbPwm, ETB_CONTROL_LINE_3_PORT, ETB_CONTROL_LINE_3_PIN, 0, 0.80, 500);

	addConsoleActionI("e", setThrottleConsole);
}
