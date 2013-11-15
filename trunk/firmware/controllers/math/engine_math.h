/*
 * @file	engine_math.h
 *
 *  Created on: Jul 13, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_MATH_H_
#define ENGINE_MATH_H_

float interpolate(float x1, float y1, float x2, float y2, float x);

float getMAPValueHonda_Denso183(float volts);

float getDefaultVE(int rpm);

float getDefaultFuel(int rpm, float map);
float getTCharge(int rpm, int tps, float coolantTemp, float airTemp);

int findIndex(float array[], int size, float value);
float getStartingFuel(int coolantTemperature);

/**
 * "For ALL 4 cycle (four-stroke) engines, no matter how many cylinders, the crankshaft
 * turns twice for every turn of the camshaft."
 *
 * Cam revolution time in milliseconds = 1000 / (RPM / 60 / 2) = 120000 / RPM
 * One stroke is 90 degrees = so, we divide revolution constant by four
 */

#define STROKE_TIME_CONSTANT (1000 * 60 * 2 / 4 * TICKS_IN_MS)

int getFullWaveLengthByRpm(int rpm);
int convertAngleToSysticks(int rpm, int angle);

#endif /* ENGINE_MATH_H_ */
