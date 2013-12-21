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

float getStartingFuel(int coolantTemperature);

int convertAngleToSysticks(int rpm, int angle);
float getCrankshaftRevolutionTime(int rpm);

typedef struct {
	float coolantTempMin;
	float coolantTempMax;
	float minTempPW;
	float maxTempPW;

	short int crankingRpm;
} CrankingMode;

#endif /* ENGINE_MATH_H_ */
