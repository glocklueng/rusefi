/**
 * @file    pwm_generator.c
 * @brief   software PWM generator
 *
 * Software PWM implementation. Considering how low all frequencies are, we can totally afford a couple of float multiplications.
 * By generating PWM programmatically we are saving the timers for better purposes. This implementation also supports generating
 * synchronized waves as needed for example to emulate dual Hall-effect crankshaft position sensors.
 *
 *
 * @date May 28, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 *
 */

#include "pwm_generator.h"

#include "pin_repository.h"
#include "wave_math.h"

static msg_t deThread(PwmConfig *state) {
	chRegSetThreadName("Wave");

//	setPadValue(state, state->idleState); todo: currently pin is always zero at first iteration.
// we can live with that for now
	// todo: figure out overflow
	myfloat rpmHere = -1;
	// initial values will be assigned during first state reset
	systime_t start = -1;
	int iteration = -1;

	while (TRUE) {
		if (state->period == 0) {
			/**
			 * zero period means PWM is paused
			 */
			chThdSleepMilliseconds(1);
			continue;
		}

		if (rpmHere != state->period) {
			/**
			 * period length has changed - we need to reset internal state
			 */
			start = chTimeNow();
			iteration = 0;
			rpmHere = state->period;
		}

		/**
		 * local copy so that both phases are executed on the same period, even if another thread
		 * would be adjusting PWM parameters
		 */
		myfloat period = state->period;

		for (int phaseIndex = 0; phaseIndex < state->multiWave.phaseCount; phaseIndex++) {
			systime_t timeToSwitch = (systime_t) ((iteration + state->multiWave.switchTimes[phaseIndex]) * period);
			chThdSleepUntil(start + timeToSwitch);

			for (int waveIndex = 0; waveIndex < state->multiWave.waveCount; waveIndex++) {
				OutputPin *outputPin = &state->outputPins[waveIndex];
				int value = state->multiWave.waves[waveIndex].pinStates[phaseIndex];
				setPinValue(outputPin, value ^ state->idleState);
			}
		}

		iteration++;
	}
#if defined __GNUC__
	return -1;
#endif
}

/**
 * Incoming parameters are potentially just values on current stack, so we have to copy
 * into our own permanent storage, right?
 */
void copyPwmParameters(PwmConfig *state, int phaseCount, myfloat *switchTimes, int waveCount, int **pinStates) {
	for (int phaseIndex = 0; phaseIndex < phaseCount; phaseIndex++) {
		state->multiWave.switchTimes[phaseIndex] = switchTimes[phaseIndex];

		for (int waveIndex = 0; waveIndex < waveCount; waveIndex++) {
//			print("output switch time index (%d/%d) at %f to %d\r\n", phaseIndex,waveIndex,
//					switchTimes[phaseIndex], pinStates[waveIndex][phaseIndex]);
			state->multiWave.waves[waveIndex].pinStates[phaseIndex] = pinStates[waveIndex][phaseIndex];
		}
	}
}

void wePlainInit(char *msg, PwmConfig *state, GPIO_TypeDef * port, int pin, int idleState, myfloat dutyCycle, myfloat freq) {
	myfloat switchTimes[] = { dutyCycle, 1 };
	int pinStates0[] = { 0, 1 };

	int *pinStates[1] = { pinStates0 };

	initOutputPin(msg, &state->outputPins[0], port, pin);

	weComplexInit(msg, state, idleState, 2, switchTimes, 1, pinStates);

	state->period = frequency2period(freq);
}

void weComplexInit(char *msg, PwmConfig *state, int idleState, int phaseCount, myfloat *switchTimes, int waveCount,
		int **pinStates) {
	chDbgCheck(phaseCount > 1, "count is too small");
	chDbgCheck(phaseCount <= PWM_PHASE_MAX_COUNT, "count is too large");
	chDbgCheck(switchTimes[phaseCount - 1] == 1, "last switch time has to be 1");
	chDbgCheck(waveCount > 0, "waveCount should be positive");
	for (int i = 0; i < phaseCount - 1; i++)
		chDbgCheck(switchTimes[i] < switchTimes[i + 1], "invalid switchTimes");

	state->multiWave.waveCount = waveCount;
	state->period = frequency2period(10);

	copyPwmParameters(state, phaseCount, switchTimes, waveCount, pinStates);

	state->name = msg;
	state->idleState = idleState;
	state->multiWave.phaseCount = phaseCount;
	chThdCreateStatic(state->deThreadStack, sizeof(state->deThreadStack), NORMALPRIO, (tfunc_t) deThread, state);
}

