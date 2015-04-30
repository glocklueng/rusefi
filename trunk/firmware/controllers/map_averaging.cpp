/**
 * @file	map_averaging.cpp
 *
 * @date Dec 11, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
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
#include "efilib2.h"
#include "map.h"

#if EFI_MAP_AVERAGING || defined(__DOXYGEN__)

#include "map_averaging.h"
#include "trigger_central.h"
#include "adc_inputs.h"
#include "engine_state.h"
#include "engine_configuration.h"
#include "interpolation.h"
#include "signal_executor.h"
#include "engine.h"
#include "engine_math.h"

#if EFI_ANALOG_CHART
#include <sensor_chart.h>
#endif /* EFI_ANALOG_CHART */

#define FAST_MAP_CHART_SKIP_FACTOR 16

static Logging *logger;
static NamedOutputPin mapAveragingPin("map");

/**
 * Running counter of measurements per revolution
 */
static volatile int perRevolutionCounter = 0;
/**
 * Number of measurements in previous shaft revolution
 */
static volatile int perRevolution = 0;

/**
 * In this lock-free imlementation 'readIndex' is always pointing
 * to the consistent copy of accumulator and counter pair
 */
static int readIndex = 0;
static float accumulators[2];
static int counters[2];


/**
 * Running MAP accumulator
 */
static volatile float mapAccumulator = 0;
/**
 * Running counter of measurements to consider for averaging
 */
static volatile int mapMeasurementsCounter = 0;

/**
 * v_ for Voltage
 */
static float v_averagedMapValue;

EXTERN_ENGINE;

static scheduling_s startTimer[2];
static scheduling_s endTimer[2];

/**
 * that's a performance optimization: let's not bother averaging
 * if we are outside of of the window
 */
static bool_t isAveraging = false;

static void startAveraging(void *arg) {
	(void) arg;
	efiAssertVoid(getRemainingStack(chThdSelf()) > 128, "lowstck#9");
	bool wasLocked = lockAnyContext();
	;
	// with locking we would have a consistent state
	mapAccumulator = 0;
	mapMeasurementsCounter = 0;
	isAveraging = true;
	if (!wasLocked)
		chSysUnlockFromIsr()
	;
	turnPinHigh(&mapAveragingPin);
}

#if EFI_PROD_CODE || defined(__DOXYGEN__)
/**
 * This method is invoked from ADC callback.
 * @note This method is invoked OFTEN, this method is a potential bottle-next - the implementation should be
 * as fast as possible
 */
void mapAveragingCallback(adcsample_t adcValue) {
	if(!isAveraging && boardConfiguration->sensorChartMode != SC_MAP) {
		return;
	}

	/* Calculates the average values from the ADC samples.*/
	perRevolutionCounter++;
	efiAssertVoid(getRemainingStack(chThdSelf()) > 128, "lowstck#9a");


#if (EFI_ANALOG_CHART && EFI_ANALOG_SENSORS) || defined(__DOXYGEN__)
	if (boardConfiguration->sensorChartMode == SC_MAP)
		if (perRevolutionCounter % FAST_MAP_CHART_SKIP_FACTOR == 0) {
			float voltage = adcToVoltsDivided(adcValue);
			float currentPressure = getMapByVoltage(voltage);
			scAddData(getCrankshaftAngleNt(getTimeNowNt() PASS_ENGINE_PARAMETER), currentPressure);
		}
#endif /* EFI_ANALOG_CHART */

	/**
	 * Local copy is now safe, but it's an overkill: we only
	 * have one writing thread anyway
	 */
	int readIndexLocal = readIndex;
	int writeIndex = readIndexLocal ^ 1;
	accumulators[writeIndex] = accumulators[readIndexLocal] + adcValue;
	counters[writeIndex] = counters[readIndexLocal] + 1;
	// this would commit the new pair of values
	readIndex = writeIndex;

	// todo: migrate to the lock-free implementation
	chSysLockFromIsr()
	;
	// with locking we would have a consistent state

	mapAccumulator += adcValue;
	mapMeasurementsCounter++;
	chSysUnlockFromIsr()
	;
}
#endif

