/**
 * @file	fuel_math.c
 * @brief	Fuel amount calculation logic
 *
 * While engine running, fuel amount is an interpolated value from the fuel map by getRpm() and getEngineLoad()
 * On top of the value from the fuel map we also apply
 * <BR>1) getInjectorLag() correction to account for fuel injector lag
 * <BR>2) getCltCorrection() for warm-up
 * <BR>3) getIatCorrection() to account for cold weather
 *
 * getCrankingFuel() depents only on getCoolantTemperature()
 *
 *
 * @date May 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "fuel_math.h"
#include "interpolation.h"
#include "engine_configuration.h"
#include "allsensors.h"
#include "engine_math.h"

static float *fuel_ptrs[FUEL_LOAD_COUNT];
static int initialized = FALSE;
extern engine_configuration_s *engineConfiguration;

/**
 * @brief	Initialize fuel map data structure
 * @note this method has nothing to do with fuel map VALUES - it's job
 * is to prepare the fuel map data structure for 3d interpolation
 */
void prepareFuelMap(void) {
	for (int k = 0; k < FUEL_LOAD_COUNT; k++)
		fuel_ptrs[k] = engineConfiguration->fuelTable[k];
	initialized = TRUE;
}

/**
 * @brief Engine warm-up fuel correction.
 */
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

float getBaseFuel(int rpm, float engineLoad) {
	chDbgCheck(initialized, "fuel map initialized");
	return interpolate3d(engineLoad, engineConfiguration->fuelLoadBins, FUEL_LOAD_COUNT, rpm, engineConfiguration->fuelRpmBins,
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
		myfloat fuel = getRunningFuel(rpm, getEngineLoad());
		return fuel;
	}
}

float getRunningFuel(int rpm, float engineLoad) {
	float baseFuel = getBaseFuel(rpm, engineLoad);

	float iatCorrection = getIatCorrection(getIntakeAirTemperature());
	float cltCorrection = getCltCorrection(getCoolantTemperature());
	float injectorLag = getInjectorLag(getVBatt());

	return baseFuel * cltCorrection * iatCorrection + injectorLag;
}

float getStartingFuel(float coolantTemperature) {
	// these magic constants are in Celsius
	if (isnan(coolantTemperature)
			|| coolantTemperature
					< engineConfiguration->crankingSettings.coolantTempMinC)
		return engineConfiguration->crankingSettings.fuelAtMinTempMs;
	if (coolantTemperature
			> engineConfiguration->crankingSettings.coolantTempMaxC)
		return engineConfiguration->crankingSettings.fuelAtMaxTempMs;
	return interpolate(engineConfiguration->crankingSettings.coolantTempMinC,
			engineConfiguration->crankingSettings.fuelAtMinTempMs,
			engineConfiguration->crankingSettings.coolantTempMaxC,
			engineConfiguration->crankingSettings.fuelAtMaxTempMs,
			coolantTemperature);
}

/**
 * @return 0 for OM_DEFAULT and OM_OPENDRAIN
 */

inline static int getElectricalValue0(pin_output_mode_e mode) {
	return mode == OM_INVERTED || mode == OM_OPENDRAIN_INVERTED;
}

/**
 * @return 1 for OM_DEFAULT and OM_OPENDRAIN
 */
inline static int getElectricalValue1(pin_output_mode_e mode) {
	return mode == OM_DEFAULT || mode == OM_OPENDRAIN;
}

// todo: this method is here for unit test visibility. todo: move to a bette place!
int getElectricalValue(int logicalValue, pin_output_mode_e mode) {
	chDbgCheck(mode <= OM_OPENDRAIN_INVERTED, "invalid pin_output_mode_e");

	return logicalValue ? getElectricalValue1(mode) : getElectricalValue0(mode);
}

