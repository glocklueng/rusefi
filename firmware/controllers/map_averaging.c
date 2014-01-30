/**
 * @file	map_averaging.c
 *
 * @date Dec 11, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "map_averaging.h"
#include "idle_controller.h" // that's for min/max. todo: move these somewhere?
#include "shaft_position_input.h"
#include "adc_inputs.h"
#include "map.h"
#include "analog_chart.h"
#include "rficonsole_logic.h"
#include "engine_state.h"
#include "engine_configuration.h"
#include "interpolation.h"
#include "signal_executor.h"

#define FAST_MAP_CHART_SKIP_FACTOR 16

static Logging logger;

/**
 * Running counter of measurements per revolution
 */
static volatile int perRevolutionCounter = 0;
/**
 * Number of measurements in previous shaft revolution
 */
static volatile int perRevolution = 0;
/**
 * Running MAP accumulator
 * v_ for Voltage
 */
static volatile float v_mapAccumulator = 0;
/**
 * Running counter of measurements to consider for averaging
 */
static volatile int mapMeasurementsCounter = 0;

static float atmosphericPressure;
static float currentMaxPressure;

/**
 * v_ for Voltage
 */
static float v_averagedMapValue;

extern engine_configuration_s *engineConfiguration;

static scheduling_s startTimer;
static scheduling_s endTimer;

float getAtmosphericPressure(void) {
	return atmosphericPressure;
}

static void startAveraging(void*arg) {
	chSysLockFromIsr()
	;
	// with locking we would have a consistent state
	v_mapAccumulator = 0;
	mapMeasurementsCounter = 0;
	chSysUnlockFromIsr()
	;
}

/**
 * This method is invoked from ADC callback
 */
void mapAveragingCallback(adcsample_t value) {
	/* Calculates the average values from the ADC samples.*/
	perRevolutionCounter++;

	float voltage = adcToVoltsDivided(value);
	float currentPressure = getMapByVoltage(voltage);

	if (engineConfiguration->analogChartMode == AC_MAP)
		if (perRevolutionCounter % FAST_MAP_CHART_SKIP_FACTOR == 0)
			acAddData(getCrankshaftAngle(chTimeNow()), currentPressure);

	currentMaxPressure = maxF(currentMaxPressure, currentPressure);

	chSysLockFromIsr()
	;
	// with locking we would have a consistent state

	v_mapAccumulator += voltage;
	mapMeasurementsCounter++;
	chSysUnlockFromIsr()
	;
}

static void endAveraging(void *arg) {
	chSysLockFromIsr()
	;
	// with locking we would have a consistent state
	v_averagedMapValue = v_mapAccumulator / mapMeasurementsCounter;
	chSysUnlockFromIsr()
	;
}

/**
 * Shaft Position callback used to schedule start and end of MAP averaging
 */
static void shaftPositionCallback(ShaftEvents ckpEventType, int index) {
	// this callback is invoked on interrupt thread
	if (index != 0)
		return;

	perRevolution = perRevolutionCounter;
	perRevolutionCounter = 0;

	atmosphericPressure = currentMaxPressure;
	currentMaxPressure = 0;

	MapConf_s * config = &engineConfiguration->map.config;

	float a_samplingStart = interpolate2d(getCurrentRpm(), config->samplingAngleBins, config->samplingAngle,
			MAP_ANGLE_SIZE);
	float a_samplingWindow = interpolate2d(getCurrentRpm(), config->samplingWindowBins, config->samplingWindow,
			MAP_WINDOW_SIZE);

	scheduleByAngle(&startTimer, a_samplingStart, startAveraging, NULL);
	scheduleByAngle(&endTimer, a_samplingStart + a_samplingWindow, endAveraging, NULL);
}

static void showMapStats(void) {
	scheduleSimpleMsg(&logger, "per revolution", perRevolution);
}

float getMap(void) {
	return getMapByVoltage(v_averagedMapValue);
}

void initMapAveraging(void) {
	initLogging(&logger, "Map Averaging");
	registerShaftPositionListener(&shaftPositionCallback, "rpm reporter");
	addConsoleAction("faststat", showMapStats);
}
