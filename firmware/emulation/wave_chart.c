/**
 * @file	wave_chart.c
 * @brief	Dev console wave sniffer logic
 *
 * Here we have our own build-in logic analyzer. The data we aggregate here is sent to the
 * java UI Dev Console so that it can be displayed nicely in the Sniffer tab.
 *
 * Both external events (see wave_analyzer.c) and internal (see signal executors) are supported
 *
 * @date Jun 23, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include <string.h>
#include "wave_chart.h"
#include "main.h"
#include "rficonsole.h"

#define CHART_DELIMETER	"!"

static volatile int chartSize = EFI_DEFAULT_CHART_SIZE;

static int isChartActive = TRUE;
//static int isChartActive = FALSE;

//#define DEBUG_WAVE 1

#if DEBUG_WAVE
static Logging debugLogging;
#endif

static Logging logger;

void resetWaveChart(WaveChart *chart) {
#if DEBUG_WAVE
	scheduleSimpleMsg(&debugLogging, "reset while at ", chart->counter);
#endif
	resetLogging(&chart->logging);
	chart->counter = 0;
	chart->isPrinted = FALSE;
	appendPrintf(&chart->logging, "wave_chart%s", DELIMETER);
}

static char LOGGING_BUFFER[5000];

static void printStatus(void) {
	scheduleIntValue(&logger, "chart", isChartActive);
	scheduleIntValue(&logger, "chartsize", chartSize);
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

/**
 * @brief	Register a change in sniffed signal
 */
void addWaveChartEvent(WaveChart *chart, char *name, char * msg) {
	chDbgAssert(chart->isInitialized, "chart not initizlied" , 0);
#if DEBUG_WAVE
	scheduleSimpleMsg(&debugLogging, "current", chart->counter);
#endif
	if (isWaveChartFull(chart)) {
		if (!chart->isPrinted) {
			appendPrintf(&chart->logging, DELIMETER);
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
	appendPrintf(&chart->logging, "%s%s%s%s", name, CHART_DELIMETER, msg, CHART_DELIMETER);
	appendPrintf(&chart->logging, "%d%s", chTimeNow(), CHART_DELIMETER);
	chart->counter++;
	unlockOutputBuffer();
}

void initWaveChart(WaveChart *chart) {
	initLogging(&logger, "wave info");

	if (!isChartActive)
		printSimpleMsg(&logger, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! chart disabled",
				0);

	printStatus();

	initLoggingExt(&chart->logging, "wave chart", LOGGING_BUFFER, sizeof(LOGGING_BUFFER));
	chart->isInitialized = TRUE;
#if DEBUG_WAVE
	initLoggingExt(&debugLogging, "wave chart debug", &debugLogging.DEFAULT_BUFFER, sizeof(debugLogging.DEFAULT_BUFFER));
#endif

	resetWaveChart(chart);
	addConsoleActionI("chartsize", setChartSize);
	addConsoleActionI("chart", setChartActive);
}
