/*
 * engine_math.h
 *
 *  Created on: Jul 13, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_MATH_H_
#define ENGINE_MATH_H_

float interpolate(float x1, float y1, float x2, float y2, float x);

float getMAPValue(float volts);

float getDefaultVE(int rpm);

float getDefaultFuel(int rpm, float map);
float getTCharge(int rpm, int tps, float coolantTemp, float airTemp);

int findIndex(float array[], int size, float value);
float getStartingFuel(int coolantTemperature);

#endif /* ENGINE_MATH_H_ */
