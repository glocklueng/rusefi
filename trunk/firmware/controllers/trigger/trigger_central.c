/*
 * @file	trigger_central.c
 *
 * @date Feb 23, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include <string.h>

#include "trigger_central.h"
#include "trigger_decoder.h"
#include "main_trigger_callback.h"
#include "engine_configuration.h"
#include "histogram.h"
#include "rfiutil.h"
#include "listener_array.h"
#include "wave_math.h"
#include "data_buffer.h"

#if defined __GNUC__
static histogram_s triggerCallback __attribute__((section(".ccm")));
#else
static histogram_s triggerCallback;
#endif

extern engine_configuration_s *engineConfiguration;
extern engine_configuration2_s *engineConfiguration2;

// we need this initial to have not_running at first invocation
static volatile time_t previousShaftEventTime = (time_t) -10 * CH_FREQUENCY;

static IntListenerArray triggerListeneres;

static Logging logging;

static trigger_state_s triggerState;

static volatile int shaftEventCounter;

int getCrankEventCounter() {
	return shaftEventCounter;
}

void registerShaftPositionListener(ShaftPositionListener handler, char *msg) {
	print("registerCkpListener: %s\r\n", msg);
	registerCallback(&triggerListeneres, (IntListener) handler, NULL);
}

#define HW_EVENT_TYPES 4

static int hwEventCounters[HW_EVENT_TYPES];

void hwHandleShaftSignal(ShaftEvents signal) {
	int beforeCallback = hal_lld_get_counter_value();
	int eventIndex = (int) signal;
	chDbgCheck(eventIndex >= 0 && eventIndex < HW_EVENT_TYPES, "signal type");
	hwEventCounters[eventIndex]++;

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
	processTriggerEvent(&triggerState, &engineConfiguration2->triggerShape, &engineConfiguration->triggerConfig, signal,
			now);

	if (!triggerState.shaft_is_synchronized)
		return; // we should not propagate event if we do not know where we are

	if (triggerState.current_index >= engineConfiguration2->triggerShape.shaftPositionEventCount) {
		warning("unexpected eventIndex=", triggerState.current_index);
		for (int i = 0; i < HW_EVENT_TYPES; i++)
			scheduleMsg(&logging, "event type: %d count=%d", i, hwEventCounters[i]);
	} else {

		/**
		 * Here we invoke all the listeners - the main engine control logic is inside these listeners
		 */
		invokeIntIntCallbacks(&triggerListeneres, signal, triggerState.current_index);
	}
	int afterCallback = hal_lld_get_counter_value();
	int diff = afterCallback - beforeCallback;
	// this counter is only 32 bits so it overflows every minute, let's ignore the value in case of the overflow for simplicity
	if (diff > 0)
		hsAdd(&triggerCallback, diff);
}

void printAllCallbacksHistogram(void) {
	printHistogram(&logging, &triggerCallback);
}

void initTriggerCentral(void) {
	initLogging(&logging, "ShaftPosition");

	memset(hwEventCounters, 0, sizeof(hwEventCounters));

	resetHistogram(&triggerCallback, "trigger");
	initTriggerDecoder();
	clearTriggerState(&triggerState);
}
