/*
 * rpm_reporter.c
 *
 *  Created on: Jan 1, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    rpm_reporter.c
 * @brief   Shaft position sensor(s) decoder code
 */

#include "ckp_events.h"
#include "crank_input.h"
#include "datalogging.h"
#include "rpm_reporter.h"
#include "rficonsole.h"

#include "output_pins.h"
#include "wave_math.h"

static volatile int rpm = 0;
// we need this initial to have not_running at first invocation
static volatile time_t lastRpmEventTime = -10 * SECOND_AS_TICKS;

/**
 * @return true if previous signal is too old
 */
int isNotRunning(int previousCrankSignalTime) {
	return overflowDiff(chTimeNow(), previousCrankSignalTime)
			> SECOND_AS_TICKS;
}

//static Logging log;

int isRunning() {
	time_t now = chTimeNow();
	return overflowDiff(now, lastRpmEventTime) < 2 * SECOND_AS_TICKS;
}

static void updateRpmValue(int ckpEventType) {
	// this code is invoked on interrupt thread

	if (ckpEventType != CKP_PRIMARY_UP)
		return;

//	logStartLine(&log, 0);
//	msgInt(&log, "msg,event ", rpmEventCounter++);
//	logPending(&log);

	time_t now = chTimeNow();

	// todo: wonder what is the RPM during cranking?
	int hadRpmRecently = isRunning();
	;

// 60000 because per minute
// * 2 because each revolution of crankshaft consists of two camshaft revolutions
// / 4 because each cylinder sends a signal
	// need to measure time from the previous non-skipped event
	if (hadRpmRecently) {
		int diff = now - lastRpmEventTime;
		if (diff == 0)
			rpm = -1;
		else
			rpm = 60000 * TICKS_IN_MS * 2 / 4 / diff;
	}
	lastRpmEventTime = now;
}

int getCurrentRpm() {
	if (isNotRunning(lastRpmEventTime))
		return 0;
	return rpm;
}

void initTachometer() {
	registerCkpListener(&updateRpmValue, "rpm reporter");
}
