/**
 * @file    idle_thread.cpp
 * @brief   Idle Air Control valve thread.
 *
 * This thread looks at current RPM and decides if it should increase or decrease IAC duty cycle.
 * This file is has the hardware & scheduling logic, desired idle level lives separately
 *
 *
 * @date May 23, 2013
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
#include "idle_controller.h"
#include "rpm_calculator.h"
#include "pwm_generator.h"
#include "idle_thread.h"
#include "pin_repository.h"
#include "engine_configuration.h"
#include "engine.h"
#include "stepper.h"

#if EFI_IDLE_CONTROL || defined(__DOXYGEN__)

static THD_WORKING_AREA(ivThreadStack, UTILITY_THREAD_STACK_SIZE);

static Logging *logger;
EXTERN_ENGINE
;

static OutputPin idleSolenoidPin;
static SimplePwm idleSolenoid;

static StepperMotor iacMotor;

/**
 * that's the position with CLT and IAT corrections
 */
static float actualIdlePosition = -100.0f;

/**
 * Idle level calculation algorithm lives in idle_controller.cpp
 */
static IdleValveState idleMath;

void idleDebug(const char *msg, percent_t value) {
	scheduleMsg(logger, "%s%f", msg, value);
}

static void showIdleInfo(void) {
	scheduleMsg(logger, "idleMode=%s position=%f isStepper=%s", getIdle_mode_e(engineConfiguration->idleMode),
			boardConfiguration->idlePosition, boolToString(boardConfiguration->useStepperIdle));
	if (boardConfiguration->useStepperIdle) {
		scheduleMsg(logger, "direction=%s reactionTime=%f", hwPortname(boardConfiguration->idle.stepperDirectionPin),
				engineConfiguration->idleStepperReactionTime);
		scheduleMsg(logger, "step=%s steps=%d", hwPortname(boardConfiguration->idle.stepperStepPin),
				engineConfiguration->idleStepperTotalSteps);
		scheduleMsg(logger, "enable=%s", hwPortname(engineConfiguration->stepperEnablePin));
	} else {
		scheduleMsg(logger, "idle valve freq=%d on %s", boardConfiguration->idle.solenoidFrequency,
				hwPortname(boardConfiguration->idle.solenoidPin));
	}
}

static void setIdleControlEnabled(int value) {
	engineConfiguration->idleMode = value ? IM_AUTO : IM_MANUAL;
	showIdleInfo();
}

static void setIdleValvePwm(percent_t value) {
	/**
	 * currently idle level is an percent value (0-100 range), and PWM takes a float in the 0..1 range
	 * todo: unify?
	 */
	idleSolenoid.setSimplePwmDutyCycle(value / 100);
}

static void doSetIdleValvePosition(int positionPercent) {
	boardConfiguration->idlePosition = positionPercent;

	percent_t cltCorrectedPosition = interpolate2d(engine->engineState.clt, config->cltIdleCorrBins, config->cltIdleCorr,
	CLT_CURVE_SIZE) * positionPercent;

	// let's put the value into the right range
	cltCorrectedPosition = maxF(cltCorrectedPosition, 0.01);
	cltCorrectedPosition = minF(cltCorrectedPosition, 99.9);

	if (absF(cltCorrectedPosition - actualIdlePosition) < 1) {
		return; // value is pretty close, let's leave the poor valve alone
	}
	actualIdlePosition = cltCorrectedPosition;

	if (boardConfiguration->useStepperIdle) {
		iacMotor.setTargetPosition(cltCorrectedPosition / 100 * engineConfiguration->idleStepperTotalSteps);
	} else {
		setIdleValvePwm(cltCorrectedPosition);
	}
}

static void setIdleValvePosition(int positionPercent) {
	if (positionPercent < 1 || positionPercent > 99)
		return;
	scheduleMsg(logger, "setting idle valve position %d", positionPercent);
	showIdleInfo();
	doSetIdleValvePosition(positionPercent);
}