static void endAveraging(void *arg) {
	(void) arg;
	bool wasLocked = lockAnyContext();
	isAveraging = false;
	// with locking we would have a consistent state
#if EFI_PROD_CODE || defined(__DOXYGEN__)
	v_averagedMapValue = adcToVoltsDivided(mapAccumulator / mapMeasurementsCounter);
#endif
	if (!wasLocked)
		chSysUnlockFromIsr()
	;
	turnPinLow(&mapAveragingPin);
}

/**
 * Shaft Position callback used to schedule start and end of MAP averaging
 */
static void mapAveragingCallback(trigger_event_e ckpEventType, uint32_t index DECLARE_ENGINE_PARAMETER_S) {
	// this callback is invoked on interrupt thread
	engine->m.beforeMapAveragingCb = GET_TIMESTAMP();
	if (index != CONFIG(mapAveragingSchedulingAtIndex))
		return;

	int rpm = ENGINE(rpmCalculator.rpmValue);
	if (!isValidRpm(rpm))
		return;

	perRevolution = perRevolutionCounter;
	perRevolutionCounter = 0;

	angle_t currentAngle = TRIGGER_SHAPE(eventAngles[index]);

	angle_t samplingStart = ENGINE(engineState.mapAveragingStart) - currentAngle;
	fixAngle(samplingStart);

	angle_t samplingDuration = ENGINE(engineState.mapAveragingDuration);
	if (samplingDuration <= 0) {
		firmwareError("map sampling angle should be positive");
		return;
	}

	angle_t samplingEnd = samplingStart + samplingDuration;
	fixAngle(samplingEnd);
	if (cisnan(samplingEnd)) {
		// value is not yet prepared
		return;
	}

	int structIndex = getRevolutionCounter() % 2;
	// todo: schedule this based on closest trigger event, same as ignition works
	scheduleByAngle(rpm, &startTimer[structIndex], samplingStart, startAveraging, NULL, &engine->rpmCalculator);
	scheduleByAngle(rpm, &endTimer[structIndex], samplingEnd, endAveraging, NULL, &engine->rpmCalculator);
	engine->m.mapAveragingCbTime = GET_TIMESTAMP() - engine->m.beforeMapAveragingCb;
}

static void showMapStats(void) {
	scheduleMsg(logger, "per revolution %d", perRevolution);
}

float getMapVoltage(void) {
	return v_averagedMapValue;
}

#if EFI_PROD_CODE || defined(__DOXYGEN__)

/**
 * Because of MAP window averaging, MAP is only available while engine is spinning
 * @return Manifold Absolute Pressure, in kPa
 */
float getMap(void) {
#if EFI_ANALOG_SENSORS || defined(__DOXYGEN__)
	if (!isValidRpm(engine->rpmCalculator.rpmValue))
		return getRawMap(); // maybe return NaN in case of stopped engine?
	return getMapByVoltage(v_averagedMapValue);
#else
	return 100;
#endif
}
#endif /* EFI_PROD_CODE */

void initMapAveraging(Logging *sharedLogger, Engine *engine) {
	logger = sharedLogger;

//	startTimer[0].name = "map start0";
//	startTimer[1].name = "map start1";
//	endTimer[0].name = "map end0";
//	endTimer[1].name = "map end1";

	addTriggerEventListener(&mapAveragingCallback, "MAP averaging", engine);
	addConsoleAction("faststat", showMapStats);
}

#else

#if EFI_PROD_CODE

float getMap(void) {
#if EFI_ANALOG_SENSORS || defined(__DOXYGEN__)
	return getRawMap();
#else
	return NAN;
#endif /* EFI_ANALOG_SENSORS */
}
#endif /* EFI_PROD_CODE */

#endif /* EFI_MAP_AVERAGING */
