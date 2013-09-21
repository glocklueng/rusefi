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
#define KELV 273.15

/**
 * Vout=r2/(r1+r2)*Vin
 */
myfloat getR1InVoltageDividor(myfloat Vout, myfloat Vin, myfloat r2);
myfloat getR2InVoltageDividor(myfloat Vout, myfloat Vin, myfloat r1);
myfloat getTempK(myfloat resistance);
/**
 * converts Kelvin temperature into Celcius temperature
 */
myfloat convertKelvinToC(myfloat tempK);
myfloat tempCtoKelvin(myfloat tempC);

myfloat tempCtoF(myfloat tempC);
myfloat tempFtoC(myfloat tempF);

myfloat tempKtoF(myfloat tempK);
int getTpsValue(myfloat volts);
myfloat getKelvinTemperature(int adcValue, float hiR);
myfloat getTemperatureC(int adcValue, float hiR);
myfloat getResistance(myfloat tempK);


#endif /* THERMISTORS_H_ */
