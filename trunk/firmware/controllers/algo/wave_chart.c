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
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "wave_chart.h"
#include "main.h"

#if EFI_WAVE_CHART

#include "eficonsole.h"
#include "status_loop.h"


#define CHART_DELIMETER	"!"

/**
 * This is the number of events in the digital chart which would be displayed
 * on the 'digital sniffer' pane
 */
static volatile int chartSize = 100;

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

void setChartSize(int newSize) {
	if (newSize < 5)
		return;
	chartSize = newSize;
	printStatus();
}

void publishChartIfFull(WaveChart *chart) {
	if (isWaveChartFull(chart)) {
		publishChart(chart);
		resetWaveChart(chart);
	}
}

int isWaveChartFull(WaveChart *chart) {
	return chart->counter >= chartSize;
}

void publishChart(WaveChart *chart) {
	appendPrintf(&chart->logging, DELIMETER);
#if DEBUG_WAVE
	Logging *l = &chart->logging;
	scheduleSimpleMsg(&debugLogging, "IT'S TIME", strlen(l->buffer));
#endif
	if (isChartActive && getFullLog())
		scheduleLogging(&chart->logging);
}

/**
 * @brief	Register a change in sniffed signal
 */
void addWaveChartEvent3(WaveChart *chart, char *name, char * msg, char * msg2) {
	chDbgCheck(chart->isInitialized, "chart not initizlied");
#if DEBUG_WAVE
	scheduleSimpleMsg(&debugLogging, "current", chart->counter);
#endif
	if (isWaveChartFull(chart))
		return;
	lockOutputBuffer(); // we have multiple threads writing to the same output buffer
	appendPrintf(&chart->logging, "%s%s%s%s", name, CHART_DELIMETER, msg, CHART_DELIMETER);
	appendPrintf(&chart->logging, "%d%s%s", chTimeNow(), msg2, CHART_DELIMETER);
	chart->counter++;
	unlockOutputBuffer();
}

void initWaveChart(WaveChart *chart) {
	initLogging(&logger, "wave info");

	if (!isChartActive)
		printMsg(&logger, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! chart disabled");

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

#endif /* EFI_WAVE_CHART */
