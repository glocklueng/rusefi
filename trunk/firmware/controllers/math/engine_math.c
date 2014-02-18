/**
 * @file	engine_math.c
 * @brief
 *
 * @date Jul 13, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include <stdio.h>

#include "engine_math.h"
#include "main.h"
#include "engine_configuration.h"
#include "interpolation.h"
#include "allsensors.h"
#include "io_pins.h"

/*
 * default Volumetric Efficiency
 */
//float getDefaultVE(int rpm) {
//	if (rpm > 5000)
//		return interpolate(5000, 1.1, 8000, 1, rpm);
//	return interpolate(500, 0.5, 5000, 1.1, rpm);
//}
//#define K_AT_MIN_RPM_MIN_TPS 0.25
//#define K_AT_MIN_RPM_MAX_TPS 0.25
//#define K_AT_MAX_RPM_MIN_TPS 0.25
//#define K_AT_MAX_RPM_MAX_TPS 0.9
//
//#define rpmMin 500
//#define rpmMax 8000
//
//#define tpMin 0
//#define tpMax 100
//
//  http://rusefi.com/math/t_charge.html
// /
//float getTCharge(int rpm, int tps, float coolantTemp, float airTemp) {
//	float minRpmKcurrentTPS = interpolate(tpMin, K_AT_MIN_RPM_MIN_TPS, tpMax,
//	K_AT_MIN_RPM_MAX_TPS, tps);
//	float maxRpmKcurrentTPS = interpolate(tpMin, K_AT_MAX_RPM_MIN_TPS, tpMax,
//	K_AT_MAX_RPM_MAX_TPS, tps);
//
//	float Tcharge_coff = interpolate(rpmMin, minRpmKcurrentTPS, rpmMax,
//			maxRpmKcurrentTPS, rpm);
//
//	float Tcharge = coolantTemp * (1 - Tcharge_coff) + airTemp * Tcharge_coff;
//
//	return Tcharge;
//}
#define MAX_STARTING_FUEL 15
#define MIN_STARTING_FUEL 8

/**
 * @return time needed to rotate crankshaft by one degree, in milliseconds.
 */
float getOneDegreeTimeMs(int rpm) {
	return 1000.0 * 60 / 360 / rpm;
}

/**
 * @return time needed to rotate crankshaft by one degree, in systicks
 */
float getOneDegreeTime(int rpm) {
	return getOneDegreeTimeMs(rpm) * TICKS_IN_MS;
}

/**
 * @return number of system it needed for one crankshaft revolution
 */
float getCrankshaftRevolutionTime(int rpm) {
	return 360 * getOneDegreeTime(rpm);
}

/**
 * @brief Shifts angle into the [0..720) range
 * TODO: should be 'crankAngleRange' range?
 */
float fixAngle(float angle) {
	// I guess this implementation would be faster than 'angle % 720'
	while (angle < 0)
		angle += 720;
	while (angle > 720)
		angle -= 720;
	return angle;
}

/**
 * @brief Returns engine load according to selected engine_load_mode
 *
 */
float getEngineLoadT(engine_configuration_s *engineConfiguration) {
	switch (engineConfiguration->engine_load_mode) {
	case LM_MAF:
		return getMaf();
	case LM_MAP:
		return getMap();
	case LM_TPS:
		return getTPS();
	case LM_SPEED_DENSITY:
		// TODO: real implementation
		return getMap();
	default:
		fatal("Unexpected engine load parameter");
		return -1;
	}
}

int isCrankingRT(engine_configuration_s *engineConfiguration, int rpm) {
	return rpm > 0 && rpm < engineConfiguration->crankingSettings.crankingRpm;
}

void initializeIgnitionActions(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2) {
	EventHandlerConfiguration *config = &engineConfiguration2->engineEventConfiguration;
	resetEventList(&config->ignitionEvents);
	chDbgCheck(engineConfiguration->cylindersCount > 0, "cylindersCount");

	int x = 13; //todo

	if (engineConfiguration->ignitionMode == IM_ONE_COIL) {

		for (int i = 0; i < engineConfiguration->cylindersCount; i++)
			registerActuatorEventExt(&config->ignitionEvents, addOutputSignal(SPARKOUT_1_OUTPUT),
					x + 720.0 * i / engineConfiguration->cylindersCount);

	} else
		fatal("unfinished initializeIgnitionActions");

}

/**
 * @return Spark dwell time, in milliseconds.
 */
float getSparkDwellMsT(engine_configuration_s *engineConfiguration, int rpm) {
	if (isCrankingR(rpm)) {
		float angle = engineConfiguration->crankingChargeAngle;
		return getOneDegreeTimeMs(rpm) * angle;
	}

	if (rpm > engineConfiguration->rpmHardLimit) {
		warning("skipping spark due to rpm=", rpm);
		return 0;
	}
	int defaultDwell = 4;
	if (rpm <= 4500)
		return defaultDwell;
	rpm -= 4500;
	/**
	 * at higher RPM we simply do not have enough time to charge the coil completely
	 */
	// for each 2000 rpm above 4500 rom we reduce dwell by 1 ms
	float dec = rpm / 2000.0;
	return defaultDwell - dec;
}


//float getTriggerEventAngle(int triggerEventIndex) {
//	return 0;
//}


