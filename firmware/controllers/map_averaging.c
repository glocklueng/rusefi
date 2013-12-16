/**
 * @file	adc_averaging.c
 *
 * @date Dec 11, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "map_averaging.h"
#include "idle_controller.h" // that's for min/max. todo: move these somewhere?
#include "ckp_events.h"
#include "shaft_position_input.h"

static Logging logger;

static volatile int fastCounter = 0;
static volatile int fastAccumulator = 0;
static volatile int fastMax = 0;
static volatile int fastMin = 9999999;
static int adcCallbackCounter_fast = 0;

static float atmosphericPressure;
static float currentMaxPressure;

float getAtmosphericPressure(void) {
	return atmosphericPressure;
}

void mapAveragingCallback(adcsample_t newValue) {
	/* Calculates the average values from the ADC samples.*/
	adcCallbackCounter_fast++;


	chSysLockFromIsr()
	;
//		newState.time = chTimeNow();
//		for (int i = 0; i < ADC_NUMBER_CHANNELS_SLOW; i++) {

	fastAccumulator += newValue;
	fastMax = max(fastMax, newValue);
	fastMin = min(fastMin, newValue);
	fastCounter++;
	chSysUnlockFromIsr()
	;

//			newState.adc_data[i] = value;

}

static void shaftPositionCallback(ShaftEvents ckpEventType, int index) {
	// this callback is invoked on interrupt thread
	if (index != 0)
		return;

}


void initMapAveraging(void) {
	initLogging(&logger, "Map Averaging");
	registerShaftPositionListener(&shaftPositionCallback, "rpm reporter");
}
