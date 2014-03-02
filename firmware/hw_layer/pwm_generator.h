/**
 * @file pwm_generator.h
 *
 * @date May 28, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef PWM_GENERATOR_H_
#define PWM_GENERATOR_H_

#include "global.h"

#include "trigger_structure.h"

#define FREQ_MATH_FREQUENCY CH_FREQUENCY

#define DEBUG_PWM FALSE

#include "gpio_helper.h"
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

	void (*changeStateCallback)(PwmConfig *state, int stateIndex);

};

void initPwmGenerator(void);
void wePlainInit(char *msg, PwmConfig *state, GPIO_TypeDef * port, int pin,
		float dutyCycle, float freq, io_pin_e ioPin);
void weComplexInit(char *msg, PwmConfig *state,
		int phaseCount, float *swithcTimes, int waveCount, int **pinStates);

#endif /* PWM_GENERATOR_H_ */
