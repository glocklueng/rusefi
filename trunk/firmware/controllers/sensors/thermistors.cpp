/**
 * @file thermistors.cpp
 *
 * @date Feb 17, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

/**
 * http://en.wikipedia.org/wiki/Thermistor
 * http://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation
 */

#include "main.h"
#include "thermistors.h"
#include "adc_inputs.h"
#include "engine_configuration.h"
#include "engine_math.h"

// Celsius
#define LIMPING_MODE_IAT_TEMPERATURE 30.0f
#define LIMPING_MODE_CLT_TEMPERATURE 70.0f

EXTERN_ENGINE
;

static Logging *logger;

static bool initialized = false;

/**
 * http://en.wikipedia.org/wiki/Voltage_divider
 */
float getR1InVoltageDividor(float Vout, float Vin, float r2) {
	return r2 * Vin / Vout - r2;
}

float getR2InVoltageDividor(float Vout, float Vin, float r1) {
	if (Vout == 0) {
		return NAN;
	}
	return r1 / (Vin / Vout - 1);
}

float getVoutInVoltageDividor(float Vin, float r1, float r2) {
	return r2 * Vin / (r1 + r2);
}

float getKelvinTemperature(float resistance, thermistor_curve_s * curve) {
	efiAssert(curve != NULL, "thermistor pointer is NULL", NAN);

	if (resistance <= 0) {
		//warning("Invalid resistance in getKelvinTemperature=", resistance);
		return 0.0f;
	}
	float logR = logf(resistance);
	return 1 / (curve->s_h_a + curve->s_h_b * logR + curve->s_h_c * logR * logR * logR);
}

float convertCelsiustoF(float tempC) {
	return tempC * 9 / 5 + 32;
}

float convertFtoCelsius(float tempF) {
	return (tempF - 32) / 9 * 5;
}

float convertKelvinToFahrenheit(float kelvin) {
	float tempC = convertKelvinToCelcius(kelvin);
	return convertCelsiustoF(tempC);
}

float getResistance(Thermistor *thermistor) {
	float voltage = getVoltageDivided("term", thermistor->channel);
	efiAssert(thermistor->config != NULL, "thermistor config is null", NAN);
	thermistor_conf_s *tc = &thermistor->config->config;

	float resistance = getR2InVoltageDividor(voltage, _5_VOLTS, tc->bias_resistor);
	return resistance;
}

float getTemperatureC(Thermistor *thermistor, thermistor_curve_s * curve) {
	if (!initialized) {
		firmwareError("thermstr not initialized");
		return NAN;
	}
	float resistance = getResistance(thermistor);

	float kelvinTemperature = getKelvinTemperature(resistance, curve);
	return convertKelvinToCelcius(kelvinTemperature);
}

bool isValidCoolantTemperature(float temperature) {
	// I hope magic constants are appropriate here
	return !cisnan(temperature) && temperature > -50 && temperature < 250;
}

bool isValidIntakeAirTemperature(float temperature) {
	// I hope magic constants are appropriate here
	return !cisnan(temperature) && temperature > -50 && temperature < 100;
}

/**
 * @return coolant temperature, in Celsius
 */
float getCoolantTemperature(DECLARE_ENGINE_PARAMETER_F) {
	float temperature = getTemperatureC(&engine->clt, &engine->engineState.cltCurve.curve);
	if (!isValidCoolantTemperature(temperature)) {
		efiAssert(engineConfiguration!=NULL, "NULL engineConfiguration", NAN);
		if (engineConfiguration->hasCltSensor) {
			warning(OBD_PCM_Processor_Fault, "unrealistic CLT %f", temperature);
		}
		return LIMPING_MODE_CLT_TEMPERATURE;
	}
	return temperature;
}

void setThermistorConfiguration(ThermistorConf * thermistor, float tempC1, float r1, float tempC2, float r2, float tempC3,
		float r3) {
	thermistor_conf_s *tc = &thermistor->config;
	tc->tempC_1 = tempC1;
	tc->resistance_1 = r1;

	tc->tempC_2 = tempC2;
	tc->resistance_2 = r2;

	tc->tempC_3 = tempC3;
	tc->resistance_3 = r3;
}

