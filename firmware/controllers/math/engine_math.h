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

/**
 * "For ALL 4 cycle (four-stroke) engines, no matter how many cylinders, the crankshaft
 * turns twice for every turn of the camshaft."
 *
 * Cam revolution time in milliseconds = 1000 / (RPM / 60 / 2) = 120000 / RPM
 * One stroke is 90 degrees = so, we divide revolution constant by four
 */

#define STROKE_TIME_CONSTANT (1000 * 60 * 2 / 4 * TICKS_IN_MS)

int convertAngleToSysticks(int rpm, int angle);

typedef struct {
	float coolantTempMin;
	float coolantTempMax;
	float minTempPW;
	float maxTempPW;

	short int crankingRpm;
} CrankingMode;

#endif /* ENGINE_MATH_H_ */
