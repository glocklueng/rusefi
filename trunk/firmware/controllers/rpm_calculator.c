/**
 * @file    rpm_calculator.c
 * @brief   RPM calculator
 *
 * Here we listen to position sensor events in order to figure our if engine is currently running or not.
 *
 *  Created on: Jan 1, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "rpm_calculator.h"
#include "ckp_events.h"
#include "shaft_position_input.h"
#include "datalogging.h"
#include "rficonsole.h"
#include "wave_math.h"

static volatile int rpm = 0;
// we need this initial to have not_running at first invocation
static volatile time_t lastRpmEventTime = -10 * CH_FREQUENCY;

/**
 * @return true if there was a full shaft revolution within the last second
 */
int isRunning() {
	time_t now = chTimeNow();
	return overflowDiff(now, lastRpmEventTime) < CH_FREQUENCY;
}

int getCurrentRpm() {
	if (!isRunning())
		return 0;
	return rpm;
}

static void shaftPositionCallback(ShaftEvents ckpEventType, int index) {
	// this callback is invoked on interrupt thread
	if (index != 0)
		return;

//	logStartLine(&logger, 0);
//	msgInt(&logger, "msg,event ", rpmEventCounter++);
//	logPending(&log);

	time_t now = chTimeNow();

	int hadRpmRecently = isRunning();
	;

	if (hadRpmRecently) {
		int diff = now - lastRpmEventTime;
		if (diff == 0) {
			// unexpected state. Noise?
			rpm = -1;
		} else {
			// 60000 because per minute
			// * 2 because each revolution of crankshaft consists of two camshaft revolutions
			// / 4 because each cylinder sends a signal
			// need to measure time from the previous non-skipped event

			rpm = 60000 * TICKS_IN_MS / RPM_MULT / diff;
		}
	}
	lastRpmEventTime = now;
}

void initRpmCalculator() {
	registerShaftPositionListener(&shaftPositionCallback, "rpm reporter");
}
