/**
 * @file	analog_chart.c
 *
 * @date Dec 20, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "rpm_calculator.h"
#include "analog_chart.h"

static char LOGGING_BUFFER[5000];
static Logging logging;

static int pendingData = FALSE;
static int initialized = FALSE;

void acAddData(float angle, float value) {
	if (!initialized)
		return; // this is possible because of initialization sequence

	if (getRevolutionCounter() % 20 != 0) {
		if (pendingData) {
			// message terminator
			appendPrintf(&logging, DELIMETER);
			// output pending data
			scheduleLogging(&logging);
			pendingData = FALSE;
		}
		return;
	}
	if (!pendingData) {
		pendingData = TRUE;
		resetLogging(&logging);
		// message header
		appendPrintf(&logging, "msg%s", DELIMETER);
		appendPrintf(&logging, "analog_chart|");
	}

	if (loggingSize(&logging) < sizeof(LOGGING_BUFFER) - 100)
		appendPrintf(&logging, "%f|%f|", angle, value);
}

void initAnalogChart(void) {
	initLoggingExt(&logging, "analog chart", LOGGING_BUFFER, sizeof(LOGGING_BUFFER));
	initialized = TRUE;
}
