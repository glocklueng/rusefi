/*
 * @file	engine_math.h
 *
 * @date Jul 13, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_MATH_H_
#define ENGINE_MATH_H_

//float getDefaultVE(int rpm);

float getDefaultFuel(int rpm, float map);
//float getTCharge(int rpm, int tps, float coolantTemp, float airTemp);

float getStartingFuel(float coolantTemperature);

float getOneDegreeTime(int rpm);
float getCrankshaftRevolutionTime(int rpm);

typedef struct {
	float coolantTempMinC;
	float coolantTempMaxC;
	float fuelAtMinTempMs;
	float fuelAtMaxTempMs;

	short int crankingRpm;
} CrankingMode;

#endif /* ENGINE_MATH_H_ */
