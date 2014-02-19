/**
 * @file	trigger_structure.c
 *
 * @date Jan 20, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "trigger_structure.h"

void clearTriggerState(trigger_state_s *state) {
	state->shaft_is_synchronized = FALSE;
	state->toothed_previous_time = 0;
	state->toothed_previous_duration = 0;
	state->current_index = 0;
}

void triggerShapeInit(trigger_shape_s *trigger) {
	trigger->size = 0;
}

void triggerAddEvent(trigger_shape_s *trigger, float angle, trigger_wheel_e waveIndex, trigger_value_e state) {
	angle /= 720;
	if (trigger->size == 0) {
		trigger->size = 1;
		for (int i = 0; i < PWM_PHASE_MAX_WAVE_PER_PWM; i++)
			trigger->wave.waves[i].pinStates[0] = 0;

		trigger->wave.switchTimes[0] = angle;
		trigger->wave.waves[waveIndex].pinStates[0] = state;
		return;
	}

//	if(angle!=trigger->wave.switchTimes[trigger->currentIndex])

	int index = trigger->size++;

	for (int i = 0; i < PWM_PHASE_MAX_WAVE_PER_PWM; i++)
		trigger->wave.waves[i].pinStates[index] = trigger->wave.waves[i].pinStates[index - 1];
	trigger->wave.switchTimes[index] = angle;
	trigger->wave.waves[waveIndex].pinStates[index] = state;
}

void checkSwitchTimes(int size, myfloat *switchTimes) {
	for (int i = 0; i < size - 1; i++)
		chDbgCheck(switchTimes[i] < switchTimes[i + 1], "invalid switchTimes");
}
