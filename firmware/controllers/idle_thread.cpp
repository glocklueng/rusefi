/**
 * @file    idle_thread.cpp
 * @brief   Idle Air Control valve thread.
 *
 * This thread looks at current RPM and decides if it should increase or decrease IAC duty cycle.
 * This file is has the hardware & scheduling logic, desired idle level lives separately
 *
 *
 * @date May 23, 2013
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
 *
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

// todo: extract interface for idle valve hardware, with solenoid and stepper implementations?
static OutputPin idleSolenoidPin;
static SimplePwm idleSolenoid;

static StepperMotor iacMotor;

/**
 * that's the position with CLT and IAT corrections
 */
static float actualIdlePosition = -100.0f;

/**
 * Idle level calculation algorithm lives in idle_controller.cpp
 * todo: replace this with a PID regulator?
 */
static IdleValveState idlePositionController;

void idleDebug(const char *msg, percent_t value) {
	scheduleMsg(logger, "idle debug: %s%f", msg, value);
}

static void showIdleInfo(void) {
	scheduleMsg(logger, "idleMode=%s position=%f isStepper=%s", getIdle_mode_e(engineConfiguration->idleMode),
			getIdlePosition(), boolToString(boardConfiguration->useStepperIdle));
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
	scheduleMsg(logger, "idleControl=%s", getIdle_control_e(engineConfiguration->idleControl));
	scheduleMsg(logger, "idle P=%f I=%f D=%f dT=%d", engineConfiguration->idleRpmPid.pFactor,
			engineConfiguration->idleRpmPid.iFactor,
			engineConfiguration->idleRpmPid.dFactor,
			engineConfiguration->idleDT);
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

static void manualIdleController(int positionPercent) {
	// todo: this is not great that we have to write into configuration here
	boardConfiguration->manIdlePosition = positionPercent;

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
	manualIdleController(positionPercent);
}

static int idlePositionBeforeBlip;
static efitimeus_t timeToStopBlip = 0;
static efitimeus_t timeToStopIdleTest = 0;

/**
 * I use this questionable feature to tune acceleration enrichment
 */
static void blipIdle(int idlePosition, int durationMs) {
	// todo: add 'blip' feature for automatic target control
	if (timeToStopBlip != 0) {
		return; // already in idle blip
	}
	idlePositionBeforeBlip = boardConfiguration->manIdlePosition;
	setIdleValvePosition(idlePosition);
	timeToStopBlip = getTimeNowUs() + 1000 * durationMs;
}

static void finishIdleTestIfNeeded() {
	if (timeToStopIdleTest != 0 && getTimeNowUs() > timeToStopIdleTest)
		timeToStopIdleTest = 0;
}

static void undoIdleBlipIfNeeded() {
	if (timeToStopBlip != 0 && getTimeNowUs() > timeToStopBlip) {
		timeToStopBlip = 0;
		setIdleValvePosition(idlePositionBeforeBlip);
	}
}

static percent_t currentIdleValve = -1;

percent_t getIdlePosition(void) {
	if (engineConfiguration->idleMode == IM_AUTO) {
		return currentIdleValve;
	} else {
		return boardConfiguration->manIdlePosition;
	}
}

static msg_t ivThread(int param) {
	(void) param;
	chRegSetThreadName("IdleValve");

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

		finishIdleTestIfNeeded();
		undoIdleBlipIfNeeded();

		if (engineConfiguration->idleMode != IM_AUTO) {
			// let's re-apply CLT correction
			manualIdleController(boardConfiguration->manIdlePosition);
			continue;
		}

		efitimems_t now = currentTimeMillis();

		percent_t newValue = idlePositionController.getIdle(getRpmE(engine), now PASS_ENGINE_PARAMETER);

		if (currentIdleValve != newValue) {
			currentIdleValve = newValue;

			// todo: looks like in auto mode stepper value is not set, only solenoid?

			setIdleValvePwm(newValue);
		}
	}
#if defined __GNUC__
	return -1;
#endif
}

