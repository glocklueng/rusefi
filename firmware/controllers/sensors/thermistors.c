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

extern EngineConfiguration *engineConfiguration;
extern EngineConfiguration2 *engineConfiguration2;

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
	chDbgCheck(thermistor!=NULL, "thermistor pointer is NULL");

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
	return getTemperatureC(&engineConfiguration2->clt);
}

void setThermistorConfiguration(ThermistorConf * tc, float temp1, float r1, float temp2, float r2, float temp3,
		float r3) {
	tc->temp_1 = temp1;
	tc->resistance_1 = r1;

	tc->temp_2 = temp2;
	tc->resistance_2 = r2;

	tc->temp_3 = temp3;
	tc->resistance_3 = r3;
}

void prepareThermistorCurve(ThermistorConf * config) {
	float T1 = config->temp_1 + KELV;
	float T2 = config->temp_2 + KELV;
	float T3 = config->temp_3 + KELV;

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
	return getTemperatureC(&engineConfiguration2->iat);
}

static void initThermistorCurve(Thermistor * t, ThermistorConf *config, int channel) {
	prepareThermistorCurve(config);
	t->config = config;
	t->channel = channel;
}

void initThermistors(void) {
	initThermistorCurve(&engineConfiguration2->clt, &engineConfiguration->cltThermistorConf,
			ADC_LOGIC_COOLANT);
	initThermistorCurve(&engineConfiguration2->iat, &engineConfiguration->iatThermistorConf,
			ADC_LOGIC_AIR);
}
#endif /* THERMISTORS_C_ */
