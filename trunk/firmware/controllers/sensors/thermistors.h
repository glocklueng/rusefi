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

#include "sensor_types.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
/**
 * Vout=r2/(r1+r2)*Vin
 */
float getR1InVoltageDividor(float Vout, float Vin, float r2);
float getR2InVoltageDividor(float Vout, float Vin, float r1);
float getTempK(float resistance);
/**
 * converts Kelvin temperature into Celcius temperature
 */
float convertKelvinToCelcius(float tempK);
float convertCelciustoKelvin(float tempC);

float convertCelciustoF(float tempC);
float convertFtoCelcius(float tempF);

float getKelvinTemperature(float resistance, ThermistorConf *thermistor);
float getResistance(Thermistor *thermistor);
float getTemperatureC(Thermistor *thermistor);
float getCoolantTemperature(void);
int isValidCoolantTemperature(float temperature);
float getIntakeAirTemperature(void);
int isValidIntakeAirTemperature(float temperature);

float convertResistanceToKelvinTemperature(float resistance,
		ThermistorConf *thermistor);
void setThermistorConfiguration(ThermistorConf * tc, float temp1, float r1, float temp2, float r2, float temp3,
		float r3);
void prepareThermistorCurve(ThermistorConf * config);
void initThermistors(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* THERMISTORS_H_ */
