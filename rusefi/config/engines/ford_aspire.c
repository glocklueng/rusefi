/*
 *  Created on: Sep 9, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    ford_aspire.c
 */

#include "main.h"

#if EFI_ENGINE_FORD_ASPIRE

#include "engine.h"
#include "engine_math.h"
#include "settings.h"
#include "rpm_reporter.h"
#include "fuel_map.h"
#include "engine_controller.h"

#define TPS_IDLE 0.60
#define TPS_WOT 4.23

// not a thermistor, but I am too lazy to create a new file
int getTpsValue(myfloat volts) {
	if (volts <= TPS_IDLE)
		return 0;
	if (volts >= TPS_WOT)
		return 100;
	return (int) (100 * (volts - TPS_IDLE) / (TPS_WOT - TPS_IDLE));
}

myfloat getTPS(void) {
	// blue, 1st board
	/* PA7 - blue TP */
	int tpsValue = getTpsValue(getVoltage(ADC_LOGIC_TPS));
	return tpsValue;
}

myfloat getMaf() {
	return getVoltage(ADC_LOGIC_MAF);
}

myfloat getAfr() {
	myfloat volts = getVoltage(ADC_LOGIC_AFR);

	return interpolate(0, 9, 5, 19, volts);
}

myfloat getVRef() {
//	return getAdcValue(ADC_CHANNEL_VREF);
	return getVoltage(ADC_CHANNEL_VREF);
}

myfloat getMap(void) {
	int adc0 = getAdcValue(ADC_LOGIC_MAP);
	float volts = adcToVolts(adc0);

	return getMAPValueHonda_Denso183(volts);
}

static float getCrankingFuel() {
	const int fuelOverride = getCrankingInjectionPeriod();
	if (fuelOverride != 0) {
		return fuelOverride / 10.0;
	} else {
		return getStartingFuel(getCoolantTemperature());
	}
}

/**
 * @brief	Amount of fuel we should inject
 */
float getFuelMs() {
	if (isCranking()) {
		return getCrankingFuel();
	} else {
		int rpm = getCurrentRpm();
		myfloat fuel;
		if (MAF_MODE)
			fuel = getFuel(rpm, getMaf());
		else
			fuel = getDefaultFuel(rpm, getMap());
	}
}

#endif
