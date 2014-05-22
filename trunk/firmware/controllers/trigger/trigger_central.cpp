/*
 * @file	trigger_central.c
 *
 * @date Feb 23, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
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

// we need this initial to have not_running at first invocation
static volatile uint64_t previousShaftEventTime = (efitimems_t) -10 * US_PER_SECOND;

TriggerCentral triggerCentral;

static Logging logging;

static TriggerState triggerState;

uint64_t getCrankEventCounter() {
	return triggerState.getTotalEventCounter();
}

uint64_t getStartOfRevolutionIndex() {
	return triggerState.getStartOfRevolutionIndex();
}

void TriggerCentral::addEventListener(ShaftPositionListener listener, const char *name, void *arg) {
	print("registerCkpListener: %s\r\n", name);
	registerCallback(&triggerListeneres, (IntListener) listener, arg);
}

/**
 * @brief Adds a trigger event listener
 *
 * Trigger event listener would be invoked on each trigger event. For example, for a 60/2 wheel
 * that would be 116 events: 58 SHAFT_PRIMARY_UP and 58 SHAFT_PRIMARY_DOWN events.
 */
void addTriggerEventListener(ShaftPositionListener listener, const char *name, void *arg) {
	triggerCentral.addEventListener(listener, name, arg);
}

extern configuration_s *configuration;

void hwHandleShaftSignal(ShaftEvents signal) {
	triggerCentral.handleShaftSignal(configuration, signal, getTimeNowUs());
}

TriggerCentral::TriggerCentral() {
	memset(hwEventCounters, 0, sizeof(hwEventCounters));
}

void TriggerCentral::handleShaftSignal(configuration_s *configuration, ShaftEvents signal, uint64_t nowUs) {
	efiAssertVoid(configuration!=NULL, "configuration");

	efiAssertVoid(configuration->engineConfiguration!=NULL, "engineConfiguration");
	efiAssertVoid(configuration->engineConfiguration2!=NULL, "engineConfiguration2");

	int beforeCallback = hal_lld_get_counter_value();
	int eventIndex = (int) signal;
	efiAssertVoid(eventIndex >= 0 && eventIndex < HW_EVENT_TYPES, "signal type");
	hwEventCounters[eventIndex]++;

	if (nowUs - previousShaftEventTime > US_PER_SECOND) {
		/**
		 * We are here if there is a time gap between now and previous shaft event - that means the engine is not runnig.
		 * That means we have lost synchronization since the engine is not running :)
		 */
		triggerState.shaft_is_synchronized = FALSE;
	}
	previousShaftEventTime = nowUs;

	/**
	 * This invocation changes the state of
	 */
	processTriggerEvent(&triggerState, &configuration->engineConfiguration2->triggerShape,
			&configuration->engineConfiguration->triggerConfig, signal, nowUs);

	if (!triggerState.shaft_is_synchronized)
		return; // we should not propagate event if we do not know where we are

	if (triggerState.getCurrentIndex() >= configuration->engineConfiguration2->triggerShape.shaftPositionEventCount) {
		int f = warning(OBD_PCM_Processor_Fault, "unexpected eventIndex=%d", triggerState.getCurrentIndex());
		if (!f) {
			for (int i = 0; i < HW_EVENT_TYPES; i++)
				scheduleMsg(&logging, "event type: %d count=%d", i, hwEventCounters[i]);
		}
	} else {

		/**
		 * Here we invoke all the listeners - the main engine control logic is inside these listeners
		 */
		invokeIntIntVoidCallbacks(&triggerListeneres, signal, triggerState.getCurrentIndex());
	}
	int afterCallback = hal_lld_get_counter_value();
#if EFI_HISTOGRAMS
	int diff = afterCallback - beforeCallback;
	// this counter is only 32 bits so it overflows every minute, let's ignore the value in case of the overflow for simplicity
	if (diff > 0)
	hsAdd(&triggerCallback, diff);
#endif /* EFI_HISTOGRAMS */
}

void printAllCallbacksHistogram(void) {
	printHistogram(&logging, &triggerCallback);
}

void initTriggerCentral(void) {
	initLogging(&logging, "ShaftPosition");

#if EFI_HISTOGRAMS
	initHistogram(&triggerCallback, "all callbacks");
#endif /* EFI_HISTOGRAMS */
	initTriggerDecoder();
}