void prepareThermistorCurve(ThermistorConf * config, thermistor_curve_s * curve) {
	efiAssertVoid(config!=NULL, "therm config");
	thermistor_conf_s *tc = &config->config;
	float T1 = tc->tempC_1 + KELV;
	float T2 = tc->tempC_2 + KELV;
	float T3 = tc->tempC_3 + KELV;
	scheduleMsg(logger, "T1=%..100000f/T2=%..100000f/T3=%..100000f", T1, T2, T3);

	float L1 = logf(tc->resistance_1);
	if (L1 == tc->resistance_1) {
		firmwareError("log is broken?");
	}
	float L2 = logf(tc->resistance_2);
	float L3 = logf(tc->resistance_3);
	scheduleMsg(logger, "R1=%..100000f/R2=%..100000f/R3=%..100000f", tc->resistance_1, tc->resistance_2,
			tc->resistance_3);
	scheduleMsg(logger, "L1=%..100000f/L2=%..100000f/L3=%..100000f", L1, L2, L3);

	float Y1 = 1 / T1;
	float Y2 = 1 / T2;
	float Y3 = 1 / T3;

	scheduleMsg(logger, "Y1=%..100000f/Y2=%..100000f/Y3=%..100000f", Y1, Y2, Y3);

	float U2 = (Y2 - Y1) / (L2 - L1);
	float U3 = (Y3 - Y1) / (L3 - L1);

	scheduleMsg(logger, "U2=%..100000f/U3=%..100000f", U2, U3);

	curve->s_h_c = (U3 - U2) / (L3 - L2) * pow(L1 + L2 + L3, -1);
	curve->s_h_b = U2 - curve->s_h_c * (L1 * L1 + L1 * L2 + L2 * L2);
	curve->s_h_a = Y1 - (curve->s_h_b + L1 * L1 * curve->s_h_c) * L1;

	scheduleMsg(logger, "s_h_c=%..100000f/s_h_b=%..100000f/s_h_a=%..100000f", curve->s_h_c, curve->s_h_b,
			curve->s_h_a);
}

/**
 * @return Celsius value
 */
float getIntakeAirTemperature(DECLARE_ENGINE_PARAMETER_F) {
	float temperature = getTemperatureC(&engine->iat, &engine->engineState.iatCurve.curve);
	if (!isValidIntakeAirTemperature(temperature)) {
		efiAssert(engineConfiguration!=NULL, "NULL engineConfiguration", NAN);
		if (engineConfiguration->hasIatSensor) {
			warning(OBD_PCM_Processor_Fault, "unrealistic IAT %f", temperature);
		}
		return LIMPING_MODE_IAT_TEMPERATURE;
	}
	return temperature;
}

static void initThermistorCurve(Thermistor * t, ThermistorConf *config, adc_channel_e channel,
		thermistor_curve_s * curve) {
	prepareThermistorCurve(config, curve);
	t->config = config;
	t->channel = channel;
}

void setDodgeSensor(ThermistorConf *thermistorConf) {
	setThermistorConfiguration(thermistorConf, -40, 336660, 30, 7550, 120, 390);
}

// todo: better method name?
void setCommonNTCSensor(ThermistorConf *thermistorConf) {
	/**
	 * 18K Ohm @ -20C
	 * 2.1K Ohm @ 24C
	 * 294 Ohm @ 80C
	 * http://www.rexbo.eu/hella/coolant-temperature-sensor-6pt009107121?c=100334&at=3130
	 */
	setThermistorConfiguration(thermistorConf, -20, 18000, 23.8889, 2100, 120.0, 100.0);
}

#if EFI_PROD_CODE
static void testCltByR(float resistance) {
	Thermistor *thermistor = &engine->clt;
	float kTemp = getKelvinTemperature(resistance, &engine->engineState.cltCurve.curve);
	scheduleMsg(logger, "for R=%f we have %f", resistance, (kTemp - KELV));

	initThermistorCurve(&engine->clt, &engineConfiguration->clt, engineConfiguration->clt.adcChannel,
			&engine->engineState.cltCurve.curve);

}
#endif

void initThermistors(Logging *sharedLogger DECLARE_ENGINE_PARAMETER_S) {
	logger = sharedLogger;
	efiAssertVoid(engine!=NULL, "e NULL initThermistors");
	efiAssertVoid(engine->engineConfiguration2!=NULL, "e2 NULL initThermistors");
	initThermistorCurve(&engine->clt, &engineConfiguration->clt, engineConfiguration->clt.adcChannel,
			&engine->engineState.cltCurve.curve);
	initThermistorCurve(&engine->iat, &engineConfiguration->iat, engineConfiguration->iat.adcChannel,
			&engine->engineState.iatCurve.curve);

#if EFI_PROD_CODE
	addConsoleActionF("test_clt_by_r", testCltByR);
#endif

	initialized = true;
}

ThermistorMath::ThermistorMath() {

}

void ThermistorMath::init(thermistor_conf_s currentConfig) {

}
