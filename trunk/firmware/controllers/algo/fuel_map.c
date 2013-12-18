/**
 * @file	fuel_map.c
 * @brief	Fuel calculation methods
 *
 * @date May 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "fuel_map.h"
#include "interpolation.h"
#include "engine_configuration.h"
#include "allsensors.h"
#include "engine_math.h"

static float *fuel_ptrs[FUEL_MAF_COUNT];
static int initialized = FALSE;
extern EngineConfiguration *engineConfiguration;

/**
 * @brief	Initialize fuel map data structure
 * @note this method has nothing to do with fuel map VALUES - it's job
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

/**
 * @brief	Injector lag correction
 * @param	vBatt	Battery voltage.
 * @return	Time in ms for injection opening time based on current battery voltage
 */
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
	return interpolate3d(key, engineConfiguration->fuelKeyBins, FUEL_MAF_COUNT, rpm, engineConfiguration->fuelRpmBins,
	FUEL_RPM_COUNT, fuel_ptrs);
}

float getCrankingFuel(void) {
	return getStartingFuel(getCoolantTemperature());
}

int isCranking(void);

/**
 * @returns	Length of fuel injection, in milliseconds
 */
float getFuelMs(int rpm) {
	if (isCranking()) {
		return getCrankingFuel();
	} else {
		myfloat fuel = getRunningFuel(rpm, getMaf());
		return fuel;
	}
}

float getRunningFuel(int rpm, float key) {
	float baseFuel = getBaseFuel(rpm, key);

	float iatCorrection = getIatCorrection(getIntakeAirTemperature());
	float cltCorrection = getCltCorrection(getCoolantTemperature());
	float injectorLag = getInjectorLag(getVBatt());

	return baseFuel * cltCorrection * iatCorrection + injectorLag;
}
