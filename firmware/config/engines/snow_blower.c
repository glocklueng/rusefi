/*
 *  Created on: Sep 9, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    snow_blower.c
 */

#include "main.h"
#include "datalogging.h"
#include "rpm_reporter.h"
#include "ckp_events.h"
#include "crank_input.h"

#if EFI_ENGINE_SNOW_BLOWER

extern OutputSignal injectorOut1;

static Logging log;

float getVRef(void) {
	return 12;
}

float getFuelMs() {
	return 1;
}

#define STROKE_TIME_CONSTANT2 (1000 * 60 * RPM_MULT * TICKS_IN_MS)

static int convertAngleToSysticks(int rpm, int advance) {
	return (int) (advance * STROKE_TIME_CONSTANT2 / 360 / rpm);
}

static void onShaftSignal(int ckpSignalType) {

	if (ckpSignalType != CKP_PRIMARY_DOWN)
		return;

	int offset = convertAngleToSysticks(getCurrentRpm(), 10);

	scheduleOutput(&injectorOut1, offset, TICKS_IN_MS);

}

void initMainEventListener() {
	initLogging(&log, "main event handler", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));

	registerCkpListener(&onShaftSignal, "main loop");

}

#endif
