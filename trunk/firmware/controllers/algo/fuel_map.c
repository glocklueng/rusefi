/*
 * fuel.c
 *
 *  Created on: May 27, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "fuel_map.h"
#include "interpolation_3d.h"
#include "engine_configuration.h"
#include "sensors.h"
#include "engine_controller.h"
#include "engine_math.h"
#include "settings.h"

static float *fuel_ptrs[FUEL_MAF_COUNT];
static int initialized = FALSE;
extern EngineConfiguration *engineConfiguration;

/**
 * this method has nothing to do with fuel map VALUES - it's job
 * is to prepare the fuel map data structure for 3d interpolation
 */
void prepareFuelMap(void) {
	for (int k = 0; k < FUEL_MAF_COUNT; k++)
		fuel_ptrs[k] = engineConfiguration->fuelTable[k];
	initialized = TRUE;
}

float getCltCorrection(float clt) {
	if (isnan(clt))
		return 1; // this error should be already reported somewhere else, let's just handle it
	return interpolate2d(clt, engineConfiguration->cltFuelCorrBins, engineConfiguration->cltFuelCorr, CLT_CURVE_SIZE);
}

float getIatCorrection(float iat) {
	if (isnan(iat))
		return 1; // this error should be already reported somewhere else, let's just handle it
	return interpolate2d(iat, engineConfiguration->iatFuelCorrBins, engineConfiguration->iatFuelCorr, IAT_CURVE_SIZE);
}

float getInjectorLag(float vBatt) {
	if (isnan(vBatt)) {
		warning("vBatt=", vBatt);
		return 0;
	}
	myfloat vBattCorrection = interpolate2d(vBatt, engineConfiguration->battInjectorLagCorrBins,
			engineConfiguration->battInjectorLagCorr, VBAT_INJECTOR_CURVE_SIZE);
	return engineConfiguration->injectorLag + vBattCorrection;
}

float getBaseFuel(int rpm, float key) {
	chDbgAssert(initialized, "fuel map initialized", NULL);
	// todo: use bins from the engineConfiguration
	return interpolate3d(key, engineConfiguration->fuelKeyBins, FUEL_MAF_COUNT, rpm, engineConfiguration->fuelRpmBins,
	FUEL_RPM_COUNT, fuel_ptrs);
}

float getCrankingFuel(void) {
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

float getFuel(int rpm, float key) {
	float baseFuel = getBaseFuel(rpm, key);

	float iatCorrection = getIatCorrection(getIntakeAirTemperature());
	float cltCorrection = getCltCorrection(getCoolantTemperature());
	float injectorLag = getInjectorLag(getVBatt());

	return baseFuel * cltCorrection * iatCorrection + injectorLag;
}
