/**
 * @file	electronic_throttle.cpp
 * @brief	Electronic Throttle Module driver L298N
 *
 * todo: make this more universal if/when we get other hardware options
 *
 * @date Dec 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 *
 * This file is part of rusEfi - see http://rusefi.com
 *
 * rusEfi is free software; you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * rusEfi is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "main.h"
#include "electronic_throttle.h"
#include "pin_repository.h"
#include "idle_controller.h"
#include "tps.h"
#include "io_pins.h"
#include "engine_configuration.h"
#include "pwm_generator.h"
#include "pwm_generator_logic.h"
#include "pid.h"
#include "engine_controller.h"

#if EFI_ELECTRONIC_THROTTLE_BODY || defined(__DOXYGEN__)

#define ETB_FREQ 400

static LoggingWithStorage logger("ETB");
/**
 * @brief Control Thread stack
 */
static THD_WORKING_AREA(etbTreadStack, UTILITY_THREAD_STACK_SIZE);
/**
 * @brief Pulse-Width Modulation state
 */
static SimplePwm etbPwmUp;
static OutputPin output1;
static SimplePwm etbPwmDown;
static OutputPin output2;

static Pid pid(10, 0, 0, 0, 100);

static float prevTps;

static float currentEtbDuty;

EXTERN_ENGINE;

static msg_t etbThread(void *arg) {
        UNUSED(arg);
	while (true) {
		float pedal = getPedalPosition(PASS_ENGINE_PARAMETER_F);
		float tps = getTPS();

		currentEtbDuty = pid.getValue(pedal, getTPS(), 1);

		etbPwmUp.setSimplePwmDutyCycle(currentEtbDuty / 100);


//		if (tps != prevTps) {
//			prevTps = tps;
//			scheduleMsg(&logger, "tps=%d", (int) tps);
//		}

		// this thread is activated 10 times per second
		chThdSleepMilliseconds(boardConfiguration->etbDT);
	}
#if defined __GNUC__
	return -1;
#endif
}

static void setThrottleConsole(int level) {
	scheduleMsg(&logger, "setting throttle=%d", level);

	float dc = 0.01 + (minI(level, 98)) / 100.0;
	etbPwmUp.setSimplePwmDutyCycle(dc);
	print("st = %f\r\n", dc);
}

static void showEthInfo(void) {
	static char pinNameBuffer[16];

	scheduleMsg(&logger, "pedal=%f %d/%d @", getPedalPosition(), engineConfiguration->pedalPositionMin, engineConfiguration->pedalPositionMax,
			getPinNameByAdcChannel(engineConfiguration->pedalPositionChannel, pinNameBuffer));

	scheduleMsg(&logger, "tsp=%f", getTPS());

	scheduleMsg(&logger, "etbControlPin1=%s duty=%f", hwPortname(boardConfiguration->etbControlPin1),
			currentEtbDuty);
	scheduleMsg(&logger, "etb P=%f I=%f D=%f dT=%d", boardConfiguration->etbPFactor,
			boardConfiguration->etbIFactor,
			0.0,
			boardConfiguration->etbDT);
}

static void apply(void) {
	pid.updateFactors(boardConfiguration->etbPFactor, boardConfiguration->etbIFactor, 0);
}

static void setEtbPFactor(float value) {
	boardConfiguration->etbPFactor = value;
	apply();
	showEthInfo();
}

static void setEtbIFactor(float value) {
	boardConfiguration->etbIFactor = value;
	apply();
	showEthInfo();
}

void setDefaultEtbParameters(void) {
	engineConfiguration->pedalPositionMax = 6;
	boardConfiguration->etbPFactor = 10;
	boardConfiguration->etbIFactor = 0;
	boardConfiguration->etbDT = 100;
}

void initElectronicThrottle(void) {
	// these two lines are controlling direction
//	outputPinRegister("etb1", ELECTRONIC_THROTTLE_CONTROL_1, ETB_CONTROL_LINE_1_PORT, ETB_CONTROL_LINE_1_PIN);
//	outputPinRegister("etb2", ELECTRONIC_THROTTLE_CONTROL_2, ETB_CONTROL_LINE_2_PORT, ETB_CONTROL_LINE_2_PIN);

	// this line used for PWM
	startSimplePwmExt(&etbPwmUp, "etb1",
			boardConfiguration->etbControlPin1,
			&output1,
			ETB_FREQ,
			0.80,
			applyPinState);
	startSimplePwmExt(&etbPwmDown, "etb2",
			boardConfiguration->etbControlPin2,
			&output2,
			ETB_FREQ,
			0.80,
			applyPinState);

	addConsoleActionI("e", setThrottleConsole);

	addConsoleAction("ethinfo", showEthInfo);

	addConsoleActionF("set_etb_p", setEtbPFactor);
	addConsoleActionF("set_etb_i", setEtbIFactor);

	apply();

	chThdCreateStatic(etbTreadStack, sizeof(etbTreadStack), NORMALPRIO, (tfunc_t) etbThread, NULL);
}

#endif /* EFI_ELECTRONIC_THROTTLE_BODY */

