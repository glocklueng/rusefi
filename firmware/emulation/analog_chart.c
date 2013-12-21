/**
 * @file	analog_chart.c
 *
 * @date Dec 20, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "rpm_calculator.h"
#include "analog_chart.h"

static char LOGGING_BUFFER[2000];
static Logging logging;

static int pendingData = FALSE;

void acAddData(float angle, float value) {
	if (getRevolutionCounter() % 20 != 0)
		return;

	resetLogging(&logging);
	appendPrintf(&logging, "msg%s", DELIMETER);
	appendPrintf(&logging, "%s|%f|%f%s", "angle", angle, value, DELIMETER);
	scheduleLogging(&logging);
}

void initAnalogChart(void) {
	initLoggingExt(&logging, "analog chart", LOGGING_BUFFER, sizeof(LOGGING_BUFFER));
}
