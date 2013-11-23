/**
 * @file	wave_analyzer.c
 * @brief	Initialization of Input Capture pins used for dev console sniffer
 *
 *
 *  Created on: Jan 7, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "wave_analyzer.h"
#include "shaft_position_input.h"
#include "rficonsole.h"
#include "wave_math.h"
#include "data_buffer.h"
#include "ckp_events.h"
#include "pin_repository.h"
#include "datalogging.h"

#define CHART_RESET_DELAY 1

volatile int ckpPeriod; // different between current crank signal and previous crank signal
volatile int previousCrankSignalStart = 0;

#define MAX_ICU_COUNT 5

static int waveReaderCount = 0;
static WaveReader readers[MAX_ICU_COUNT];
WaveChart crankChart;

data_buffer_s waveWidthCounters;

data_buffer_s waveWidthTime;
data_buffer_s waveWidth;

data_buffer_s wavePeriodTime;
data_buffer_s wavePeriod;

int waveWidthCounter = 0;

static Logging logger;

static void ensureInitialized(WaveReader *reader) {
	if (!reader->hw.started)
		fatal("wave analyzer NOT INITIALIZED");
}

#ifdef EFI_WAVE_ANALYZER

static void waAnaWidthCallback(WaveReader *reader) {
	systime_t now = chTimeNow();
	reader->eventCounter++;
	reader->lastActivityTime = now;
	addWaveChartEvent(&crankChart, reader->name, "up");

	int width = overflowDiff(now, reader->periodEventTime);
	reader->last_wave_low_width = width;

	reader->signalPeriod = overflowDiff(now, reader->widthEventTime);
	reader->widthEventTime = now;
}

static void waIcuPeriodCallback(WaveReader *reader) {
	systime_t now = chTimeNow();
	reader->eventCounter++;
	reader->lastActivityTime = now;
	addWaveChartEvent(&crankChart, reader->name, "down");

	int width = overflowDiff(now, reader->widthEventTime);
	reader->last_wave_high_width = width;

	reader->periodEventTime = now;


	//scheduleSimpleMsg(&irqLogging, "co", reader->chart.counter);


//	dbAdd(&wavePeriodTime, now);

	int period = ckpPeriod;  // local copy of volatile variable

	int offset = overflowDiff(now, previousCrankSignalStart);

	if (offset > period / 2) {
		/**
		 * here we calculate the offset in relation to future cranking signal
		 */
		offset -= period;
	}
	reader->waveOffsetSystimer = offset;

	// we want only the low phase length, so we subsctract high width from period
//	processSignal(1, &dataPinReader, last_period - last_adc_response_width);
}

static void setWaveModeSilent(int index, int mode) {
	WaveReader *reader = &readers[index];

	setWaveReaderMode(&reader->hw, mode);
}

void setWaveMode(int index, int mode) {
	setWaveModeSilent(index, mode);
	print("wavemode%d:%d\r\n", index, mode);
}

int getWaveMode(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->hw.activeMode;
}

int getEventCounter(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->eventCounter;
}

static void initWave(char *name, int index, ICUDriver *driver, ioportid_t port, int pin, int mode) {
	waveReaderCount++;
	chDbgCheck(index < MAX_ICU_COUNT, "too many ICUs");
	WaveReader *reader = &readers[index];
	WaveReaderHw *hw = &reader->hw;

	reader->name = name;

	registerCallback(&hw->widthListeners, (IntListener)waAnaWidthCallback, reader);

	registerCallback(&hw->periodListeners, (IntListener)waIcuPeriodCallback, reader);

	initWaveAnalyzerDriver(hw, driver, port, pin);

	print("wave%d input on %s%d\r\n", index, portname(reader->hw.port), reader->hw.pin);
	setWaveReaderMode(hw, mode);
}
#endif

//int getCrankStart() {
//	return previousCrankSignalStart;
//}

static int getCrankPeriod(void) {
	return ckpPeriod;
}

static void onWaveShaftSignal(ShaftEvents ckpSignalType, int index) {
	if (index != 0)
		return;
	systime_t now = chTimeNow();
	ckpPeriod = now - previousCrankSignalStart;
	previousCrankSignalStart = now;
}

