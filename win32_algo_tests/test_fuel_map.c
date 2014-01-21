/**
 * @file	test_fuel_map.c
 *
 *  Created on: Nov 6, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "engine_configuration.h"
#include "fuel_map.h"
#include "trigger_structure.h"
#include "allsensors.h"

extern EngineConfiguration *engineConfiguration;

void testFuelMap(void) {
	chDbgCheck(engineConfiguration!=NULL, "engineConfiguration");

	printf("*************************************************** testFuelMap\r\n");

	for (int k = 0; k < FUEL_LOAD_COUNT; k++) {
		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
			engineConfiguration->fuelTable[k][r] = k * 200 + r;
		}
	}
	printf("*************************************************** initThermistors\r\n");

	initThermistors();

	printf("*** getInjectorLag\r\n");
	assertEquals(0, getInjectorLag(12));

	for (int i = 0; i < FUEL_LOAD_COUNT; i++)
		engineConfiguration->fuelLoadBins[i] = i;
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

	engineConfiguration->crankingSettings.coolantTempMin = 15;
	engineConfiguration->crankingSettings.coolantTempMax = 65;
	engineConfiguration->crankingSettings.minTempPW = 16;
	engineConfiguration->crankingSettings.maxTempPW = 8;

	printf("*************************************************** getStartingFuel\r\n");
	// NAN in case we have issues with the CLT sensor
	assertEquals(16, getStartingFuel(NAN));
	assertEquals(8, getStartingFuel(70));
}

static void confgiureFordAspireTriggerShape(trigger_shape_s * s) {
	triggerShapeInit(s);

	triggerAddEvent(s, 53.747, T_SECONDARY, 1);
	triggerAddEvent(s, 121.90, T_SECONDARY, 0);
	triggerAddEvent(s, 232.76, T_SECONDARY, 1);
	triggerAddEvent(s, 300.54, T_SECONDARY, 0);
	triggerAddEvent(s, 360, T_PRIMARY, 1);

	triggerAddEvent(s, 409.8412, T_SECONDARY, 1);
	triggerAddEvent(s, 478.6505, T_SECONDARY, 0);
	triggerAddEvent(s, 588.045, T_SECONDARY, 1);
	triggerAddEvent(s, 657.03, T_SECONDARY, 0);
	triggerAddEvent(s, 720, T_PRIMARY, 0);
}

static trigger_shape_s ts;
static ActuatorEventList ae;

extern int outputSignalCount;

void testAngleResolver(void) {
	printf("*************************************************** testAngleResolver\r\n");

	confgiureFordAspireTriggerShape(&ts);
	assertEquals(10, ts.size);

	outputSignalCount = 0;

	resetEventList(&ae);
	printf("*************************************************** testAngleResolver 0\r\n");
	registerActuatorEventExt(&ae, addOutputSignal(INJECTOR_1_OUTPUT), 53, &ts);
	assertEquals(1, ae.size);
	assertEquals(1, outputSignalCount);
	assertEquals(0, ae.events[0].eventIndex);
	assertEquals(53, ae.events[0].angleOffset);

	printf("*************************************************** testAngleResolver 2\r\n");
	resetEventList(&ae);
	registerActuatorEventExt(&ae, addOutputSignal(INJECTOR_1_OUTPUT), 51 + 180, &ts);
	assertEquals(2, ae.events[0].eventIndex);
	assertEquals(51.9870, ae.events[0].angleOffset);
}

