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
#include "datalogging.h"

static Logging logger;

static void applyPinState(PwmConfig *state, int stateIndex) {
	chDbgAssert(state->multiWave.waveCount <= PWM_PHASE_MAX_WAVE_PER_PWM, "invalid waveCount", NULL);
	for (int waveIndex = 0; waveIndex < state->multiWave.waveCount; waveIndex++) {
		io_pin_e ioPin = state->outputPins[waveIndex];
		chDbgAssert(stateIndex < PWM_PHASE_MAX_COUNT, "invalid stateIndex", NULL);
		int value = state->multiWave.waves[waveIndex].pinStates[stateIndex];
		setOutputPinValue(ioPin, value);
	}
}

static time_t getNextSwitchTime(PwmConfig *state) {
	chDbgAssert(state->safe.phaseIndex < PWM_PHASE_MAX_COUNT, "phaseIndex range", NULL);
	int iteration = state->safe.iteration;
	myfloat switchTime = state->multiWave.switchTimes[state->safe.phaseIndex];
	myfloat period = state->safe.period;
#if DEBUG_PWM
	scheduleMsg(&logger, "iteration=%d switchTime=%f period=%f", iteration, switchTime, period);
#endif

	systime_t timeToSwitch = (systime_t) ((iteration + switchTime) * period);

#if DEBUG_PWM
	scheduleMsg(&logger, "start=%d timeToSwitch=%d", state->safe.start, timeToSwitch);
#endif
	return state->safe.start + timeToSwitch;
}

static time_t togglePwmState(PwmConfig *state) {
#if DEBUG_PWM
	scheduleMsg(&logger, "togglePwmState phaseIndex=%d iteration=%d", state->safe.phaseIndex, state->safe.iteration);
	scheduleMsg(&logger, "state->period=%f state->safe.period=%f", state->period, state->safe.period);
#endif

	if (state->safe.phaseIndex == 0) {
		if (isnan(state->period)) {
			/**
			 * zero period means PWM is paused
			 */
			return TICKS_IN_MS;
		}
		chDbgAssert(state->period != 0, "period not initialized", NULL);
		if (state->safe.period != state->period) {
			/**
			 * period length has changed - we need to reset internal state
			 */
			state->safe.start = chTimeNow();
			state->safe.iteration = 0;
			state->safe.period = state->period;
#if DEBUG_PWM
	scheduleMsg(&logger, "state reset start=%d iteration=%d", state->safe.start, state->safe.iteration);
#endif
		}
	}

	applyPinState(state, state->safe.phaseIndex == 0 ? state->multiWave.phaseCount - 1 : state->safe.phaseIndex - 1);

	time_t nextSwitchTime = getNextSwitchTime(state);
#if DEBUG_PWM
	scheduleMsg(&logger, "%s: nextSwitchTime %d", state->name, nextSwitchTime);
#endif
	time_t timeToSwitch = nextSwitchTime - chTimeNow();

	state->safe.phaseIndex++;
	if (state->safe.phaseIndex == state->multiWave.phaseCount) {
		state->safe.phaseIndex = 0; // restart
		state->safe.iteration++;
	}
	return timeToSwitch;
}

static msg_t deThread(PwmConfig *state) {
	chRegSetThreadName("Wave");

#if DEBUG_PWM
	scheduleMsg(&logger, "Thread started for %s", state->name);
#endif


//	setPadValue(state, state->idleState); todo: currently pin is always zero at first iteration.
// we can live with that for now
	// todo: figure out overflow

	while (TRUE) {
		time_t timeToSwitch = togglePwmState(state);
#if DEBUG_PWM
	scheduleMsg(&logger, "%s: sleep %d", state->name, timeToSwitch);
#endif
		chThdSleep(timeToSwitch);
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

void wePlainInit(char *msg, PwmConfig *state, GPIO_TypeDef * port, int pin, myfloat dutyCycle, myfloat freq,
		io_pin_e ioPin) {
	myfloat switchTimes[] = { dutyCycle, 1 };
	int pinStates0[] = { 0, 1 };

	int *pinStates[1] = { pinStates0 };

	state->outputPins[0] = ioPin;

	outputPinRegister(msg, state->outputPins[0], port, pin);

	state->period = frequency2period(freq);
	weComplexInit(msg, state, 2, switchTimes, 1, pinStates);
}

void weComplexInit(char *msg, PwmConfig *state, int phaseCount, myfloat *switchTimes, int waveCount, int **pinStates) {


	chDbgCheck(state->period != 0, "period is not initialized");
	chDbgCheck(phaseCount > 1, "count is too small");
	chDbgCheck(phaseCount <= PWM_PHASE_MAX_COUNT, "count is too large");
	chDbgCheck(switchTimes[phaseCount - 1] == 1, "last switch time has to be 1");
	chDbgCheck(waveCount > 0, "waveCount should be positive");
	checkSwitchTimes(phaseCount, switchTimes);

	state->multiWave.waveCount = waveCount;

	copyPwmParameters(state, phaseCount, switchTimes, waveCount, pinStates);

	state->safe.phaseIndex = 0;
	state->safe.period = -1;
	state->safe.iteration = -1;
	state->name = msg;
	state->multiWave.phaseCount = phaseCount;
	chThdCreateStatic(state->deThreadStack, sizeof(state->deThreadStack),
	NORMALPRIO, (tfunc_t) deThread, state);
}

void initPwmGenerator(void) {
	initLogging(&logger, "PWM gen");
}

