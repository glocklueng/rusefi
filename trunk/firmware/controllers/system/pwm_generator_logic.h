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
	float period;
	/**
	 * Iteration counter
	 */
	int iteration;
	/**
	 * Start time of current iteration
	 */
	systime_t start;
	int phaseIndex;
} pwm_config_safe_state_s;

typedef struct PwmConfig_struct PwmConfig;

typedef void (pwm_gen_callback)(PwmConfig *state, int stateIndex);

/**
 * @brief   Multi-channel software PWM output configuration
 */
struct PwmConfig_struct {
	io_pin_e outputPins[PWM_PHASE_MAX_WAVE_PER_PWM];
	multi_wave_s multiWave;
	char *name;
	/**
	 * float value of PWM period
	 * PWM generation is not happening while this value is zero
	 */
	float period;

	WORKING_AREA(deThreadStack, UTILITY_THREAD_STACK_SIZE);
	scheduling_s scheduling;

	pwm_config_safe_state_s safe;

	pwm_gen_callback *changeStateCallback;
};

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

void weComplexInit(char *msg, PwmConfig *state,
		int phaseCount, float *swithcTimes, int waveCount, int **pinStates, pwm_gen_callback *callback);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* PWM_GENERATOR_LOGIC_H_ */
