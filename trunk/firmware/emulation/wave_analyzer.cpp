/**
 * @file	wave_analyzer.cpp
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
#include "engine_math.h"
#include "engine.h"
#include "rpm_calculator.h"

extern Engine engine;

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

#if EFI_WAVE_ANALYZER || defined(__DOXYGEN__)

static void waAnaWidthCallback(WaveReader *reader) {
	uint64_t nowUs = getTimeNowUs();
	reader->eventCounter++;
	reader->lastActivityTimeUs = nowUs;
	addWaveChartEvent(reader->name, WC_UP, "");

	uint32_t width = nowUs - reader->periodEventTimeUs;
	reader->last_wave_low_widthUs = width;

	reader->signalPeriodUs = nowUs - reader->widthEventTimeUs;
	reader->widthEventTimeUs = nowUs;
}

void WaveReader::onFallEvent() {
	uint64_t nowUs = getTimeNowUs();
	eventCounter++;
	lastActivityTimeUs = nowUs;
	addWaveChartEvent(name, WC_DOWN, "");

	uint64_t width = nowUs - widthEventTimeUs;
	last_wave_high_widthUs = width;

	int revolutionCounter = getRevolutionCounter();

	totalOnTimeAccumulatorUs += width;
	if (currentRevolutionCounter != revolutionCounter) {
		/**
		 * We are here in case of a new engine cycle
		 */
		currentRevolutionCounter = revolutionCounter;
		prevTotalOnTimeUs = totalOnTimeAccumulatorUs;
		totalOnTimeAccumulatorUs = 0;
	}

	periodEventTimeUs = nowUs;

	//scheduleSimpleMsg(&irqLogging, "co", reader->chart.counter);

//	dbAdd(&wavePeriodTime, now);

	uint32_t period = ckpPeriodUs;  // local copy of volatile variable

	uint32_t offset = nowUs - previousCrankSignalStart;

	if (offset > period / 2) {
		/**
		 * here we calculate the offset in relation to future cranking signal
		 */
		offset -= period;
	}
	waveOffsetUs = offset;

	// we want only the low phase length, so we subsctract high width from period
//	processSignal(1, &dataPinReader, last_period - last_adc_response_width);

}

static void waIcuPeriodCallback(WaveReader *reader) {
	reader->onFallEvent();
}

static void setWaveModeSilent(int index, int mode) {
	WaveReader *reader = &readers[index];

	setWaveReaderMode(&reader->hw, mode);
}

static int getEventCounter(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->eventCounter;
}

static void initWave(const char *name, int index) {
	brain_pin_e brainPin = boardConfiguration->logicAnalyzerPins[index];

	ioportid_t port = getHwPort(brainPin);
	ioportmask_t pin = getHwPin(brainPin);
	ICUDriver *driver = getInputCaptureDriver(brainPin);

	bool mode = boardConfiguration->logicAnalyzerMode[index];

	waveReaderCount++;
	efiAssertVoid(index < MAX_ICU_COUNT, "too many ICUs");
	WaveReader *reader = &readers[index];
	WaveReaderHw *hw = &reader->hw;

	reader->name = name;

	registerCallback(&hw->widthListeners, (IntListener) waAnaWidthCallback, (void*) reader);

	registerCallback(&hw->periodListeners, (IntListener) waIcuPeriodCallback, (void*) reader);

	initWaveAnalyzerDriver(hw, driver, port, pin);

	print("wave%d input on %s%d\r\n", index, portname(reader->hw.port), reader->hw.pin);
	setWaveReaderMode(hw, mode);
}
#endif

static void onWaveShaftSignal(trigger_event_e ckpSignalType, int index, void *arg) {
	if (index != 0) {
		return;
	}
	uint64_t nowUs = getTimeNowUs();
	ckpPeriodUs = nowUs - previousCrankSignalStart;
	previousCrankSignalStart = nowUs;
}

static THD_WORKING_AREA(waThreadStack, UTILITY_THREAD_STACK_SIZE);

//static Logging logger;

static msg_t waThread(void *arg) {
	chRegSetThreadName("Wave Analyzer");
#if EFI_WAVE_CHART
	while (TRUE) {
		chThdSleepSeconds(CHART_RESET_DELAY);

		publishChartIfFull(&waveChart);
	}
#endif /* EFI_WAVE_CHART */
#if defined __GNUC__
	return -1;
#endif
}

static uint32_t getWaveLowWidth(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->last_wave_low_widthUs;
}

static float getSignalOnTime(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	if (getTimeNowUs() - reader->lastActivityTimeUs > 4 * US_PER_SECOND) {
		return 0.0f; // dwell time has expired
	}
	return reader->last_wave_high_widthUs / 1000.0f;
}

static uint64_t getWaveOffset(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->waveOffsetUs;
}

static float getSignalPeriodMs(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->signalPeriodUs / 1000.0f;
}

static uint64_t getWidthEventTime(int index) {
	WaveReader *reader = &readers[index];
	ensureInitialized(reader);
	return reader->widthEventTimeUs;
}

static void reportWave(Logging *logging, int index) {
//	int counter = getEventCounter(index);
//	debugInt2(logging, "ev", index, counter);

	float dwellMs = getSignalOnTime(index);
	float periodMs = getSignalPeriodMs(index);

	appendPrintf(logging, "duty%d%s", index, DELIMETER);
	appendFloat(logging, 100.0f * dwellMs / periodMs, 2);
	appendPrintf(logging, "%s", DELIMETER);

	/**
	 * that's the ON time of the LAST signal
	 */
	appendPrintf(logging, "dwell%d%s", index, DELIMETER);
	appendFloat(logging, dwellMs, 2);
	appendPrintf(logging, "%s", DELIMETER);

	appendPrintf(logging, "total_dwell%d%s", index, DELIMETER);
	appendFloat(logging, readers[index].prevTotalOnTimeUs / 1000.0f, 2);
	appendPrintf(logging, "%s", DELIMETER);


	appendPrintf(logging, "period%d%s", index, DELIMETER);
	appendFloat(logging, periodMs, 2);
	appendPrintf(logging, "%s", DELIMETER);

	int offset = getWaveOffset(index);
	int crank = getOneDegreeTimeMs(getRpm()) * 360;

	appendPrintf(logging, "advance%d%s", index, DELIMETER);
	appendFloat(logging, 90.0 * offset / crank, 3);
	appendPrintf(logging, "%s", DELIMETER);
}

void printWave(Logging *logging) {
	reportWave(logging, 0);
	reportWave(logging, 1);
}

void initWaveAnalyzer(void) {
#if EFI_WAVE_ANALYZER || defined(__DOXYGEN__)
	initLogging(&logger, "wave");

	initWave(WA_CHANNEL_1, 0);
	initWave(WA_CHANNEL_2, 1);

	addTriggerEventListener(&onWaveShaftSignal, "wave analyzer", (void*) NULL);

	addConsoleActionII("set_logic_input_mode", setWaveModeSilent);

	chThdCreateStatic(waThreadStack, sizeof(waThreadStack), NORMALPRIO, waThread, (void*) NULL);

#else
	print("wave disabled\r\n");
#endif
}
