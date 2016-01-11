/**
 * @author Andrey Belomutskiy, (c) 2012-2016
 */
#include "main.h"
#include "tps.h"
#include "engine_configuration.h"
#include "interpolation.h"
#include "adc_inputs.h"
#include "allsensors.h"

#if !EFI_PROD_CODE
	int mockTps;
#endif

	EXTERN_ENGINE;

/**
 * We are using one instance for read and another for modification, this is how we get lock-free thread-safety
 *
 */
static tps_roc_s states[2];

int tpsFastAdc = 0;

static volatile int tpsRocIndex = 0;

/**
 * this method is lock-free thread-safe if invoked only from one thread
 */
void saveTpsState(time_t now, float curValue) {
	int tpsNextIndex = (tpsRocIndex + 1) % 2;
	tps_roc_s *cur = &states[tpsRocIndex];
	tps_roc_s *next = &states[tpsNextIndex];

	next->prevTime = cur->curTime;
	next->prevValue = cur->curValue;
	next->curTime = now;
	next->curValue = curValue;

	int diffSysticks = overflowDiff(now, cur->curTime);
	float diffSeconds = diffSysticks * 1.0 / CH_FREQUENCY;
	next->rateOfChange = (curValue - cur->curValue) / diffSeconds;

	// here we update volatile index
	tpsRocIndex = tpsNextIndex;
}

/**
 * this read-only method is lock-free thread-safe
 */
float getTpsRateOfChange(void) {
	return states[tpsRocIndex].rateOfChange;
}

/*
 * Return current TPS position based on configured ADC levels, and adc
 *
 * */
percent_t getTpsValue(int adc DECLARE_ENGINE_PARAMETER_S) {
	if (engineConfiguration->tpsMin == engineConfiguration->tpsMax) {
		warning(OBD_PCM_Processor_Fault, "Invalid TPS configuration: same value %d", engineConfiguration->tpsMin);
		return NAN;
	}
	float result = interpolate(engineConfiguration->tpsMin, 0, engineConfiguration->tpsMax, 100, adc);
	// this would put the value into the 0-100 range
	return maxF(0, minF(100, result));
}

/*
 * Return voltage on TPS AND channel
 * */
float getTPSVoltage(DECLARE_ENGINE_PARAMETER_F) {
	return getVoltageDivided("tps", engineConfiguration->tpsAdcChannel);
}

/*
 * Return TPS ADC readings.
 * We need ADC value because TunerStudio has a nice TPS configuration wizard, and this wizard
 * wants a TPS value.
 */
int getTPS10bitAdc(DECLARE_ENGINE_PARAMETER_F) {
#if !EFI_PROD_CODE
	if (mockTps != MOCK_UNDEFINED)
		return mockTps;
#endif
	if(engineConfiguration->tpsAdcChannel==EFI_ADC_NONE)
		return -1;
#if EFI_PROD_CODE
	return tpsFastAdc / 4;
#else
	return 0;
#endif /* EFI_PROD_CODE */
}

/**
 * @brief Position on physical primary TPS
 */
static float getPrimatyRawTPS(DECLARE_ENGINE_PARAMETER_F) {
	float tpsValue = getTpsValue(getTPS10bitAdc(PASS_ENGINE_PARAMETER_F) PASS_ENGINE_PARAMETER);
	return tpsValue;
}

#define NO_TPS_MAGIC_VALUE 66.611

bool hasPedalPositionSensor(DECLARE_ENGINE_PARAMETER_F) {
	return engineConfiguration->pedalPositionChannel != EFI_ADC_NONE;
}

percent_t getPedalPosition(DECLARE_ENGINE_PARAMETER_F) {
	float voltage = getVoltageDivided("pPS", engineConfiguration->pedalPositionChannel);
	float result = interpolate(engineConfiguration->pedalPositionMin, 0, engineConfiguration->pedalPositionMax, 100, voltage);

	// this would put the value into the 0-100 range
	return maxF(0, minF(100, result));
}

percent_t getTPS(DECLARE_ENGINE_PARAMETER_F) {
	if (!engineConfiguration->hasTpsSensor)
		return NO_TPS_MAGIC_VALUE;
	// todo: if (config->isDualTps)
	// todo: blah blah
	// todo: if two TPS do not match - show OBD code via malfunction_central.c

	return getPrimatyRawTPS(PASS_ENGINE_PARAMETER_F);
}

int convertVoltageTo10bitADC(float voltage) {
	// divided by 2 because of voltage divider, then converted into 10bit ADC value (TunerStudio format)
	return (int) (voltage / 2 * 1024 / 3.3);
}
