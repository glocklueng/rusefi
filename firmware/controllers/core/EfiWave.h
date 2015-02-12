/**
 * @file	EfiWave.h
 *
 * @date May 18, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */
#ifndef EFI_WAVE_H_
#define EFI_WAVE_H_

#include "engine_configuration.h"

/**
 * this value should be dividable by four, see FuelSchedule.hasEvents
 */
#define PWM_PHASE_MAX_COUNT 252
#define PWM_PHASE_MAX_WAVE_PER_PWM 3

/**
 * int8_t is probably less efficient then int32_t but we need
 * to reduce memory footprint
 *
 * todo: migrate to bit-array to same memory? but this would
 * this would some CPU cycles. see std::vector<bool>
 */
typedef int8_t pin_state_t;

/**
 * @brief   PWM configuration for the specific output pin
 */
class single_wave_s {
public:
	single_wave_s();
	single_wave_s(pin_state_t *pinStates);
	void init(pin_state_t *pinStates);
	pin_state_t *pinStates;
};

class TriggerShape;

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

	int findAngleMatch(float angle, int size) const;
	int waveIndertionAngle(float angle, int size) const;

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
void configureHondaAccordCD(TriggerShape *s, bool with3rdSignal);
void configureHondaAccordCDDip(TriggerShape *s);

#endif /* EFI_WAVE_H_ */
