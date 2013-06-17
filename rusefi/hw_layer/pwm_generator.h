/*
 * pwm_generator.h
 *
 *  Created on: May 28, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef PWM_GENERATOR_H_
#define PWM_GENERATOR_H_

#include "main.h"

#define PWM_PHASE_MAX_COUNT 4

#define FREQ_MATH_FREQUENCY CH_FREQUENCY

typedef struct {
	int currentPinState;
	volatile int zeroToOneTime;
	volatile int oneToZeroTime;
	GPIO_TypeDef * port;
	int pin;
	int idleState;
	int rangeCount;
	volatile myfloat lefts[PWM_PHASE_MAX_COUNT];
	volatile myfloat rights[PWM_PHASE_MAX_COUNT];
	myfloat waveLen;
	WORKING_AREA(deThreadStack, 256);
} PwmWave;

void initModulation(PwmWave *state, int count, myfloat *lefts, myfloat *rights);

void wePlainInit(char *msg, PwmWave *state, GPIO_TypeDef * port, int pin,
		int idleState, myfloat left, myfloat right);
void weComplexInit(char *msg, PwmWave *state, GPIO_TypeDef * port, int pin,
		int idleState, int count, myfloat *lefts, myfloat *rights);

#endif /* PWM_GENERATOR_H_ */
