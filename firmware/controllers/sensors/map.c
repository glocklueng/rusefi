#include "main.h"
#include "boards.h"
#include "engine_configuration.h"
#include "engine_math.h"
#include "adc_inputs.h"
#include "interpolation.h"
#include "error_handling.h"
#include "map.h"

extern engine_configuration_s * engineConfiguration;

/**
 * @brief	MAP value decoded for a 1.83 Honda sensor
 * -6.64kPa at zero volts
 * 182.78kPa at 5 volts
 *
 * @returns kPa value
 */
float getMAPValueHonda_Denso183(float voltage) {
	return interpolate(0, -6.64, 5, 182.78, voltage);
}

float getMAPValueMPX_4250(float voltage) {
	return interpolate(0, 8, 5, 260, voltage);
}

float decodePressure(float voltage, air_pressure_sensor_config_s * config) {
	switch (config->mapType) {
	case MT_CUSTOM:
		return interpolate(0, config->Min, 5, config->Max, voltage);
	case MT_DENSO183:
		return getMAPValueHonda_Denso183(voltage);
	case MT_MPX4250:
		return getMAPValueMPX_4250(voltage);
	default:
		firmwareError("Unknown MAP type: %d", config->mapType);
		return NAN;
	}
}

/**
 * @brief	MAP value decoded according to current settings
 * @returns kPa value
 */
float getMapByVoltage(float voltage) {
	air_pressure_sensor_config_s * config = &engineConfiguration->map.sensor;
	return decodePressure(voltage, config);
}

float getRawMap(void) {
	float voltage = getVoltageDivided(engineConfiguration->map.sensor.hwChannel);
	return getMapByVoltage(voltage);
}

float getBaroPressure(void) {
	float voltage = getVoltageDivided(engineConfiguration->baroSensor.hwChannel);
	return decodePressure(voltage, &engineConfiguration->baroSensor);
}
