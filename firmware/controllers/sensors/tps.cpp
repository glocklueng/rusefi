#include "main.h"
#include "boards.h"
#include "tps.h"
#include "engine_configuration.h"
#include "interpolation.h"
#include "adc_inputs.h"

extern engine_configuration_s *engineConfiguration;

/**
 * We are using one instance for read and another for modification, this is how we get lock-free thread-safety
 *
 */
static tps_roc_s states[2];

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
float getTpsValue(int adc) {
	if (adc < engineConfiguration->tpsMin)
		return 0;
	if (adc > engineConfiguration->tpsMax)
		return 100;
	// todo: double comparison using EPS
	if (engineConfiguration->tpsMin == engineConfiguration->tpsMax) {
		firmwareError("Invalid TPS configuration: same value");
		return 0;
	}
	return interpolate(engineConfiguration->tpsMin, 0, engineConfiguration->tpsMax, 100, adc);
}

/*
 * Return voltage on TPS AND channel
 * */
float getTPSVoltage(void) {
	return getVoltageDivided(engineConfiguration->tpsAdcChannel);
}

/*
 * Return TPS ADC readings.
 * We need ADC value because TunerStudio has a nice TPS configuration wizard, and this wizard
 * wants a TPS value.
 */
int getTPS10bitAdc(void) {
	int adc = getAdcValue(engineConfiguration->tpsAdcChannel);
	return (int) adc / 4; // Only for TunerStudio compatibility. Max TS adc value in 1023
}

/**
 * @brief Position on physical primary TPS
 */
static float getPrimatyRawTPS(void) {
	// blue, 1st board
	/* PA7 - blue TP */
	float tpsValue = getTpsValue(getTPS10bitAdc());
	return tpsValue;
}

// todo: static float getSecondaryRawTPS

/*
 * In case of dual TPS this function would return logical TPS position
 *
 * @return Current TPS position, percent of WOT. 0 means idle and 100 means Wide Open Throttle
 */
float getTPS(void) {
	// todo: if (config->isDualTps)
	// todo: blah blah
	// todo: if two TPS do not match - show OBD code via malfunction_central.c

	return getPrimatyRawTPS();
}

int convertVoltageTo10bitADC(float voltage) {
	// divided by 2 because of voltage divider, then converted into 10bit ADC value (TunerStudio format)
	return (int)(voltage / 2 * 1024 / 3.3);
}
