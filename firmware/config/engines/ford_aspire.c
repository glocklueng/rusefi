/*
 *  Created on: Sep 9, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    ford_aspire.c
 */

#include "main.h"

#if EFI_ENGINE_FORD_ASPIRE

#include "ford_aspire.h"

#include "engine.h"
#include "engine_math.h"
#include "settings.h"
#include "rpm_reporter.h"
#include "fuel_map.h"
#include "engine_controller.h"

#define TPS_IDLE 0.60
#define TPS_WOT 4.23

int getTpsValue(myfloat volts) {
	if (volts <= TPS_IDLE)
		return 0;
	if (volts >= TPS_WOT)
		return 100;
	// todo: replace with 'interpolate' function invocation
	return (int) (100 * (volts - TPS_IDLE) / (TPS_WOT - TPS_IDLE));
}

myfloat getTPS(void) {
	// blue, 1st board
	/* PA7 - blue TP */
	int tpsValue = getTpsValue(getVoltage(ADC_LOGIC_TPS));
	return tpsValue;
}

myfloat getMaf(void) {
	return getVoltage(ADC_LOGIC_MAF);
}

myfloat getAfr(void) {
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

static float getCrankingFuel(void) {
	const int fuelOverride = getCrankingInjectionPeriod();
	if (fuelOverride != 0) {
		return fuelOverride / 10.0;
	} else {
		return getStartingFuel(getCoolantTemperature());
	}
}

/**
 * @brief	Length of fuel injection, in milliseconds
 */
float getFuelMs(int rpm) {
	if (isCranking()) {
		return getCrankingFuel();
	} else {
		myfloat fuel = getFuel(rpm, getMaf());
		return fuel;
	}
}

void confgiureShaftPositionEmulatorShape(PwmConfig *state) {
	myfloat x = ASPIRE_MAGIC_DUTY_CYCLE / 4;

	/**
	 * 1993 Ford Aspire has two hall sensors for CKP sensor
	 *
	 * X__X__X__X__  38% duty cycle
	 * __XXXXXX____  50% duty cycle
	 */

	myfloat secondStart = 0.17; //x + (0.25 - x) / 2;

	myfloat switchTimes[] = { x, secondStart, 0.25, 0.25 + x, 0.5, 0.5 + x,
			secondStart + 0.5,
			0.75, 0.75 + x, 1 };

	/**
	 * One signal per cam shaft revolution
	 */
	int pinStates0[] = { 1, 0, 0, 0, 0,
			             0, 1, 1, 1, 1};

	/**
	 * Four signals per cam shaft revolution
	 */
	int pinStates1[] = { 0, 0, 1 /* start of 2nd signal*/ , 0, 1 /* start of 3rd signal*/, 0, 0, 1, 0, 1 };


	int *pinStates[2] = { pinStates0, pinStates1 };

	weComplexInit("distributor", state, 0, 10, switchTimes, 2, pinStates);
}

void configureInjection(InjectionConfiguration *injectionConfiguration) {
	injectionConfiguration->fireAtEventIndex[1] = 1;
	injectionConfiguration->fireAtEventIndex[3] = 1;
}

#endif /* EFI_ENGINE_FORD_ASPIRE */