static msg_t ivThread(int param) {
	(void) param;
	chRegSetThreadName("IdleValve");

	percent_t currentIdleValve = -1;
	while (true) {
		chThdSleepMilliseconds(boardConfiguration->idleThreadPeriod);

		// this value is not used yet
		if (boardConfiguration->clutchDownPin != GPIO_UNASSIGNED) {
			engine->clutchDownState = palReadPad(getHwPort(boardConfiguration->clutchDownPin),
					getHwPin(boardConfiguration->clutchDownPin));
		}
		if (boardConfiguration->clutchUpPin != GPIO_UNASSIGNED) {
			engine->clutchUpState = palReadPad(getHwPort(boardConfiguration->clutchUpPin),
					getHwPin(boardConfiguration->clutchUpPin));
		}

		if (engineConfiguration->idleMode != IM_AUTO) {
			// let's re-apply CLT correction
			doSetIdleValvePosition(boardConfiguration->idlePosition);
			continue;
		}

		efitimems_t now = currentTimeMillis();

		percent_t newValue = idleMath.getIdle(getRpm(), now PASS_ENGINE_PARAMETER);

		if (currentIdleValve != newValue) {
			currentIdleValve = newValue;

			setIdleValvePwm(newValue);
		}
	}
#if defined __GNUC__
	return -1;
#endif
}

static void setIdleRpmAction(int value) {
	idleMath.setTargetRpm(value);
	scheduleMsg(logger, "target idle RPM %d", value);
}

static void applyIdleSolenoidPinState(PwmConfig *state, int stateIndex) {
	efiAssertVoid(stateIndex < PWM_PHASE_MAX_COUNT, "invalid stateIndex");
	efiAssertVoid(state->multiWave.waveCount == 1, "invalid idle waveCount");
	OutputPin *output = state->outputPins[0];
	int value = state->multiWave.waves[0].pinStates[stateIndex];
	if (!value || engine->rpmCalculator.rpmValue != 0)
		output->setValue(value);
}

void startIdleThread(Logging*sharedLogger, Engine *engine) {
	logger = sharedLogger;

	if (boardConfiguration->useStepperIdle) {
		iacMotor.initialize(boardConfiguration->idle.stepperStepPin, boardConfiguration->idle.stepperDirectionPin,
				engineConfiguration->idleStepperReactionTime, engineConfiguration->idleStepperTotalSteps,
				engineConfiguration->stepperEnablePin);
	} else {
		/**
		 * Start PWM for idleValvePin
		 */
		startSimplePwmExt(&idleSolenoid, "Idle Valve", boardConfiguration->idle.solenoidPin, &idleSolenoidPin,
				boardConfiguration->idle.solenoidFrequency, boardConfiguration->idlePosition / 100,
				applyIdleSolenoidPinState);
	}

	idleMath.init();
	scheduleMsg(logger, "initial idle %d", idleMath.value);

	chThdCreateStatic(ivThreadStack, sizeof(ivThreadStack), NORMALPRIO, (tfunc_t) ivThread, NULL);

	// this is idle switch INPUT - sometimes there is a switch on the throttle pedal
	// this switch is not used yet
	if (boardConfiguration->clutchDownPin != GPIO_UNASSIGNED)
		mySetPadMode2("clutch down switch", boardConfiguration->clutchDownPin,
				getInputMode(boardConfiguration->clutchDownPinMode));

	if (boardConfiguration->clutchUpPin != GPIO_UNASSIGNED)
		mySetPadMode2("clutch up switch", boardConfiguration->clutchUpPin,
				getInputMode(boardConfiguration->clutchUpPinMode));

	addConsoleAction("idleinfo", showIdleInfo);
	addConsoleActionI("set_idle_rpm", setIdleRpmAction);

	addConsoleActionI("set_idle_position", setIdleValvePosition);

	addConsoleActionI("set_idle_enabled", (VoidInt) setIdleControlEnabled);
}

#endif
