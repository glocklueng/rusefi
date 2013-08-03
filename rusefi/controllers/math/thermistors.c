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
#include "thermistors.h"
#include "adc_inputs.h"
#include "rficonsole.h"
#include "engine_math.h"


	//	myfloat tempC = 30;
	//	myfloat tempK = tempCtoK(tempC);
	//	print("k=%d\r\n", (int) (tempK * 1000));
	//	print("k=%d\r\n", (int) (tempK * 1000.0));
	//	myfloat r = getResistance(tempK);
	//	myfloat tt = getTempK(r);
	//	myfloat tc = tempKtoC(tt);
	//
	//	print("r=%d, t=%d\r\n", (int) (r * 1000), (int) (1000 * tc));


	//	myfloat r1 = getR1InVoltageDividor3(2, _5_VOLTS, 1000);
//	print("r1=%f\r\n", r1);
//	print("r2=%f\r\n", getR2InVoltageDividor3(2, _5_VOLTS, 1000));
//	print("pot %d\r\n", getPotStep(r1));

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
	myfloat logR = log(resistance);
	return 1 / (S_H_A + S_H_B * logR + S_H_C * logR * logR * logR);
}


// I am not sure this method works, wonder where the bug is
//myfloat getResistance(myfloat tempK) {
//	myfloat y = (S_H_A - 1 / tempK) / 2 / S_H_C;
//	print("y=%d\r\n", (int) (y * 1000));
//	myfloat xx = pow(S_H_B / 3 / S_H_C, 3) + y * y;
//	print("xx=%d\r\n", (int) (xx * 1000));
//	myfloat x = sqrt(xx);
//	print("x=%d\r\n", (int) (x * 1000));
//
//	return exp(pow(x - y, 1.0 / 3) - pow(x + y, 1.0 / 3));
//}

myfloat tempKtoC(myfloat tempK) {
	return tempK - KELV;
}

myfloat tempCtoK(myfloat tempC) {
	return tempC + KELV;
}

myfloat tempCtoF(myfloat tempC) {
	return tempC * 9 / 5 + 32;
}

myfloat tempFtoC(myfloat tempF) {
	return (tempF - 32) / 9 * 5;
}

myfloat convertKelvinToFahrenheit(myfloat tempK) {
	myfloat tempC = tempKtoC(tempK);
	return tempCtoF(tempC);
}

myfloat getFahrenheittemp(int adcValue) {
	myfloat voltage = adcToVolts2(adcValue);
	myfloat resistance = getR2InVoltageDividor(voltage, _5_VOLTS, THERMISTOR_BIAS_RESISTOR);
	myfloat kelvinTemperature = convertResistanceToKelvinTemperature(resistance);
	return convertKelvinToFahrenheit(kelvinTemperature);
}

#define TPS_IDLE 0.60
#define TPS_WOT 4.23

// not a thermistor, but I am too lazy to create a new file
int getTpsValue(myfloat volts) {
	if (volts <= TPS_IDLE)
		return 0;
	if (volts >= TPS_WOT)
		return 100;
	return (int) (100 * (volts - TPS_IDLE) / (TPS_WOT - TPS_IDLE));
}

#endif /* THERMISTORS_C_ */
