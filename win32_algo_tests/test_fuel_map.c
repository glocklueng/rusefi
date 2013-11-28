/*
 * test_fuel_map.c
 *
 *  Created on: Nov 6, 2013
 *      Author: pc
 */

#include "main.h"
#include "engine_configuration.h"
#include "fuel_map.h"

static EngineConfiguration ec;

EngineConfiguration *engineConfiguration = &ec;


float getCoolantTemperature() {
	return 1;
}

float getVBatt() {
	return 1;
}

float getIntakeAirTemperature() {
	return 1;
}

void testFuelMap(void) {
	printf("*************************************************** testFuelMap\r\n");

	for (int k = 0; k < FUEL_MAF_COUNT; k++) {
		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
			engineConfiguration->fuelTable[k][r] = k * 200 + r;
		}
	}

	assertEquals(0, getInjectorLag(12));

	for (int i = 0; i < FUEL_MAF_COUNT; i++)
		engineConfiguration->fuelKeyBins[i] = i;
	for (int i = 0; i < FUEL_RPM_COUNT; i++)
		engineConfiguration->fuelRpmBins[i] = i;


	prepareFuelMap();
	assertEquals(1005, getBaseFuel(5, 5));

	engineConfiguration->injectorLag = 0.5;
	// because all the correction tables are zero
	assertEquals(0.5, getRunningFuel(5, 5));

	for (int i = 0; i < IAT_CURVE_SIZE; i++) {
		engineConfiguration->iatFuelCorrBins[i] = i;
		engineConfiguration->iatFuelCorr[i] = 2 * i;
	}

	for (int i = 0; i < CLT_CURVE_SIZE; i++) {
		engineConfiguration->cltFuelCorrBins[i] = i;
		engineConfiguration->cltFuelCorr[i] = 1;
	}
	engineConfiguration->injectorLag = 0;

	// 1005 * 2 for IAT correction
	assertEquals(2010, getRunningFuel(5, 5));

}
