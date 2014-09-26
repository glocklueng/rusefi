/**
 * @file trigger_emulator_algo.cpp
 *
 * @date Mar 3, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */
#include "main.h"
#include "trigger_emulator_algo.h"
#include "engine_configuration.h"
#include "LocalVersionHolder.h"
#include "ec2.h"
#include "trigger_central.h"

#if EFI_PROD_CODE
#include "pwm_generator.h"
#endif

TriggerEmulatorHelper::TriggerEmulatorHelper() {
	primaryWheelState = false;
	secondaryWheelState = false;
	thirdWheelState = false;
}

void TriggerEmulatorHelper::handleEmulatorCallback(PwmConfig *state, int stateIndex) {
	int newPrimaryWheelState = state->multiWave.waves[0].pinStates[stateIndex];
	int newSecondaryWheelState = state->multiWave.waves[1].pinStates[stateIndex];
	int new3rdWheelState = state->multiWave.waves[2].pinStates[stateIndex];

	if (primaryWheelState != newPrimaryWheelState) {
		primaryWheelState = newPrimaryWheelState;
		hwHandleShaftSignal(primaryWheelState ? SHAFT_PRIMARY_UP : SHAFT_PRIMARY_DOWN);
	}

	if (secondaryWheelState != newSecondaryWheelState) {
		secondaryWheelState = newSecondaryWheelState;
		hwHandleShaftSignal(secondaryWheelState ? SHAFT_SECONDARY_UP : SHAFT_SECONDARY_DOWN);
	}

	if (thirdWheelState != new3rdWheelState) {
		thirdWheelState = new3rdWheelState;
		hwHandleShaftSignal(thirdWheelState ? SHAFT_3RD_UP : SHAFT_3RD_DOWN);
	}

	//	print("hello %d\r\n", chTimeNow());
}


extern engine_configuration_s *engineConfiguration;
extern engine_configuration2_s *engineConfiguration2;

/*
 * todo: should we simply re-use instances used by trigger_decoder?
 * todo: since we are emulating same shape we are decoding
 */
static int pinStates1[PWM_PHASE_MAX_COUNT];
static int pinStates2[PWM_PHASE_MAX_COUNT];
static int pinStates3[PWM_PHASE_MAX_COUNT];
static single_wave_s waves[PWM_PHASE_MAX_WAVE_PER_PWM] = {single_wave_s(pinStates1), single_wave_s(pinStates2), single_wave_s(pinStates3)};
static single_wave_s sr[PWM_PHASE_MAX_WAVE_PER_PWM] = {waves[0], waves[1], waves[2]};

static float swtchTms[PWM_PHASE_MAX_COUNT];

PwmConfig triggerSignal(swtchTms, sr);

static Logging logger;
static LocalVersionHolder localVersion;

void setTriggerEmulatorRPM(int rpm) {
	engineConfiguration->bc.triggerSimulatorFrequency = rpm;
	/**
	 * All we need to do here is to change the periodMs
	 * togglePwmState() would see that the periodMs has changed and act accordingly
	 */
	if (rpm == 0) {
		triggerSignal.periodNt = NAN;
	} else {
		float gRpm = rpm * engineConfiguration->rpmMultiplier / 60.0; // per minute converted to per second
		triggerSignal.periodNt = US2NT(frequency2periodUs(gRpm));
	}
	scheduleMsg(&logger, "Emulating position sensor(s). RPM=%d", rpm);
}

static void updateTriggerShapeIfNeeded(PwmConfig *state) {
	if (localVersion.isOld()) {
		scheduleMsg(&logger, "Stimulator: updating trigger shape: %d/%d %d", localVersion.getVersion(), getGlobalConfigurationVersion(), currentTimeMillis());


		applyNonPersistentConfiguration(&logger, engineConfiguration, engineConfiguration2);

		trigger_shape_s *s = &engineConfiguration2->triggerShape;
		int *pinStates[PWM_PHASE_MAX_WAVE_PER_PWM] = {s->wave.waves[0].pinStates, s->wave.waves[1].pinStates, s->wave.waves[2].pinStates};
		copyPwmParameters(state, s->getSize(), s->wave.switchTimes, PWM_PHASE_MAX_WAVE_PER_PWM, pinStates);
		state->safe.periodNt = -1; // this would cause loop re-initialization
	}
}

static TriggerEmulatorHelper helper;

#if EFI_EMULATE_POSITION_SENSORS || defined(__DOXYGEN__)

static void emulatorApplyPinState(PwmConfig *state, int stateIndex) {
#if EFI_PROD_CODE
	applyPinState(state, stateIndex);
#endif /* EFI_PROD_CODE */
	if (engineConfiguration->directSelfStimulation) {
		/**
		 * this callback would invoke the input signal handlers directly
		 */
		helper.handleEmulatorCallback(state, stateIndex);
	}
}
#endif /* EFI_EMULATE_POSITION_SENSORS */


void initTriggerEmulatorLogic(void) {
	initLogging(&logger, "position sensor(s) emulator");

	trigger_shape_s *s = &engineConfiguration2->triggerShape;
	setTriggerEmulatorRPM(engineConfiguration->bc.triggerSimulatorFrequency);
	int *pinStates[PWM_PHASE_MAX_WAVE_PER_PWM] = { s->wave.waves[0].pinStates, s->wave.waves[1].pinStates, s->wave.waves[2].pinStates};
	weComplexInit("position sensor", &triggerSignal, s->getSize(), s->wave.switchTimes, PWM_PHASE_MAX_WAVE_PER_PWM, pinStates,
			updateTriggerShapeIfNeeded, emulatorApplyPinState);

	addConsoleActionI("rpm", &setTriggerEmulatorRPM);

}
