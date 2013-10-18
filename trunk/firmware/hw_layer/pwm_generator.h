/*
 * pwm_generator.h
 *
 *  Created on: May 28, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef PWM_GENERATOR_H_
#define PWM_GENERATOR_H_

#include "global.h"


#define PWM_PHASE_MAX_COUNT 150

#define PWM_PHASE_MAX_WAVE_PER_PWM 2

#define FREQ_MATH_FREQUENCY CH_FREQUENCY

#include "gpio_helper.h"


/**
 * @brief   PWM configuration for the specific output pin
 */
typedef struct {
	OutputPin outputPin;
	int pinStates[PWM_PHASE_MAX_COUNT];
} SingleWave;

/**
 * @brief   Multi-channel software PWM output configuration
 */
typedef struct {
	SingleWave waves[PWM_PHASE_MAX_WAVE_PER_PWM];
	int waveCount;
	int idleState;
	int phaseCount;
	char *name;
	/**
	 * values in the (0..1] range which refer to points within the period at at which pin state should be changed
	 * So, in the simplest case we turn pin off at 0.3 and turn it on at 1 - that would give us a 70% duty cycle PWM
	 */
	volatile myfloat switchTimes[PWM_PHASE_MAX_COUNT];
	/**
	 * float value of PWM period
	 * PWM generation is not happening while this value is zero
	 */
	myfloat period;
	WORKING_AREA(deThreadStack, 256);
} PwmConfig;

void initModulation(PwmConfig *state, int count, myfloat *switchTimes,
		int *pinStates);

void wePlainInit(char *msg, PwmConfig *state, GPIO_TypeDef * port, int pin,
		int idleState, myfloat dutyCycle);
void weComplexInit(char *msg, PwmConfig *state,
		int idleState, int phaseCount, myfloat *swithcTimes, int waveCount, int **pinStates);

#endif /* PWM_GENERATOR_H_ */
