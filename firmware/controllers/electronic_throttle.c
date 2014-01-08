/**
 * @file	electronic_throttle.c
 * @brief	Electronic Throttle Module driver L298N
 *
 * todo: make this more universal if/when we get other hardware options
 *
 * @date Dec 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "electronic_throttle.h"
#include "boards.h"
#include "pin_repository.h"
#include "rficonsole_logic.h"
#include "idle_controller.h"
#include "tps.h"
#include "io_pins.h"
#include "engine_configuration.h"

static Logging logger;
/**
 * @brief Control Thread stack
 */
static WORKING_AREA(etbTreadStack, UTILITY_THREAD_STACK_SIZE);
/**
 * @brief Pulse-Width Modulation state
 */
static PwmConfig etbPwm;

static float prevTps;

extern EngineConfiguration *engineConfiguration;

static msg_t etbThread(void *arg) {
	while (TRUE) {
		int tps = (int)getTPS();

		if (tps != prevTps) {
			prevTps = tps;
			scheduleSimpleMsg(&logger, "tps=", (int) tps);
		}

		// this thread is activated 10 times per second
		chThdSleepMilliseconds(100);
	}
	return -1;
}

static void setThrottleConsole(int level) {
	scheduleSimpleMsg(&logger, "setting throttle=", level);

	etbPwm.multiWave.switchTimes[0] = 0.01 + (min(level, 98)) / 100.0;
	print("st = %f\r\n", etbPwm.multiWave.switchTimes[0]);
}

void initElectronicThrottle(void) {
	if (1 == 1)
		return;
	initLogging(&logger, "Electronic Throttle");

	engineConfiguration->tpsMin = 140;
	engineConfiguration->tpsMax = 898;

	// these two lines are controlling direction
	outputPinRegister("etb1", ELECTRONIC_THROTTLE_CONTROL_1, ETB_CONTROL_LINE_1_PORT, ETB_CONTROL_LINE_1_PIN);
	outputPinRegister("etb2", ELECTRONIC_THROTTLE_CONTROL_2, ETB_CONTROL_LINE_2_PORT, ETB_CONTROL_LINE_2_PIN);

	// this line used for PWM
	wePlainInit("etb", &etbPwm, ETB_CONTROL_LINE_3_PORT, ETB_CONTROL_LINE_3_PIN, 0, 0.80, 500);

	addConsoleActionI("e", setThrottleConsole);
	chThdCreateStatic(etbTreadStack, sizeof(etbTreadStack), NORMALPRIO, (tfunc_t) etbThread, NULL);
}
