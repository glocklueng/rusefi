/**
 * @file    rpm_calculator.c
 * @brief   RPM calculator
 *
 * Here we listen to position sensor events in order to figure our if engine is currently running or not.
 *
 * @date Jan 1, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "rpm_calculator.h"
#include "ckp_events.h"
#include "shaft_position_input.h"
#include "datalogging.h"
#include "rficonsole.h"
#include "wave_math.h"
#include "engine_configuration.h"
#include "analog_chart.h"

static rpm_s rpmState;

extern EngineConfiguration *engineConfiguration;
extern EngineConfiguration2 *engineConfiguration2;

/**
 * @return true if there was a full shaft revolution within the last second
 */
int isRunning() {
	time_t now = chTimeNow();
	return overflowDiff(now, rpmState.lastRpmEventTime) < CH_FREQUENCY;
}

int getCurrentRpm() {
	if (!isRunning())
		return 0;
	return rpmState.rpm;
}

/**
 * @return Current crankshaft angle, 0 to 720 for four-stroke
 */
float getCrankshaftAngle(time_t time) {
	int timeSinceZeroAngle = overflowDiff(time, rpmState.lastRpmEventTime);

	float crt = getCrankshaftRevolutionTime(rpmState.rpm);

	return 360 * timeSinceZeroAngle / crt;
}

int getRevolutionCounter(void) {
	return rpmState.revolutionCounter;
}

/**
 * @brief Shaft position callback used by RPM calculation logic.
 *
 * This callback is invoked on interrupt thread.
 */
static void shaftPositionCallback(ShaftEvents ckpEventType, int index) {
	if (index != 0) {
		if (engineConfiguration->analogChartMode == AC_SHAFT)
			acAddData(getCrankshaftAngle(chTimeNow()), index);
		return;
	}
	rpmState.revolutionCounter++;

	time_t now = chTimeNow();

	int hadRpmRecently = isRunning();

	if (hadRpmRecently) {
		int diff = now - rpmState.lastRpmEventTime;
		if (diff == 0) {
			// unexpected state. Noise?
			rpmState.rpm = -1;
		} else {
			// 60000 because per minute
			// * 2 because each revolution of crankshaft consists of two camshaft revolutions
			// / 4 because each cylinder sends a signal
			// need to measure time from the previous non-skipped event

			rpmState.rpm = 60000 * TICKS_IN_MS / engineConfiguration2->rpmMultiplier / diff;
		}
	}
	rpmState.lastRpmEventTime = now;
	if (engineConfiguration->analogChartMode == AC_SHAFT)
		acAddData(getCrankshaftAngle(now), index);
}

void initRpmCalculator(void) {
	rpmState.rpm = 0;

	// we need this initial to have not_running at first invocation
	rpmState.lastRpmEventTime = -10 * CH_FREQUENCY;

	registerShaftPositionListener(&shaftPositionCallback, "rpm reporter");
}
