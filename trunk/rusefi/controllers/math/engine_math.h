/*
 * engine_math.h
 *
 *  Created on: Jul 13, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_MATH_H_
#define ENGINE_MATH_H_

float interpolate(float x1, float y1, float x2, float y2, float x);

float getMAPValue(int adcValue);

float getDefaultVE(int rpm);

float getDefaultFuel(int rpm, float map);
float getTCharge(int rpm, int tps, float coolantTemp, float airTemp);

float adcToVolts(int adc);
// this method should be used to display real voltage if we have divided it by two to fit it under +3v
float adcToVolts2(int adc);
int findIndex(float array[], int size, float value);
float getStartingFuel(int coolantTemperature);

#endif /* ENGINE_MATH_H_ */
