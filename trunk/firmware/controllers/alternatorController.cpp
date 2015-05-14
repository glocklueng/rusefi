/**
 * @file    alternatorController.cpp
 * @brief   alternator controller - turn alternator off if you do not really need it
 *
 * @date Apr 6, 2014
 * @author Dmitry Sidin
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "main.h"
#include "engine.h"
#include "rpm_calculator.h"
#include "pwm_generator.h"
#include "alternatorController.h"
#include "pin_repository.h"
#include "voltage.h"
#include "pid.h"

EXTERN_ENGINE
;

static Logging *logger;

#define ALTERNATOR_VALVE_PWM_FREQUENCY 300

static SimplePwm alternatorControl;
static OutputPin alternatorPin;
static Pid altPid(10, 0, 0, 1, 90);

static THD_WORKING_AREA(alternatorControlThreadStack, UTILITY_THREAD_STACK_SIZE);

static float currentAltDuty;

static msg_t AltCtrlThread(int param) {
	chRegSetThreadName("AlternatorController");
	while (true) {
		chThdSleepMilliseconds(boardConfiguration->alternatorDT);

		currentAltDuty = altPid.getValue(boardConfiguration->targetVBatt, getVBatt(engineConfiguration), 1);
		if (boardConfiguration->isVerboseAlternator) {
			scheduleMsg(logger, "alt duty: %f/vbatt=%f/p=%f/i=%f/d=%f int=%f", currentAltDuty, getVBatt(engineConfiguration),
					altPid.getP(), altPid.getI(), altPid.getD(), altPid.getIntegration());
		}

		alternatorControl.setSimplePwmDutyCycle(currentAltDuty / 100);
	}
#if defined __GNUC__
	return -1;
#endif
}

static void applySettings(void) {
	altPid.updateFactors(engineConfiguration->alternatorControlPFactor, 0, 0);
}

static void showAltInfo(void) {
	scheduleMsg(logger, "alt=%s @ %s", boolToString(engineConfiguration->isAlternatorControlEnabled),
			hwPortname(boardConfiguration->alternatorControlPin));
	scheduleMsg(logger, "p=%f/i=%f/d=%f", engineConfiguration->alternatorControlPFactor,
			0, 0); // todo: i & d
	scheduleMsg(logger, "vbatt=%f/duty=%f/target=%f", getVBatt(engineConfiguration), currentAltDuty,
			boardConfiguration->targetVBatt);
}

static void setAltPFactor(float p) {
	engineConfiguration->alternatorControlPFactor = p;
	scheduleMsg(logger, "setAltPid: %f", p);
	applySettings();
	showAltInfo();
}

static void applyAlternatorPinState(PwmConfig *state, int stateIndex) {
	efiAssertVoid(stateIndex < PWM_PHASE_MAX_COUNT, "invalid stateIndex");
	efiAssertVoid(state->multiWave.waveCount == 1, "invalid idle waveCount");
	OutputPin *output = state->outputPins[0];
	int value = state->multiWave.waves[0].pinStates[stateIndex];
	if (!value || engineConfiguration->isAlternatorControlEnabled)
		output->setValue(value);
}

void initAlternatorCtrl(Logging *sharedLogger) {
	logger = sharedLogger;
	if (boardConfiguration->alternatorControlPin == GPIO_UNASSIGNED)
		return;

	startSimplePwmExt(&alternatorControl, "Alternator control", boardConfiguration->alternatorControlPin,
			&alternatorPin,
			ALTERNATOR_VALVE_PWM_FREQUENCY, 0.1, applyAlternatorPinState);
	chThdCreateStatic(alternatorControlThreadStack, sizeof(alternatorControlThreadStack), LOWPRIO,
			(tfunc_t) AltCtrlThread, NULL);

	addConsoleActionF("set_alt_p", setAltPFactor);
	addConsoleAction("altinfo", showAltInfo);

	applySettings();
}
