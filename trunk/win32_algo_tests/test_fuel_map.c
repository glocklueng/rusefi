/**
 * @file	test_fuel_map.c
 *
 *  Created on: Nov 6, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "engine_configuration.h"
#include "fuel_map.h"
#include "allsensors.h"

extern EngineConfiguration *engineConfiguration;

void testFuelMap(void) {
	chDbgCheck(engineConfiguration!=NULL, "engineConfiguration");

	printf("*************************************************** testFuelMap\r\n");

	for (int k = 0; k < FUEL_MAF_COUNT; k++) {
		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
			engineConfiguration->fuelTable[k][r] = k * 200 + r;
		}
	}
	printf("*************************************************** initThermistors\r\n");

	initThermistors();

	printf("*** getInjectorLag\r\n");
	assertEquals(0, getInjectorLag(12));

	for (int i = 0; i < FUEL_MAF_COUNT; i++)
		engineConfiguration->fuelKeyBins[i] = i;
	for (int i = 0; i < FUEL_RPM_COUNT; i++)
		engineConfiguration->fuelRpmBins[i] = i;

	printf("*************************************************** prepareFuelMap\r\n");
	prepareFuelMap();
	assertEquals(1005, getBaseFuel(5, 5));

	engineConfiguration->injectorLag = 0.5;
	// because all the correction tables are zero
	printf("*************************************************** getRunningFuel\r\n");
	assertEquals(1005.5, getRunningFuel(5, 5));

	printf("*************************************************** setting IAT table\r\n");
	for (int i = 0; i < IAT_CURVE_SIZE; i++) {
		engineConfiguration->iatFuelCorrBins[i] = i;
		engineConfiguration->iatFuelCorr[i] = 2 * i;
	}
	engineConfiguration->iatFuelCorr[0] = 2;

	printf("*************************************************** setting CLT table\r\n");
	for (int i = 0; i < CLT_CURVE_SIZE; i++) {
		engineConfiguration->cltFuelCorrBins[i] = i;
		engineConfiguration->cltFuelCorr[i] = 1;
	}
	engineConfiguration->injectorLag = 0;

	assertEquals(NAN, getIntakeAirTemperature());
	float iatCorrection = getIatCorrection(-KELV);
	assertEqualsM("IAT", 2, iatCorrection);
	float cltCorrection = getCltCorrection(getCoolantTemperature());
	assertEqualsM("CLT", 1, cltCorrection);
	float injectorLag = getInjectorLag(getVBatt());
	assertEquals(0, injectorLag);

	// 1005 * 2 for IAT correction
	printf("*************************************************** getRunningFuel\r\n");
	assertEquals(1005, getRunningFuel(5, 5));
}
