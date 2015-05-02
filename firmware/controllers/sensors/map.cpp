#include "main.h"
#include "engine_configuration.h"
#include "engine_math.h"
#include "adc_inputs.h"
#include "interpolation.h"
#include "error_handling.h"
#include "map.h"

#if EFI_ANALOG_SENSORS || defined(__DOXYGEN__)

EXTERN_ENGINE;

static FastInterpolation customMap;

/**
 * @brief	MAP value decoded for a 1.83 Honda sensor
 * -6.64kPa at zero volts
 * 182.78kPa at 5 volts
 *
 * about 3 volts at 100kPa
 *
 * @returns kPa value
 */
static FastInterpolation denso183(0, -6.64, 5, 182.78);

/**
 * MAP sensor output voltage of 3.0v = a gauge reading of 0 in. Hg
 * MAP sensor output voltage of 0.5v = a gauge reading of 27 in. Hg
 */
static FastInterpolation honda3bar(0.5, 91.422, 3.0, 0);

static FastInterpolation subyDenso(0, 0, 5, 200);

static FastInterpolation mpx4250(0, 8, 5, 260);

static FastInterpolation dodgeNeon2003(0.5, 0, 4.5, 100);

/**
 * We hold a reference to current decoder to reduce code branching
 * to lookup decoder each time we need to decode
 */
static FastInterpolation *mapDecoder;

float decodePressure(float voltage, air_pressure_sensor_config_s * config) {
	switch (config->type) {
	case MT_CUSTOM:
		// todo: migrate to 'FastInterpolation customMap'
		return interpolate(0, config->valueAt0, 5, config->valueAt5, voltage);
	case MT_DENSO183:
		return denso183.getValue(voltage);
	case MT_MPX4250:
		return mpx4250.getValue(voltage);
	case MT_HONDA3BAR:
		return honda3bar.getValue(voltage);
	case MT_DODGE_NEON_2003:
		return dodgeNeon2003.getValue(voltage);
	case MT_SUBY_DENSO:
		return subyDenso.getValue(voltage);
	default:
		firmwareError("Unknown MAP type: %d", config->type);
		return NAN;
	}
}

/**
 * @brief	MAP value decoded according to current settings
 * @returns kPa value
 */
float getMapByVoltage(float voltage DECLARE_ENGINE_PARAMETER_S) {
	// todo: migrate to mapDecoder once parameter listeners are ready
	air_pressure_sensor_config_s * apConfig = &engineConfiguration->map.sensor;
	return decodePressure(voltage, apConfig);
}

/**
 * @return Manifold Absolute Pressure, in kPa
 */
float getRawMap(DECLARE_ENGINE_PARAMETER_F) {
	float voltage = getVoltageDivided("map", engineConfiguration->map.sensor.hwChannel);
	return getMapByVoltage(voltage PASS_ENGINE_PARAMETER);
}

float getBaroPressure(DECLARE_ENGINE_PARAMETER_F) {
	float voltage = getVoltageDivided("map", engineConfiguration->baroSensor.hwChannel);
	return decodePressure(voltage, &engineConfiguration->baroSensor);
}

static FastInterpolation *getDecoder(air_pressure_sensor_type_e type) {
	switch (type) {
	case MT_CUSTOM:
		return &customMap;
	case MT_DENSO183:
		return &denso183;
	case MT_MPX4250:
		return &mpx4250;
	case MT_HONDA3BAR:
		return &honda3bar;
	case MT_DODGE_NEON_2003:
		return &dodgeNeon2003;
	case MT_SUBY_DENSO:
		return &subyDenso;
	default:
		firmwareError("Unknown MAP type: %d", type);
		return &customMap;
	}
}

static void applyConfiguration(DECLARE_ENGINE_PARAMETER_F) {
	air_pressure_sensor_config_s * apConfig = &engineConfiguration->map.sensor;
	customMap.init(0, apConfig->valueAt0, 5, apConfig->valueAt5);
	mapDecoder = getDecoder(engineConfiguration->map.sensor.type);
}

void initMapDecoder(DECLARE_ENGINE_PARAMETER_F) {
	applyConfiguration(PASS_ENGINE_PARAMETER_F);
	//engine->configurationListeners.registerCallback(applyConfiguration);
}

#else

void initMapDecoder(DECLARE_ENGINE_PARAMETER_F) {
}

#endif /* EFI_ANALOG_SENSORS */
