/**
 * @file	adc_averaging.c
 *
 * @date Dec 11, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "adc_averaging.h"
#include "idle_controller.h" // that's for min/max. todo: move these somewhere?

static volatile int fastCounter = 0;
static volatile int fastAccumulator = 0;
static volatile int fastMax = 0;
static volatile int fastMin = 9999999;
static int adcCallbackCounter_fast = 0;

void adcAveragingLogic(adcsample_t newValue) {
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
