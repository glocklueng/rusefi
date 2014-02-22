/**
 * @file    rpm_calculator.c
 * @brief   RPM calculator
 *
 * Here we listen to position sensor events in order to figure our if engine is currently running or not.
 * Actual getRpm() is calculated once per crankshaft revolution, based on the amount of time passed
 * since the start of previous shaft revolution.
 *
 * @date Jan 1, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "rpm_calculator.h"
#include "trigger_input.h"
#include "rficonsole.h"
#include "wave_math.h"
#include "engine_configuration.h"
#include "engine_math.h"
#include "analog_chart.h"

static rpm_s rpmState;

extern engine_configuration_s *engineConfiguration;
extern engine_configuration2_s *engineConfiguration2;

/**
 * @return true if there was a full shaft revolution within the last second
 */
int isRunning() {
	time_t now = chTimeNow();
	return overflowDiff(now, rpmState.lastRpmEventTime) < CH_FREQUENCY;
}

/**
 * @return -1 in case of isNoisySignal(), current RPM otherwise
 */
int getRpm() {
	if (!isRunning())
		return 0;
	return rpmState.rpm;
}

/**
 * @return Current crankshaft angle, 0 to 720 for four-stroke
 */
float getCrankshaftAngle(time_t time) {
	int timeSinceZeroAngle = overflowDiff(time, rpmState.lastRpmEventTime);

	float cRevolutionTime = getCrankshaftRevolutionTime(rpmState.rpm);

	return 360 * timeSinceZeroAngle / cRevolutionTime;
}

int getRevolutionCounter(void) {
	return rpmState.revolutionCounter;
}

/**
 * Checks for noise on the trigger input line. Noise is detected by an unexpectedly small time gap between
 * current and previous trigger input events.
 *
 * @return TRUE if noise is detected
 */
static int isNoisySignal(rpm_s * rpmState, int now) {
	int diff = now - rpmState->lastRpmEventTime;
	return diff == 0;
}

/**
 * @brief Shaft position callback used by RPM calculation logic.
 *
 * This callback is invoked on interrupt thread.
 */
static void shaftPositionCallback(ShaftEvents ckpEventType, int index) {
	if (index != 0) {
		if (engineConfiguration->analogChartMode == AC_TRIGGER)
			acAddData(getCrankshaftAngle(chTimeNow()), 1000 * ckpEventType + index);
		return;
	}
	rpmState.revolutionCounter++;

	time_t now = chTimeNow();

	int hadRpmRecently = isRunning();

	if (hadRpmRecently) {
		if (isNoisySignal(&rpmState, now)) {
			// unexpected state. Noise?
			rpmState.rpm = -1;
		} else {
			int diff = now - rpmState.lastRpmEventTime;
			// 60000 because per minute
			// * 2 because each revolution of crankshaft consists of two camshaft revolutions
			// / 4 because each cylinder sends a signal
			// need to measure time from the previous non-skipped event

			rpmState.rpm = (int)(60000 * TICKS_IN_MS / engineConfiguration->rpmMultiplier / diff);
		}
	}
	rpmState.lastRpmEventTime = now;
	if (engineConfiguration->analogChartMode == AC_TRIGGER)
		acAddData(getCrankshaftAngle(now), index);
}

void initRpmCalculator(void) {
	rpmState.rpm = 0;

	// we need this initial to have not_running at first invocation
	rpmState.lastRpmEventTime = (time_t)-10 * CH_FREQUENCY;

	registerShaftPositionListener(&shaftPositionCallback, "rpm reporter");
}
