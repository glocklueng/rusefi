/*
 * engine_math.c
 *
 *  Created on: Jul 13, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "engine_math.h"

#define INTERPOLATION_A(x1, y1, x2, y2) ((y1 - y2) / (x1 - x2))

/**
 * linear interpolation
 */

float interpolate(float x1, float y1, float x2, float y2, float x) {
	// a*x1 + b = y1
	// a*x2 + b = y2
//	chDbgCheck(x1 != x2, "no way we can interpolate");
	float a = INTERPOLATION_A(x1, y1, x2, y2);
	float b = y1 - a * x1;
	float result = a * x + b;
//	printf("a=%f b=%f x=%f result=%f\r\n", a, b, x, result);
	return result;
}

#define Honda_Denso183_Min -6.64
#define Honda_Denso183_Max 182.78
#define Honda_Denso183_Range (Honda_Denso183_Max - Honda_Denso183_Min)

/**
 * returns kPa value
 */
float getMAPValue(float volts) {
	return Honda_Denso183_Range / 5 * volts + Honda_Denso183_Min;
}

/**
 * default Volumetric Efficiency
 */
float getDefaultVE(int rpm) {
	if (rpm > 5000)
		return interpolate(5000, 1.1, 8000, 1, rpm);
	return interpolate(500, 0.5, 5000, 1.1, rpm);
}

#define K_AT_MIN_RPM_MIN_TPS 0.25
#define K_AT_MIN_RPM_MAX_TPS 0.25
#define K_AT_MAX_RPM_MIN_TPS 0.25
#define K_AT_MAX_RPM_MAX_TPS 0.9

#define rpmMin 500
#define rpmMax 8000

#define tpMin 0
#define tpMax 100

float getDefaultFuel(int rpm, float map) {
	return 0.11558472166666668 * map + 0.01037;
}

/**
 * http://rusefi.com/math/t_charge.html
 */
float getTCharge(int rpm, int tps, float coolantTemp, float airTemp) {
	float minRpmKcurrentTPS = interpolate(tpMin, K_AT_MIN_RPM_MIN_TPS, tpMax, K_AT_MIN_RPM_MAX_TPS, tps);
	float maxRpmKcurrentTPS = interpolate(tpMin, K_AT_MAX_RPM_MIN_TPS, tpMax, K_AT_MAX_RPM_MAX_TPS, tps);

	float Tcharge_coff = interpolate(rpmMin, minRpmKcurrentTPS, rpmMax, maxRpmKcurrentTPS, rpm);

	float Tcharge = coolantTemp * (1 - Tcharge_coff) + airTemp * Tcharge_coff;

	return Tcharge;
}

/**
 * return the index of sorted array such that array[i] is
 * greater that value
 *
 * return index of last array element (size - 1) is value is
 * higher than last value
 */
int findIndex(float array[], int size, float value) {

	for (int i = 0; i < size; i++) {
		if (value <= array[i])
			return i;
	}
	return size - 1;
}

#define MAX_STARTING_FUEL 15
#define MIN_STARTING_FUEL 8

float getStartingFuel(int coolantTemperature) {
	if (coolantTemperature < 60)
		return MAX_STARTING_FUEL;
	if (coolantTemperature > 150)
		return MIN_STARTING_FUEL;
	return interpolate(60, MAX_STARTING_FUEL, 150, MIN_STARTING_FUEL, coolantTemperature);
}
