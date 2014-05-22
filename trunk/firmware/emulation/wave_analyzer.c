/**
 * @file	wave_analyzer.c
 * @brief	Initialization of Input Capture pins used for dev console sniffer
 *
 * This file is responsible for sniffing of external digital signals and registering
 * these digital events in WaveChart used by the Sniffer tab of Dev Console.
 *
 *
 * @date Jan 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "wave_analyzer.h"
#include "eficonsole.h"
#include "data_buffer.h"
#include "pin_repository.h"
#include "engine_state.h"
#include "signal_executor.h"
#include "engine_configuration.h"
#include "trigger_central.h"
#include "rfiutil.h"


#define CHART_RESET_DELAY 1

extern board_configuration_s *boardConfiguration;

extern engine_configuration_s *engineConfiguration;

static volatile uint32_t ckpPeriodUs; // difference between current crank signal and previous crank signal
static volatile uint64_t previousCrankSignalStart = 0;

#define MAX_ICU_COUNT 5

static int waveReaderCount = 0;
static WaveReader readers[MAX_ICU_COUNT];
extern WaveChart waveChart;

static Logging logger;

static void ensureInitialized(WaveReader *reader) {
	efiAssertVoid(reader->hw.started, "wave analyzer NOT INITIALIZED");
}

#ifdef EFI_WAVE_ANALYZER

static void waAnaWidthCallback(WaveReader *reader) {
	uint64_t nowUs = getTimeNowUs();
	reader->eventCounter++;
	reader->lastActivityTimeUs = nowUs;
	addWaveChartEvent(reader->name, "up", "");

	uint64_t width = nowUs - reader->periodEventTimeUs;
	reader->last_wave_low_widthUs = width;

	reader->signalPeriodUs = nowUs - reader->widthEventTimeUs;
	reader->widthEventTimeUs = nowUs;
}

static void waIcuPeriodCallback(WaveReader *reader) {
	uint64_t nowUs = getTimeNowUs();
	reader->eventCounter++;
	reader->lastActivityTimeUs = nowUs;
	addWaveChartEvent(reader->name, "down", "");

	uint64_t width = nowUs - reader->widthEventTimeUs;
	reader->last_wave_high_widthUs = width;

	reader->periodEventTimeUs = nowUs;

	//scheduleSimpleMsg(&irqLogging, "co", reader->chart.counter);

//	dbAdd(&wavePeriodTime, now);

	int period = ckpPeriodUs;  // local copy of volatile variable

	uint64_t offset = nowUs - previousCrankSignalStart;

	if (offset > period / 2) {
		/**
		 * here we calculate the offset in relation to future cranking signal
		 */
		offset -= period;
	}
	reader->waveOffsetUs = offset;

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
	efiAssertVoid(index < MAX_ICU_COUNT, "too many ICUs");
	WaveReader *reader = &readers[index];
	WaveReaderHw *hw = &reader->hw;

	reader->name = name;

	registerCallback(&hw->widthListeners, (IntListener) waAnaWidthCallback, reader);

	registerCallback(&hw->periodListeners, (IntListener) waIcuPeriodCallback, reader);

	initWaveAnalyzerDriver(hw, driver, port, pin);

	print("wave%d input on %s%d\r\n", index, portname(reader->hw.port), reader->hw.pin);
	setWaveReaderMode(hw, mode);
}
#endif

//int getCrankStart() {
//	return previousCrankSignalStart;
//}

//static int getCrankPeriod(void) {
//	return ckpPeriod;
//}

static void onWaveShaftSignal(ShaftEvents ckpSignalType, int index, void *arg) {
	if (index != 0)
		return;
	uint64_t nowUs = getTimeNowUs();
	ckpPeriodUs = nowUs - previousCrankSignalStart;
	previousCrankSignalStart = nowUs;
}

static WORKING_AREA(waThreadStack, UTILITY_THREAD_STACK_SIZE);

//static Logging logger;

static msg_t waThread(void *arg) {
	chRegSetThreadName("Wave Analyzer");

	while (TRUE) {
		chThdSleepSeconds(CHART_RESET_DELAY);

		publishChartIfFull(&waveChart);
	}
#if defined __GNUC__
	return -1;
#endif
}

int getWaveLowWidth(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->last_wave_low_widthUs;
}

float getWaveHighWidthMs(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	if (getTimeNowUs() - reader->lastActivityTimeUs > 4 * US_PER_SECOND)
		return 0; // dwell time has expired
	return reader->last_wave_high_widthUs / 1000.0;
}

uint64_t getWaveOffset(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->waveOffsetUs;
}

float getSignalPeriodMs(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->signalPeriodUs / 1000.0;
}

int getWidthEventTime(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->widthEventTimeUs;
}

uint64_t getPeriodEventTime(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->periodEventTimeUs;
}

int waveBufferReported = 0;

static void reportWave(Logging *logging, int index) {
//	int counter = getEventCounter(index);
//	debugInt2(logging, "ev", index, counter);

	float dwellMs = getWaveHighWidthMs(index);
	float periodMs = getSignalPeriodMs(index);

	appendPrintf(logging, "duty%d%s", index, DELIMETER);
	appendFloat(logging, 100.0 * dwellMs / periodMs, 2);
	appendPrintf(logging, "%s", DELIMETER);

	appendPrintf(logging, "dwell%d%s", index, DELIMETER);
	appendFloat(logging, dwellMs, 2);
	appendPrintf(logging, "%s", DELIMETER);

	appendPrintf(logging, "period%d%s", index, DELIMETER);
	appendFloat(logging, periodMs, 2);
	appendPrintf(logging, "%s", DELIMETER);

//	int crank = getCrankPeriod();

//	int offset = getWaveOffset(index);
//	debugFloat2(logging, "advance", index, 90.0 * offset / crank, 3);
//	debugInt2(logging, "offset", index, offset);
}

void printWave(Logging *logging) {
	reportWave(logging, 0);
	reportWave(logging, 1);
}

void initWaveAnalyzer(void) {
#ifdef EFI_WAVE_ANALYZER
	initLogging(&logger, "wave");

	initWave("input1 A8", 0, getInputCaptureDriver(boardConfiguration->primaryLogicAnalyzerPin), getHwPort(boardConfiguration->primaryLogicAnalyzerPin), getHwPin(boardConfiguration->primaryLogicAnalyzerPin), 1);
	initWave("input2 E5", 1, getInputCaptureDriver(boardConfiguration->secondaryLogicAnalyzerPin), getHwPort(boardConfiguration->secondaryLogicAnalyzerPin), getHwPin(boardConfiguration->secondaryLogicAnalyzerPin), 1);
	//	initWave("input0 C6", 2, &WAVE_TIMER, WAVE_INPUT_PORT, WAVE_INPUT_PIN, 0);

	addTriggerEventListener(&onWaveShaftSignal, "wave analyzer", NULL);

	addConsoleActionII("wm", setWaveModeSilent);

	chThdCreateStatic(waThreadStack, sizeof(waThreadStack), NORMALPRIO, waThread, NULL);

#else
	print("wave disabled\r\n");
#endif
}
