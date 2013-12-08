#include "main.h"
#include "boards.h"
#include "engine_configuration.h"
#include "interpolation.h"
#include "adc_inputs.h"

extern EngineConfiguration *engineConfiguration;

/*
 * Return current TPS position based on configured ADC levels, and adc
 *
 * */
myfloat getTpsValue(int adc) {
	return interpolate(engineConfiguration->tpsMin, 0, engineConfiguration->tpsMax, 100, adc);
}

/*
 * Return voltage on TPS AND channel
 * */
myfloat getTPSVoltage(void) {
	return getVoltage(ADC_LOGIC_TPS);
}

/*
 * Return TPS ADC readings
 */
int getTPSAdc(void) {
	int adc = getAdcValue(ADC_LOGIC_TPS);
	return (int) adc / 4; // Only for TunerStudio compatibility. Max TS adc value in 1023
}

/*
 * @return Current TPS position. 0 means idle and 100 means Wide Open Throttle
 * */
myfloat getTPS(void) {
	// blue, 1st board
	/* PA7 - blue TP */
	myfloat tpsValue = getTpsValue(getTPSAdc());
	return tpsValue;
}
