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
#include "adc_inputs.h"
#include "map.h"
#include "analog_chart.h"
#include "rficonsole_logic.h"
#include "engine_state.h"

#define FAST_MAP_CHART_SKIP_FACTOR 16

static Logging logger;

static volatile int perRevolutionCounter = 0;
static volatile int perRevolution = 0;

static volatile int fastAccumulator = 0;
static volatile int fastMax = 0;
static volatile int fastMin = 9999999;

static float atmosphericPressure;
static float currentMaxPressure;

float getAtmosphericPressure(void) {
	return atmosphericPressure;
}

void mapAveragingCallback(adcsample_t value) {
	/* Calculates the average values from the ADC samples.*/
	perRevolutionCounter++;

	float voltage = adcToVolts(value);
	float currentPressure = getMapByVoltage(voltage);

	if (perRevolutionCounter % FAST_MAP_CHART_SKIP_FACTOR == 0)
		acAddData(getCrankshaftAngle(chTimeNow()), currentPressure);

	currentMaxPressure = max(currentMaxPressure, currentPressure);

	chSysLockFromIsr()
	;
//		newState.time = chTimeNow();
//		for (int i = 0; i < ADC_NUMBER_CHANNELS_SLOW; i++) {

	fastAccumulator += value;
	fastMax = max(fastMax, value);
	fastMin = min(fastMin, value);
	chSysUnlockFromIsr()
	;

//			newState.adc_data[i] = value;

}

static void shaftPositionCallback(ShaftEvents ckpEventType, int index) {
	// this callback is invoked on interrupt thread
	if (index != 0)
		return;

	perRevolution = perRevolutionCounter;
	perRevolutionCounter = 0;

	atmosphericPressure = currentMaxPressure;
	currentMaxPressure = 0;

}

static void showMapStats(void) {
	scheduleSimpleMsg(&logger, "per revolution", perRevolution);
}

void initMapAveraging(void) {
	initLogging(&logger, "Map Averaging");
	registerShaftPositionListener(&shaftPositionCallback, "rpm reporter");
	addConsoleAction("faststat", showMapStats);
}