static void setTargetRpm(int value) {
	idlePositionController.setTargetRpm(value);
	scheduleMsg(logger, "target idle RPM %d", value);
}

static void apply(void) {
//	idleMath.updateFactors(engineConfiguration->idlePFactor, engineConfiguration->idleIFactor, engineConfiguration->idleDFactor, engineConfiguration->idleDT);
}

static void setIdlePFactor(float value) {
	engineConfiguration->idleRpmPid.pFactor = value;
	apply();
	showIdleInfo();
}

static void setIdleIFactor(float value) {
	engineConfiguration->idleRpmPid.iFactor = value;
	apply();
	showIdleInfo();
}

static void setIdleDFactor(float value) {
	engineConfiguration->idleRpmPid.dFactor = value;
	apply();
	showIdleInfo();
}

static void setIdleDT(int value) {
	engineConfiguration->idleDT = value;
	apply();
	showIdleInfo();
}

static void startIdleBench(void) {
	timeToStopIdleTest = getTimeNowUs() + MS2US(3000); // 3 seconds
	scheduleMsg(logger, "idle valve bench test");
	showIdleInfo();
}

void setDefaultIdleParameters(void) {
	engineConfiguration->idleRpmPid.pFactor = 0.1f;
	engineConfiguration->idleRpmPid.iFactor = 0.05f;
	engineConfiguration->idleRpmPid.dFactor = 0.0f;
	engineConfiguration->idleDT = 10;
}

static void applyIdleSolenoidPinState(PwmConfig *state, int stateIndex) {
	efiAssertVoid(stateIndex < PWM_PHASE_MAX_COUNT, "invalid stateIndex");
	efiAssertVoid(state->multiWave.waveCount == 1, "invalid idle waveCount");
	OutputPin *output = state->outputPins[0];
	int value = state->multiWave.waves[0].pinStates[stateIndex];
	if (!value /* always allow turning solenoid off */ ||
			(engine->rpmCalculator.rpmValue != 0 || timeToStopIdleTest != 0) /* do not run solenoid unless engine is spinning or bench testing in progress */
			) {
		output->setValue(value);
	}
}

static void initIdleHardware() {
	if (boardConfiguration->useStepperIdle) {
		iacMotor.initialize(boardConfiguration->idle.stepperStepPin, boardConfiguration->idle.stepperDirectionPin,
				engineConfiguration->idleStepperReactionTime, engineConfiguration->idleStepperTotalSteps,
				engineConfiguration->stepperEnablePin);
	} else {
		/**
		 * Start PWM for idleValvePin
		 */
		startSimplePwmExt(&idleSolenoid, "Idle Valve", boardConfiguration->idle.solenoidPin, &idleSolenoidPin,
				boardConfiguration->idle.solenoidFrequency, boardConfiguration->manIdlePosition / 100,
				applyIdleSolenoidPinState);
	}
}

void startIdleThread(Logging*sharedLogger, Engine *engine) {
	logger = sharedLogger;

	// todo: re-initialize idle pins on the fly
	initIdleHardware();

	idlePositionController.init();
	scheduleMsg(logger, "initial idle %d", idlePositionController.value);

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

	addConsoleActionI("set_idle_position", setIdleValvePosition);

	addConsoleActionI("set_idle_enabled", (VoidInt) setIdleControlEnabled);

	addConsoleActionII("blipidle", blipIdle);

	// split this whole file into manual controller and auto controller? move these commands into the file
	// which would be dedicated to just auto-controller?
	addConsoleActionI("set_idle_rpm", setTargetRpm);
	addConsoleActionF("set_idle_p", setIdlePFactor);
	addConsoleActionF("set_idle_i", setIdleIFactor);
	addConsoleActionF("set_idle_d", setIdleDFactor);
	addConsoleActionI("set_idle_dt", setIdleDT);

	addConsoleAction("idlebench", startIdleBench);
	apply();
}

#endif
