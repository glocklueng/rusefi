/*
 * pwm_generator.c
 *
 *  Created on: May 28, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "pwm_generator.h"

#include "pin_repository.h"
#include "wave_math.h"

static void weSetState(PwmWave *state, int value) {
	if (state->currentPinState != value) {
		int now = chTimeNow();
		if (value)
			state->zeroToOneTime = now;
		else
			state->oneToZeroTime = now;

		palWritePad(state->port, state->pin, value ^ state->idleState);
		state->currentPinState = value;
	}
}

static msg_t deThread(PwmWave *state) {
	chRegSetThreadName("Wave");

	int iteration;

	weSetState(state, state->idleState);
	// todo: figure out overflow
	systime_t start;
	myfloat rpmHere = -1;

	while (TRUE) {
		if (state->waveLen == 0) {
			chThdSleep(100);
			continue;
		}

		if (rpmHere != state->waveLen) {
			start = chTimeNow();
			iteration = 0;
			rpmHere = state->waveLen;
		}

		// local copy so that both phases are executed on the same len
		myfloat waveLen = state->waveLen;

		systime_t timeToSwitch = (systime_t) ((iteration + state->rights[0])
				* waveLen);
		chThdSleepUntil(start + timeToSwitch);
		weSetState(state, !state->idleState);

		timeToSwitch = (systime_t) ((iteration + 1) * waveLen);
		chThdSleepUntil(start + timeToSwitch);
		weSetState(state, state->idleState);

		iteration++;
	}
}

void initModulation(PwmWave *state, int count, myfloat *lefts,
		myfloat *rights) {
	for (int i = 0; i < count; i++) {
		print("output wave (%d) from %f to %f\r\n", i, lefts[i], rights[i]);
		state->lefts[i] = lefts[i];
		state->rights[i] = rights[i];
	}
}

void wePlainInit(char *msg, PwmWave *state, GPIO_TypeDef * port, int pin,
		int idleState, myfloat left, myfloat right) {
	myfloat lefts[] = { left };
	myfloat rights[] = { right };
	weComplexInit(msg, state, port, pin, idleState, 1, lefts, rights);
}

void weComplexInit(char *msg, PwmWave *state, GPIO_TypeDef * port, int pin,
		int idleState, int count, myfloat *lefts, myfloat *rights) {
	mySetPadMode(msg, port, pin, PAL_MODE_OUTPUT_PUSHPULL);

	chDbgCheck(count <= PWM_PHASE_MAX_COUNT, "count is too large");

	state->waveLen = freq2wave(10);
	initModulation(state, count, lefts, rights);
	state->currentPinState = -1;
	state->port = port;
	state->pin = pin;
	state->idleState = idleState;
	state->rangeCount = count;
	chThdCreateStatic(state->deThreadStack, sizeof(state->deThreadStack),
			NORMALPRIO, deThread, state);
}

