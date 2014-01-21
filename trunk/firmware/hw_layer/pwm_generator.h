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

#include "gpio_helper.h"
#include "io_pins.h"

/**
 * @brief   Multi-channel software PWM output configuration
 */
typedef struct {
	io_pin_e outputPins[PWM_PHASE_MAX_WAVE_PER_PWM];
	multi_wave_s multiWave;
	char *name;
	/**
	 * float value of PWM period
	 * PWM generation is not happening while this value is zero
	 */
	myfloat period;
	WORKING_AREA(deThreadStack, UTILITY_THREAD_STACK_SIZE);
} PwmConfig;

void initModulation(PwmConfig *state, int count, myfloat *switchTimes,
		int *pinStates);

void wePlainInit(char *msg, PwmConfig *state, GPIO_TypeDef * port, int pin,
		myfloat dutyCycle, myfloat freq, io_pin_e ioPin);
void weComplexInit(char *msg, PwmConfig *state,
		int phaseCount, myfloat *swithcTimes, int waveCount, int **pinStates);

#endif /* PWM_GENERATOR_H_ */
