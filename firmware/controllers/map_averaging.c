/**
 * @file	map_averaging.c
 *
 * @date Dec 11, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 *
 * This file is part of rusEfi - see http://rusefi.com
 *
 * rusEfi is free software; you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * rusEfi is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "main.h"
#include "map_averaging.h"
#include "trigger_central.h"
#include "adc_inputs.h"
#include "map.h"
#include "analog_chart.h"
#include "engine_state.h"
#include "engine_configuration.h"
#include "interpolation.h"
#include "signal_executor.h"

#if EFI_MAP_AVERAGING

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

static float currentMaxPressure;

/**
 * v_ for Voltage
 */
static float v_averagedMapValue;

extern engine_configuration_s *engineConfiguration;

static scheduling_s startTimer;
static scheduling_s endTimer;

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
			acAddData(getCrankshaftAngle(getTimeNowUs()), currentPressure);

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

	int rpm = getRpm();
	if(!isValidRpm(rpm))
		return;

	perRevolution = perRevolutionCounter;
	perRevolutionCounter = 0;

	currentMaxPressure = 0;

	MAP_sensor_config_s * config = &engineConfiguration->map;

	float startAngle = interpolate2d(rpm, config->samplingAngleBins, config->samplingAngle, MAP_ANGLE_SIZE);
	float windowAngle = interpolate2d(rpm, config->samplingWindowBins, config->samplingWindow, MAP_WINDOW_SIZE);

	// todo: schedule this based on closest trigger event, same as ignition works
	scheduleByAngle(&startTimer, startAngle, startAveraging, NULL);
	scheduleByAngle(&endTimer, startAngle + windowAngle, endAveraging, NULL);
}

static void showMapStats(void) {
	scheduleMsg(&logger, "per revolution %d", perRevolution);
}

float getMapVoltage(void) {
	return v_averagedMapValue;
}

/**
 * because of MAP window averaging, MAP is only available while engine is spinning
 */
float getMap(void) {
	if (getRpm() == 0)
		return getRawMap(); // maybe return NaN and have a
	return getMapByVoltage(v_averagedMapValue);
}

void initMapAveraging(void) {
	initLogging(&logger, "Map Averaging");
	addTriggerEventListener(&shaftPositionCallback, "rpm reporter");
	addConsoleAction("faststat", showMapStats);
}

#else

float getMap(void) {
	return getRawMap();
}

#endif /* EFI_MAP_AVERAGING */
