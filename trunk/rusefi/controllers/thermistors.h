/*
 * thermistors.h
 *
 *  Created on: Feb 17, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef THERMISTORS_H_
#define THERMISTORS_H_

#include "main.h"

#define _5_VOLTS 5.0
#define BIAS_RESISTOR 2700
#define KELV 273.15

myfloat getR1InVoltageDividor3(myfloat Vout, myfloat Vin, myfloat r2);
myfloat getR2InVoltageDividor3(myfloat Vout, myfloat Vin, myfloat r1);
/**
 * Vout=r2/(r1+r2)*Vin
 */
myfloat getR2InVoltageDividor(myfloat vin);
myfloat getTempK(myfloat resistance);
/**
 * converts Kelvin temperature into Celcius temperature
 */
myfloat tempKtoC(myfloat tempK);
myfloat tempCtoK(myfloat tempC);

myfloat tempCtoF(myfloat tempC);
myfloat tempFtoC(myfloat tempF);

myfloat tempKtoF(myfloat tempK);
int getTpsValue(myfloat volts);
myfloat getFtemp(int adcValue);
myfloat getResistance(myfloat tempK);

myfloat getHondaMAPValue(int adcValue);

#endif /* THERMISTORS_H_ */
