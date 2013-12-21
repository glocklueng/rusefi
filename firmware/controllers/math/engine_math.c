/**
 * @file	engine_math.c
 * @brief
 *
 * @date Jul 13, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include <stdio.h>

#include "engine_math.h"
#include "engine_configuration.h"
#include "main.h"
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
extern EngineConfiguration *engineConfiguration;
extern EngineConfiguration2 *engineConfiguration2;

float getStartingFuel(int coolantTemperature) {
	// these magic constants are in Celsius
	if (coolantTemperature < engineConfiguration->crankingSettings.coolantTempMin)
		return engineConfiguration->crankingSettings.minTempPW;
	if (coolantTemperature > engineConfiguration->crankingSettings.coolantTempMax)
		return engineConfiguration->crankingSettings.maxTempPW;
	return interpolate(
			engineConfiguration->crankingSettings.coolantTempMin,
			engineConfiguration->crankingSettings.minTempPW,
			engineConfiguration->crankingSettings.coolantTempMax,
			engineConfiguration->crankingSettings.maxTempPW,
			coolantTemperature);
}

/**
 * @return number of system it needed for one crankshaft revolution
 */
float getCrankshaftRevolutionTime(int rpm) {
	return 1000.0 * 60 * TICKS_IN_MS / rpm;
}

// todo: the problem with this method is that it takes CAMSHAFT angle
int convertAngleToSysticks(int rpm, int angle) {

	return (int) (angle * getCrankshaftRevolutionTime(rpm) / engineConfiguration2->rpmMultiplier / 360);
}
