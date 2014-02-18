/**
 * @file	trigger_input.c
 * @brief	Position sensor hardware layer
 *
 * @date Dec 30, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "trigger_input.h"

#include "rficonsole.h"

#include "wave_math.h"
#include "data_buffer.h"
#include "wave_analyzer_hw.h"
#include "pinout.h"
#include "pin_repository.h"

#include "trigger_decoder.h"
#include "engine_configuration.h"
#include "histogram.h"
#include "main_trigger_callback.h"

#if defined __GNUC__
static histogram_s triggerCallback __attribute__((section(".ccm")));
#else
static histogram_s triggerCallback;
#endif

extern engine_configuration_s *engineConfiguration;
extern engine_configuration2_s *engineConfiguration2;

// we need this initial to have not_running at first invocation
static volatile time_t previousShaftEventTime = (time_t)-10 * CH_FREQUENCY;

static IntListenerArray triggerListeneres;

static Logging logger;

static trigger_state_s triggerState;

static volatile int shaftEventCounter;

static WaveReaderHw primaryCrankInput;
static WaveReaderHw secondaryCrankInput;

int getCrankEventCounter() {
	return shaftEventCounter;
}

void registerShaftPositionListener(ShaftPositionListener handler, char *msg) {
	print("registerCkpListener: %s\r\n", msg);
	registerCallback(&triggerListeneres, (IntListener) handler, NULL);
}

#if EFI_SHAFT_POSITION_INPUT

void hwHandleShaftSignal(ShaftEvents signal) {
	int beforeCallback = hal_lld_get_counter_value();

	time_t now = chTimeNow();

	if (overflowDiff(now, previousShaftEventTime) > CH_FREQUENCY) {
		/**
		 * We are here if there is a time gap between now and previous shaft event - that means the engine is not runnig.
		 * That means we have lost synchronization since the engine is not running :)
		 */
		triggerState.shaft_is_synchronized = FALSE;
	}
	previousShaftEventTime = now;
	// this is not atomic, but it's fine here
	shaftEventCounter++;

	/**
	 * This invocation changes the state of
	 */
	processTriggerEvent(&triggerState, &engineConfiguration2->triggerShape,
			&engineConfiguration->triggerConfig,
			signal, now);

	if (!triggerState.shaft_is_synchronized)
		return; // we should not propagate event if we do not know where we are


	/**
	 * Here we invoke all the listeners - the main engine control logic is inside these listeners
	 */
	invokeIntIntCallbacks(&triggerListeneres, signal, triggerState.current_index);
	int afterCallback = hal_lld_get_counter_value();
	int diff = afterCallback - beforeCallback;
	// this counter is only 32 bits so it overflows every minute, let's ignore the value in case of the overflow for simplicity
	if (diff > 0) {
		hsAdd(&triggerCallback, diff);
	}
}

/**
 * that's hardware timer input capture IRQ entry point
 * 'width' events happens before the 'period' event
 */
static void shaft_icu_width_callback(ICUDriver *icup) {
	//	icucnt_t last_width = icuGetWidth(icup); so far we are fine with system time
	ShaftEvents signal = icup == &PRIMARY_SHAFT_POSITION_INPUT_DRIVER ? SHAFT_PRIMARY_UP : SHAFT_SECONDARY_UP;

	hwHandleShaftSignal(signal);
}

static void shaft_icu_period_callback(ICUDriver *icup) {
	//	icucnt_t last_period = icuGetPeriod(icup); so far we are fine with system time
	ShaftEvents signal = icup == &PRIMARY_SHAFT_POSITION_INPUT_DRIVER ? SHAFT_PRIMARY_DOWN : SHAFT_SECONDARY_DOWN;
	hwHandleShaftSignal(signal);
}

/**
 * the main purpose of this configuration structure is to specify the input interrupt callbacks
 */
static ICUConfig shaft_icucfg = { ICU_INPUT_ACTIVE_LOW, 100000, /* 100kHz ICU clock frequency.   */
shaft_icu_width_callback, shaft_icu_period_callback };
#endif

static void showTriggerHistogram(void) {
	printHistogram(&logger, &triggerCallback);
	showMainHistogram();
}

void initShaftPositionInputCapture(void) {
	initLogging(&logger, "ShaftPosition");

	resetHistogram(&triggerCallback, "trigger");
	initTriggerDecoder();
	clearTriggerState(&triggerState);

	addConsoleAction("trigger_hist", showTriggerHistogram);

#if EFI_SHAFT_POSITION_INPUT

	// initialize primary Input Capture Unit pin
	initWaveAnalyzerDriver(&primaryCrankInput, &PRIMARY_SHAFT_POSITION_INPUT_DRIVER, PRIMARY_SHAFT_POSITION_INPUT_PORT,
	PRIMARY_SHAFT_POSITION_INPUT_PIN);
	/**
	 * Start primary Input Capture Unit using given configuration
	 * @see shaft_icucfg for callback entry points
	 */
	shaft_icucfg.channel = PRIMARY_SHAFT_POSITION_INPUT_CHANNEL;
	print("initShaftPositionInputCapture 1 %s:%d\r\n", portname(PRIMARY_SHAFT_POSITION_INPUT_PORT),
			PRIMARY_SHAFT_POSITION_INPUT_PIN);
	icuStart(&PRIMARY_SHAFT_POSITION_INPUT_DRIVER, &shaft_icucfg);
	icuEnable(&PRIMARY_SHAFT_POSITION_INPUT_DRIVER);

	// initialize secondary Input Capture Unit pin
	initWaveAnalyzerDriver(&secondaryCrankInput, &SECONDARY_SHAFT_POSITION_INPUT_DRIVER,
			SECONDARY_SHAFT_POSITION_INPUT_PORT,
			SECONDARY_SHAFT_POSITION_INPUT_PIN);
	shaft_icucfg.channel = SECONDARY_SHAFT_POSITION_INPUT_CHANNEL;
	print("initShaftPositionInputCapture 2 %s:%d\r\n", portname(SECONDARY_SHAFT_POSITION_INPUT_PORT),
			SECONDARY_SHAFT_POSITION_INPUT_PIN);
	icuStart(&SECONDARY_SHAFT_POSITION_INPUT_DRIVER, &shaft_icucfg);
	icuEnable(&SECONDARY_SHAFT_POSITION_INPUT_DRIVER);

#else
	print("crank input disabled\r\n");
#endif
}
