/**
 * @file	speed_density.cpp
 *
 * @date May 29, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "speed_density.h"
#include "interpolation.h"
#include "engine.h"
#include "rpm_calculator.h"

#define K_AT_MIN_RPM_MIN_TPS 0.25
#define K_AT_MIN_RPM_MAX_TPS 0.25
#define K_AT_MAX_RPM_MIN_TPS 0.25
#define K_AT_MAX_RPM_MAX_TPS 0.9

#define rpmMin 500
#define rpmMax 8000

#define tpMin 0
#define tpMax 100
//  http://rusefi.com/math/t_charge.html
float getTCharge(int rpm, int tps, float coolantTemp, float airTemp) {
	float minRpmKcurrentTPS = interpolate(tpMin, K_AT_MIN_RPM_MIN_TPS, tpMax,
	K_AT_MIN_RPM_MAX_TPS, tps);
	float maxRpmKcurrentTPS = interpolate(tpMin, K_AT_MAX_RPM_MIN_TPS, tpMax,
	K_AT_MAX_RPM_MAX_TPS, tps);

	float Tcharge_coff = interpolate(rpmMin, minRpmKcurrentTPS, rpmMax, maxRpmKcurrentTPS, rpm);

	float Tcharge = coolantTemp * (1 - Tcharge_coff) + airTemp * Tcharge_coff;

	return Tcharge;
}

#define GAS_R 287.05

float getSpeedDensityFuel(Engine *engine) {
	int rpm = engine->rpmCalculator->rpm();

	float Vol = engine->engineConfiguration->displacement / engine->engineConfiguration->cylindersCount;
	float tps = 0;
	float coolant = 0;
	float intake = 0;
	float tCharge = getTCharge(rpm, tps, coolant, intake);
	float VE = 0.8;
	float MAP = 0;
	float AFR = 14.7;
	float injectorFlowRate = engine->engineConfiguration->injectorFlow;

	return (Vol * VE * MAP) / (AFR * injectorFlowRate * GAS_R * tCharge);

}

