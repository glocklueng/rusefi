/*
 * thermistors.c
 *
 * @date Feb 17, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * http://en.wikipedia.org/wiki/Thermistor
 * http://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation
 */

#ifndef THERMISTORS_C_
#define THERMISTORS_C_

#include "main.h"
#include "thermistors.h"
#include "adc_inputs.h"
#include "engine_configuration.h"

extern EngineConfiguration2 engineConfiguration2;

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


myfloat convertResistanceToKelvinTemperature(myfloat resistance,
		ThermistorConf *thermistor) {
	if (resistance <= 0) {
		//warning("Invalid resistance in convertResistanceToKelvinTemperature=", resistance);
		return 0;
	}
	myfloat logR = log(resistance);
	return 1
			/ (thermistor->s_h_a + thermistor->s_h_b * logR
					+ thermistor->s_h_c * logR * logR * logR);
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

myfloat getKelvinTemperature(myfloat voltage, ThermistorConf *thermistor) {
	myfloat resistance = getR2InVoltageDividor(voltage, _5_VOLTS,
			thermistor->bias_resistor);
	myfloat kelvinTemperature = convertResistanceToKelvinTemperature(resistance,
			thermistor);
	return kelvinTemperature;
}

myfloat getTemperatureC(Thermistor *thermistor) {

	myfloat voltage = getVoltage(thermistor->channel);
	myfloat kelvinTemperature = getKelvinTemperature(voltage, &thermistor->config);
	return convertKelvinToC(kelvinTemperature);
}

myfloat getCoolantTemperature(void) {
	return getTemperatureC(&engineConfiguration2.clt);
}

myfloat getIntakeAirTemperature(void) {
	return getTemperatureC(&engineConfiguration2.iat);
}

#endif /* THERMISTORS_C_ */
