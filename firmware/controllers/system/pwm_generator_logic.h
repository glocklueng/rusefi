/**
 * @file    pwm_generator_logic.h
 *
 * @date Mar 2, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef PWM_GENERATOR_LOGIC_H_
#define PWM_GENERATOR_LOGIC_H_

#include "global.h"
#include "trigger_structure.h"
#include "io_pins.h"
#include "signal_executor.h"

typedef struct {
	/**
	 * a copy so that all phases are executed on the same period, even if another thread
	 * would be adjusting PWM parameters
	 */
	float periodMs;
	/**
	 * Iteration counter
	 */
	int iteration;
	/**
	 * Start time of current iteration
	 */
	uint64_t startUs;
	int phaseIndex;
} pwm_config_safe_state_s;

class PwmConfig;

typedef void (pwm_cycle_callback)(PwmConfig *state);
typedef void (pwm_gen_callback)(PwmConfig *state, int stateIndex);


/**
 * @brief   Multi-channel software PWM output configuration
 */
class PwmConfig {
public:
	PwmConfig(float *st);
	io_pin_e outputPins[PWM_PHASE_MAX_WAVE_PER_PWM];
	multi_wave_s multiWave;
	char *name;
	/**
	 * float value of PWM period
	 * PWM generation is not happening while this value is zero
	 */
	float periodMs;

	scheduling_s scheduling;

	single_wave_s waves[2];
	single_wave_s sr[2] = {waves[0], waves[1]};

	pwm_config_safe_state_s safe;

	/**
	 * this callback is invoked before each wave generation cycle
	 */
	pwm_cycle_callback *cycleCallback;

	/**
	 * this main callback is invoked when it's time to switch level on amy of the output channels
	 */
	pwm_gen_callback *stateChangeCallback;
};

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

void copyPwmParameters(PwmConfig *state, int phaseCount, float *switchTimes,
		int waveCount, int **pinStates);

void weComplexInit(char *msg, PwmConfig *state,
		int phaseCount, float *swithcTimes, int waveCount, int **pinStates,
		pwm_cycle_callback *cycleCallback,
		pwm_gen_callback *callback);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* PWM_GENERATOR_LOGIC_H_ */
