/**
 * @file thermistors.h
 *
 * @date Feb 17, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef THERMISTORS_H_
#define THERMISTORS_H_

#include "main.h"

#define _5_VOLTS 5.0
#define KELV 273.15

/**
 * @brief thermistor curve parameters
 */
typedef struct {
	float temp_1;
	float temp_2;
	float temp_3;
	float resistance_1;
	float resistance_2;
	float resistance_3;

	float bias_resistor;

	float s_h_a;
	float s_h_b;
	float s_h_c;
} ThermistorConf;

typedef struct {
	ThermistorConf *config;
	int channel;
} Thermistor;

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

myfloat getKelvinTemperature(myfloat voltage, ThermistorConf *thermistor);
myfloat getTemperatureC(Thermistor *thermistor);
myfloat getCoolantTemperature(void);
myfloat getIntakeAirTemperature(void);

void setThermistorConfiguration(ThermistorConf * tc, float temp1, float r1, float temp2, float r2, float temp3,
		float r3);
void prepareThermistorCurve(ThermistorConf * config);
void initThermistors(void);

#endif /* THERMISTORS_H_ */
