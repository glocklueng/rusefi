/**
 * @file	EfiWave.h
 *
 * @date May 18, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */
#ifndef EFI_WAVE_H_
#define EFI_WAVE_H_

#include "engine_configuration.h"

#define PWM_PHASE_MAX_COUNT 250
#define PWM_PHASE_MAX_WAVE_PER_PWM 2

/**
 * @brief   PWM configuration for the specific output pin
 */
class single_wave_s {
public:
	single_wave_s();
	single_wave_s(int *pinStates);
	void init(int *pinStates);
	int *pinStates;
};

class trigger_shape_s;

class multi_wave_s {
public:
	multi_wave_s();
	multi_wave_s(float *st, single_wave_s *waves);
	void init(float *st, single_wave_s *waves);
	void reset(void);
	float getSwitchTime(int phaseIndex) const;
	void setSwitchTime(int phaseIndex, float value);
	void checkSwitchTimes(int size);
	int getChannelState(int channelIndex, int phaseIndex) const;
	/**
	 * Number of signal wires
	 */
	int waveCount;
	single_wave_s *waves;
//private:
	/**
	 * values in the (0..1] range which refer to points within the period at at which pin state should be changed
	 * So, in the simplest case we turn pin off at 0.3 and turn it on at 1 - that would give us a 70% duty cycle PWM
	 */
	float *switchTimes;
};

void checkSwitchTimes2(int size, float *switchTimes);

#endif /* EFI_WAVE_H_ */
