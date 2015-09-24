/*
 * @file trigger_simulator.cpp
 *
 * @date Sep 23, 2015
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "main.h"
#include "engine.h"
#include "trigger_simulator.h"

#define SIMULATION_CYCLE_PERIOD 720000

EXTERN_ENGINE;

TriggerStimulatorHelper::TriggerStimulatorHelper() {
}

void TriggerStimulatorHelper::nextStep(TriggerState *state, TriggerShape * shape, int i,
		trigger_config_s const*triggerConfig DECLARE_ENGINE_PARAMETER_S) {
	int stateIndex = i % shape->getSize();
	int prevIndex = (stateIndex + shape->getSize() - 1 ) % shape->getSize();


	int loopIndex = i / shape->getSize();

	int time = (int) (SIMULATION_CYCLE_PERIOD * (loopIndex + shape->wave.getSwitchTime(stateIndex)));

	bool_t primaryWheelState = shape->wave.getChannelState(0, prevIndex);
	bool_t newPrimaryWheelState = shape->wave.getChannelState(0, stateIndex);

	bool_t secondaryWheelState = shape->wave.getChannelState(1, prevIndex);
	bool_t newSecondaryWheelState = shape->wave.getChannelState(1, stateIndex);

	bool_t thirdWheelState = shape->wave.getChannelState(2, prevIndex);
	bool_t new3rdWheelState = shape->wave.getChannelState(2, stateIndex);

	if (primaryWheelState != newPrimaryWheelState) {
		primaryWheelState = newPrimaryWheelState;
		trigger_event_e s = primaryWheelState ? SHAFT_PRIMARY_UP : SHAFT_PRIMARY_DOWN;
		state->decodeTriggerEvent(s, time PASS_ENGINE_PARAMETER);
	}

	if (secondaryWheelState != newSecondaryWheelState) {
		secondaryWheelState = newSecondaryWheelState;
		trigger_event_e s = secondaryWheelState ? SHAFT_SECONDARY_UP : SHAFT_SECONDARY_DOWN;
		state->decodeTriggerEvent(s, time PASS_ENGINE_PARAMETER);
	}

	if (thirdWheelState != new3rdWheelState) {
		thirdWheelState = new3rdWheelState;
		trigger_event_e s = thirdWheelState ? SHAFT_3RD_UP : SHAFT_3RD_DOWN;
		state->decodeTriggerEvent(s, time PASS_ENGINE_PARAMETER);
	}
}

void TriggerStimulatorHelper::assertSyncPositionAndSetDutyCycle(uint32_t index, TriggerState *state, TriggerShape * shape,
		trigger_config_s const*triggerConfig DECLARE_ENGINE_PARAMETER_S) {
	int startIndex = engineConfiguration->useOnlyFrontForTrigger ? index + 2 : index + 1;

	for (uint32_t i = startIndex; i <= index + 2 * shape->getSize(); i++) {
		nextStep(state, shape, i, triggerConfig PASS_ENGINE_PARAMETER);
		if (engineConfiguration->useOnlyFrontForTrigger)
			i++;
	}
	// todo: nicer error handling?
	efiAssertVoid(state->getTotalRevolutionCounter() == 3, "totalRevolutionCounter2 expected 3");

	for (int i = 0; i < PWM_PHASE_MAX_WAVE_PER_PWM; i++) {
		shape->dutyCycle[i] = 1.0 * state->expectedTotalTime[i] / SIMULATION_CYCLE_PERIOD;
	}
}

uint32_t TriggerStimulatorHelper::doFindTrigger(TriggerShape * shape,
		trigger_config_s const*triggerConfig, TriggerState *state DECLARE_ENGINE_PARAMETER_S) {
	for (int i = 0; i < 4 * PWM_PHASE_MAX_COUNT; i++) {
		nextStep(state, shape, i, triggerConfig PASS_ENGINE_PARAMETER);

		if (state->shaft_is_synchronized)
			return i;
	}
	firmwareError("findTriggerZeroEventIndex() failed");
	return EFI_ERROR_CODE;
}
