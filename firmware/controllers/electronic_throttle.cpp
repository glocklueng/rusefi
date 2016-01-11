/**
 * @file	electronic_throttle.cpp
 * @brief	Electronic Throttle Module driver L298N
 *
 * todo: make this more universal if/when we get other hardware options
 *
 * @date Dec 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2016
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
extern pin_output_mode_e DEFAULT_OUTPUT;

static LoggingWithStorage logger("ETB");
/**
 * @brief Control Thread stack
 */
static THD_WORKING_AREA(etbTreadStack, UTILITY_THREAD_STACK_SIZE);
/**
 * @brief Pulse-Width Modulation state
 */
static SimplePwm etbPwmUp CCM_OPTIONAL;
static OutputPin output1 CCM_OPTIONAL;
static SimplePwm etbPwmDown CCM_OPTIONAL;
static OutputPin output2 CCM_OPTIONAL;

static OutputPin outputDirectionOpen CCM_OPTIONAL;
static OutputPin outputDirectionClose CCM_OPTIONAL;

static Pid pid(1, 0, 0, 0, 100);

static float prevTps;

static float currentEtbDuty;

EXTERN_ENGINE;

static bool wasEtbBraking = false;

static msg_t etbThread(void *arg) {
        UNUSED(arg);
	while (true) {
		percent_t pedal = getPedalPosition(PASS_ENGINE_PARAMETER_F);
		percent_t tps = getTPS();

		currentEtbDuty = pid.getValue(pedal, getTPS(), 1);

		etbPwmUp.setSimplePwmDutyCycle(currentEtbDuty / 100);

		bool needEtbBraking = absF(pedal - tps) < 3;
		if (needEtbBraking != wasEtbBraking) {
			scheduleMsg(&logger, "need ETB braking: %d", needEtbBraking);
			wasEtbBraking = needEtbBraking;
		}
		outputDirectionClose.setValue(needEtbBraking);


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

	scheduleMsg(&logger, "TPS=%f", getTPS());

	scheduleMsg(&logger, "etbControlPin1=%s duty=%f", hwPortname(boardConfiguration->etbControlPin1),
			currentEtbDuty);
	scheduleMsg(&logger, "close dir=%s", hwPortname(boardConfiguration->etbDirectionPin2));
	scheduleMsg(&logger, "etb P=%f I=%f D=%f dT=%d", engineConfiguration->etb.pFactor,
			engineConfiguration->etb.iFactor,
			0.0,
			boardConfiguration->etbDT);
}

static void apply(void) {
	pid.updateFactors(engineConfiguration->etb.pFactor, engineConfiguration->etb.iFactor, 0);
}

static void setEtbPFactor(float value) {
	engineConfiguration->etb.pFactor = value;
	apply();
	showEthInfo();
}

static void setEtbIFactor(float value) {
	engineConfiguration->etb.iFactor = value;
	apply();
	showEthInfo();
}

void setDefaultEtbParameters(void) {
	engineConfiguration->pedalPositionMax = 6;
	engineConfiguration->etb.pFactor = 1;
	engineConfiguration->etb.iFactor = 0.5;
	boardConfiguration->etbDT = 100;
}

void initElectronicThrottle(void) {
	// these two lines are controlling direction
//	outputPinRegister("etb1", ELECTRONIC_THROTTLE_CONTROL_1, ETB_CONTROL_LINE_1_PORT, ETB_CONTROL_LINE_1_PIN);
//	outputPinRegister("etb2", ELECTRONIC_THROTTLE_CONTROL_2, ETB_CONTROL_LINE_2_PORT, ETB_CONTROL_LINE_2_PIN);

	if (!hasPedalPositionSensor()) {
		return;
	}

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

	outputPinRegisterExt2("etb dir open", &outputDirectionOpen, boardConfiguration->etbDirectionPin1, &DEFAULT_OUTPUT);
	outputPinRegisterExt2("etb dir close", &outputDirectionClose, boardConfiguration->etbDirectionPin2, &DEFAULT_OUTPUT);

	addConsoleActionI("e", setThrottleConsole);

	addConsoleAction("ethinfo", showEthInfo);

	addConsoleActionF("set_etb_p", setEtbPFactor);
	addConsoleActionF("set_etb_i", setEtbIFactor);

	apply();

	chThdCreateStatic(etbTreadStack, sizeof(etbTreadStack), NORMALPRIO, (tfunc_t) etbThread, NULL);
}

#endif /* EFI_ELECTRONIC_THROTTLE_BODY */

