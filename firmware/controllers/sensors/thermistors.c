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
	myfloat kelvinTemperature = getKelvinTemperature(voltage, thermistor->config);
	return convertKelvinToC(kelvinTemperature);
}

myfloat getCoolantTemperature(void) {
	return getTemperatureC(&engineConfiguration2.clt);
}

static void prepareThermistorCurve(ThermistorConf * config) {
	float T1 = config->temp_1 + 273.15;
	float T2 = config->temp_2 + 273.15;
	float T3 = config->temp_3 + 273.15;

	float L1 = log(config->resistance_1);
	float L2 = log(config->resistance_2);
	float L3 = log(config->resistance_3);

	float Y1 = 1 / T1;
	float Y2 = 1 / T2;
	float Y3 = 1 / T3;

	float U2 = (Y2 - Y1) / (L2 - L1);
	float U3 = (Y3 - Y1) / (L3 - L1);

	config->s_h_c = (U3 - U2) / (L3 - L2) * pow(L1 + L2 + L3, -1);
	config->s_h_b = U2 - config->s_h_c * (L1 * L1 + L1 * L2 + L2 * L2);
	config->s_h_a = Y1 - (config->s_h_b + L1 * L1 * config->s_h_c) * L1;
}

myfloat getIntakeAirTemperature(void) {
	return getTemperatureC(&engineConfiguration2.iat);
}

static void initThermistorCurve(Thermistor * t, ThermistorConf *config, int pin) {
	prepareThermistorCurve(config);
	t->config = config;
	t->channel = pin;
}

void initThermistors(void) {

}
#endif /* THERMISTORS_C_ */
