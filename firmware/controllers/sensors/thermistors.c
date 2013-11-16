/*
 * thermistors.c
 *
 *  Created on: Feb 17, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * http://en.wikipedia.org/wiki/Thermistor
 * http://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation
 */

#ifndef THERMISTORS_C_
#define THERMISTORS_C_

#include <math.h>
#include "main.h"
#include "thermistors.h"

/**
 * http://en.wikipedia.org/wiki/Voltage_divider
 */
myfloat getR1InVoltageDividor(myfloat Vout, myfloat Vin, myfloat r2) {
	return r2 * Vin / Vout - r2;
}

myfloat getR2InVoltageDividor(myfloat Vout, myfloat Vin, myfloat r1) {
	return r1 / (Vin / Vout - 1);
}

myfloat getVoutInVoltageDividor(myfloat Vin, myfloat r1, myfloat r2) {
	return r2 * Vin / (r1 + r2);
}

#define S_H_A (-0.0015925922146267837)
#define S_H_B (0.0008205491888240184)
#define S_H_C (-0.0000029438499727564513)

myfloat convertResistanceToKelvinTemperature(myfloat resistance) {
	if (resistance <= 0) {
		warning("Invalid resistance in convertResistanceToKelvinTemperature", resistance);
		return 0;
	}
	myfloat logR = log(resistance);
	return 1 / (S_H_A + S_H_B * logR + S_H_C * logR * logR * logR);
}

myfloat convertKelvinToC(myfloat tempK) {
	return tempK - KELV;
}

myfloat convertCelciustoKelvin(myfloat tempC) {
	return tempC + KELV;
}

myfloat convertCelciustoF(myfloat tempC) {
	return tempC * 9 / 5 + 32;
}

myfloat convertFtoCelcius(myfloat tempF) {
	return (tempF - 32) / 9 * 5;
}

myfloat convertKelvinToFahrenheit(myfloat kelvin) {
	myfloat tempC = convertKelvinToC(kelvin);
	return convertCelciustoF(tempC);
}

myfloat getKelvinTemperature(myfloat voltage, float hiR) {
	myfloat resistance = getR2InVoltageDividor(voltage, _5_VOLTS, hiR);
	myfloat kelvinTemperature = convertResistanceToKelvinTemperature(resistance);
	return kelvinTemperature;
}

myfloat getTemperatureC(myfloat voltage, float hiR) {
	myfloat kelvinTemperature = getKelvinTemperature(voltage, hiR);
	return convertKelvinToC(kelvinTemperature);
}

#endif /* THERMISTORS_C_ */
