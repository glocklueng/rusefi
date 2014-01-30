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
extern engine_configuration_s *engineConfiguration;
extern engine_configuration2_s *engineConfiguration2;

float getStartingFuel(float coolantTemperature) {
	// these magic constants are in Celsius
	if (isnan(coolantTemperature) || coolantTemperature < engineConfiguration->crankingSettings.coolantTempMinC)
		return engineConfiguration->crankingSettings.fuelAtMinTempMs;
	if (coolantTemperature > engineConfiguration->crankingSettings.coolantTempMaxC)
		return engineConfiguration->crankingSettings.fuelAtMaxTempMs;
	return interpolate(
			engineConfiguration->crankingSettings.coolantTempMinC,
			engineConfiguration->crankingSettings.fuelAtMinTempMs,
			engineConfiguration->crankingSettings.coolantTempMaxC,
			engineConfiguration->crankingSettings.fuelAtMaxTempMs,
			coolantTemperature);
}

/**
 * @return time needed to rotate crankshaft by one degree
 */
float getOneDegreeTime(int rpm) {
	return 1000.0 * 60 * TICKS_IN_MS  / 360 / rpm;
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

//float getTriggerEventAngle(int triggerEventIndex) {
//	return 0;
//}