static WORKING_AREA(waThreadStack, 256);

//static Logging logger;

static msg_t waThread(void *arg) {
	chRegSetThreadName("Wave Analyzer");

	while (1) {
		chThdSleepSeconds(CHART_RESET_DELAY);

		if (crankChart.isPrinted)
			resetWaveChart(&crankChart);
	}
	return -1;
}

static void onShaftSignalWA(ShaftEvents ckpSignalType, int index) {
	if (ckpSignalType == SHAFT_PRIMARY_UP) {
		addWaveChartEvent(&crankChart, "crank", "up");
	} else if (ckpSignalType == SHAFT_PRIMARY_DOWN) {
		addWaveChartEvent(&crankChart, "crank", "down");
	} else if (ckpSignalType == SHAFT_SECONDARY_UP) {
		addWaveChartEvent(&crankChart, "crank2", "up");
	} else if (ckpSignalType == SHAFT_SECONDARY_DOWN) {
		addWaveChartEvent(&crankChart, "crank2", "down");
	}
}

int getWaveLowWidth(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->last_wave_low_width;
}

int getWaveHighWidth(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	if (reader->lastActivityTime < chTimeNow() - 4 * ckpPeriod)
		return 0; // dwell time has expired
	return reader->last_wave_high_width;
}

int getWaveOffset(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->waveOffsetSystimer;
}

int getSignalPeriod(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->signalPeriod;
}

int getWidthEventTime(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->widthEventTime;
}

int getPeriodEventTime(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->periodEventTime;
}

int waveBufferReported = 0;

#define WAVE_COLUMNS 4

data_buffer_s *waveTable[WAVE_COLUMNS] = { &waveWidthCounters, &waveWidth, &waveWidthTime, &wavePeriodTime };

char *waveCaptions[WAVE_COLUMNS] = { "count", "wid", "time", "ptime" };

void pokeWaveInfo(void) {
	if (!waveBufferReported && dbIsFull(&waveWidthTime)) {
		waveBufferReported = 1;
		dbPrintTable(waveTable, waveCaptions, WAVE_COLUMNS);
	}
}

static void reportWave(Logging *logging, int index) {
	int counter = getEventCounter(index);
//	debugInt2(logging, "ev", index, counter);

	int dwell = getWaveHighWidth(index);
	int period = getSignalPeriod(index);

	debugFloat2(logging, "duty", index, 100.0 * dwell / period, 2);
	debugFloat2(logging, "dwell", index, ((myfloat) dwell) / TICKS_IN_MS, 2);
	debugFloat2(logging, "period", index, ((myfloat) period) / TICKS_IN_MS, 2);

	int crank = getCrankPeriod();

	int offset = getWaveOffset(index);
//	debugFloat2(logging, "advance", index, 90.0 * offset / crank, 3);
//	debugInt2(logging, "offset", index, offset);
}

void printWave(Logging *logging) {
	reportWave(logging, 0);
	reportWave(logging, 1);
}

void initWaveAnalyzer(void) {
#ifdef EFI_WAVE_ANALYZER

	initLogging(&logger, "wave", logger.DEFAULT_BUFFER, sizeof(logger.DEFAULT_BUFFER));


	registerShaftPositionListener(&onWaveShaftSignal, "wave analyzer");

	initWaveChart(&crankChart);

	initWave("input1 A8", 0, &LOGIC_ANALYZER_ONE_DRIVER, LOGIC_ANALYZER_PORT, LOGIC_ANALYZER_PIN, 1);
	initWave("input2 E5", 1, &ICUD9, GPIOE, 5, 1);
	//	initWave("input0 C6", 2, &WAVE_TIMER, WAVE_INPUT_PORT, WAVE_INPUT_PIN, 0);

	registerShaftPositionListener(&onShaftSignalWA, "crank chart");

	addConsoleAction2I("wm", setWaveModeSilent);

	chThdCreateStatic(waThreadStack, sizeof(waThreadStack), NORMALPRIO, waThread, NULL);

#else
	print("wave disabled\r\n");
#endif
}
