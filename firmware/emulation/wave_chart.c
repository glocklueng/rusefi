/*
 * wave_chart.c
 *
 *  Created on: Jun 23, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include <string.h>
#include "wave_chart.h"
#include "ch.h"
#include "hal.h"
#include "rficonsole.h"

#define CHART_DELIMETER	"!"

static volatile int chartSize = 90;

static int isChartActive = TRUE;
//static int isChartActive = FALSE;

//#define DEBUG_WAVE 1

#if DEBUG_WAVE
static Logging debugLogging;
#endif

static Logging log;

void resetWaveChart(WaveChart *chart) {
#if DEBUG_WAVE
	scheduleSimpleMsg(&debugLogging, "reset while at ", chart->counter);
#endif
	resetLogging(&chart->logging);
	chart->counter = 0;
	chart->isPrinted = FALSE;
	append(&chart->logging, "wave_chart");
//	append(&chart->logging, chart->name);
	append(&chart->logging, DELIMETER);
}

static char LOGGING_BUFFER[5000];

static void printStatus(void) {
	scheduleIntValue(&log, "chart", isChartActive);
	scheduleIntValue(&log, "chartsize", chartSize);
}

static void setChartActive(int value) {
	isChartActive = value;
	printStatus();
}

static void setChartSize(int newSize) {
	if (newSize < 5)
		return;
	chartSize = newSize;
	printStatus();
}

int isWaveChartFull(WaveChart *chart) {
	return chart->counter >= chartSize;
}

void addWaveChartEvent(WaveChart *chart, char *name, char * msg) {
#if DEBUG_WAVE
	scheduleSimpleMsg(&debugLogging, "current", chart->counter);
#endif
	if (isWaveChartFull(chart)) {
		if (!chart->isPrinted) {
			append(&chart->logging, DELIMETER);
#if DEBUG_WAVE
			Logging *l = &chart->logging;
			scheduleSimpleMsg(&debugLogging, "IT'S TIME", strlen(l->buffer));
#endif
			if (isChartActive)
				scheduleLogging(&chart->logging);
			chart->isPrinted = TRUE;
		}
		return;
	}
	lockOutputBuffer(); // we have multiple threads writing to the same output buffer
	append(&chart->logging, name);
	append(&chart->logging, CHART_DELIMETER);
	append(&chart->logging, msg);
	append(&chart->logging, CHART_DELIMETER);
	appendInt(&chart->logging, chTimeNow());
	append(&chart->logging, CHART_DELIMETER);
	chart->counter++;
	unlockOutputBuffer();
}

void initWaveChart(WaveChart *chart, char *name) {
	initLogging(&log, "wave info", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));

	if (!isChartActive)
		printSimpleMsg(&log, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! chart disabled",
				0);

	printStatus();

	initLogging(&chart->logging, "wave chart", LOGGING_BUFFER, sizeof(LOGGING_BUFFER));
#if DEBUG_WAVE
	initLogging(&debugLogging, "wave chart debug", &debugLogging.DEFAULT_BUFFER, sizeof(debugLogging.DEFAULT_BUFFER));
#endif

//	chart->name = name;
	resetWaveChart(chart);
	addConsoleAction1("chartsize", setChartSize);
	addConsoleAction1("chart", setChartActive);
}
