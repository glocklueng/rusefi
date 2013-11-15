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
myfloat convertKelvinToCelcius(myfloat tempK);
myfloat convertCelciustoKelvin(myfloat tempC);

myfloat convertCelciustoF(myfloat tempC);
myfloat convertFtoCelcius(myfloat tempF);

int getTpsValue(myfloat volts);
myfloat getKelvinTemperature(myfloat voltage, float hiR);
myfloat getTemperatureC(myfloat voltage, float hiR);

#endif /* THERMISTORS_H_ */
