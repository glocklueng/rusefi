#include "main.h"
#include "boards.h"
#include "engine_configuration.h"
#include "engine_math.h"
#include "adc_inputs.h"

#define Honda_Denso183_Min -6.64
#define Honda_Denso183_Max 182.78
#define Honda_Denso183_Range (Honda_Denso183_Max - Honda_Denso183_Min)

extern EngineConfiguration * engineConfiguration;

/**
 * @brief	MAP value decoded for a 1.83 Honda sensor
 * @returns kPa value
 */
static float getMAPValueHonda_Denso183(float volts) {
	return Honda_Denso183_Range / 5 * volts + Honda_Denso183_Min;
}

/**
 * @brief	MAP value decoded according to current settings
 * @returns kPa value
 */
float getMapByVoltage(float voltage) {
	// todo: here is the place where we should read the settings and decide
	// todo: how to translate voltage into pressure
	return getMAPValueHonda_Denso183(voltage);
}

myfloat getRawMap(void) {
	float voltage = getVoltage(engineConfiguration->map.channel);
	return getMapByVoltage(voltage);
}
