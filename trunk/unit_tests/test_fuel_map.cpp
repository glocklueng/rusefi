/**
 * @file	test_fuel_map.cpp
 *
 * @date Nov 6, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "test_fuel_map.h"
#include "main.h"
#include "engine_configuration.h"
#include "fuel_math.h"
#include "trigger_structure.h"
#include "allsensors.h"
#include "engine_math.h"
#include "trigger_decoder.h"
#include "engine_test_helper.h"
#include "efiGpio.h"
#include "advance_map.h"

extern float testMafValue;

void testMafFuelMath(void) {
	printf("*************************************************** testMafFuelMath\r\n");
	EngineTestHelper eth(FORD_ASPIRE_1996);
	EXPAND_EngineTestHelper;

	engineConfiguration->algorithm = LM_REAL_MAF;
	engineConfiguration->injector.flow = 200;

	setMap(config->afrTable, 13);

	float fuelMs = getRealMafFuel(300, 6000 PASS_ENGINE_PARAMETER);
	assertEquals(26.7099, fuelMs);
}

void testFuelMap(void) {
	printf("*************************************************** testFuelMap\r\n");

	printf("Setting up FORD_ASPIRE_1996\r\n");
	EngineTestHelper eth(FORD_ASPIRE_1996);
	EXPAND_EngineTestHelper;

	printf("Filling fuel map\r\n");
	for (int k = 0; k < FUEL_LOAD_COUNT; k++) {
		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
			eth.engine.config->fuelTable[k][r] = k * 200 + r;
		}
	}
	for (int i = 0; i < FUEL_LOAD_COUNT; i++)
		eth.engine.config->fuelLoadBins[i] = i;
	for (int i = 0; i < FUEL_RPM_COUNT; i++)
		eth.engine.config->fuelRpmBins[i] = i;

	assertEqualsM("base fuel table", 1005, getBaseTableFuel(eth.engine.engineConfiguration, 5, 5));

	printf("*************************************************** initThermistors\r\n");

	initThermistors(NULL PASS_ENGINE_PARAMETER);

	printf("*** getInjectorLag\r\n");
	assertEquals(1.0, getInjectorLag(12 PASS_ENGINE_PARAMETER));

	eth.engine.engineConfiguration->injector.lag = 0.5;

	for (int i = 0; i < VBAT_INJECTOR_CURVE_SIZE; i++) {
		eth.engine.engineConfiguration->injector.battLagCorrBins[i] = i;
		eth.engine.engineConfiguration->injector.battLagCorr[i] = 2 * i;
	}

	eth.engine.updateSlowSensors();

	// because all the correction tables are zero
	printf("*************************************************** getRunningFuel 1\r\n");
	prepareTimingMap(PASS_ENGINE_PARAMETER_F);
	eth.engine.periodicFastCallback(PASS_ENGINE_PARAMETER_F);
	float baseFuel = getBaseTableFuel(eth.engine.engineConfiguration, 5, getEngineLoadT(PASS_ENGINE_PARAMETER_F));
	assertEqualsM("base fuel", 5.05, getRunningFuel(baseFuel, 5 PASS_ENGINE_PARAMETER));

	printf("*************************************************** setting IAT table\r\n");
	for (int i = 0; i < IAT_CURVE_SIZE; i++) {
		eth.engine.config->iatFuelCorrBins[i] = i;
		eth.engine.config->iatFuelCorr[i] = 2 * i;
	}
	eth.engine.config->iatFuelCorr[0] = 2;

	printf("*************************************************** setting CLT table\r\n");
	for (int i = 0; i < CLT_CURVE_SIZE; i++) {
		eth.engine.config->cltFuelCorrBins[i] = i;
		eth.engine.config->cltFuelCorr[i] = 1;
	}
	eth.engine.engineConfiguration->injector.lag = 0;

	assertEquals(NAN, getIntakeAirTemperature(PASS_ENGINE_PARAMETER_F));
	float iatCorrection = getIatCorrection(-KELV PASS_ENGINE_PARAMETER);
	assertEqualsM("IAT", 2, iatCorrection);
	float cltCorrection = getCltCorrection(getCoolantTemperature(PASS_ENGINE_PARAMETER_F) PASS_ENGINE_PARAMETER);
	assertEqualsM("CLT", 1, cltCorrection);
	float injectorLag = getInjectorLag(getVBatt(PASS_ENGINE_PARAMETER_F) PASS_ENGINE_PARAMETER);
	assertEquals(0, injectorLag);

	testMafValue = 5;

	// 1005 * 2 for IAT correction
	printf("*************************************************** getRunningFuel 2\r\n");
	eth.engine.periodicFastCallback(PASS_ENGINE_PARAMETER_F);
	baseFuel = getBaseTableFuel(eth.engine.engineConfiguration, 5, getEngineLoadT(PASS_ENGINE_PARAMETER_F));
	assertEqualsM("v1", 30150, getRunningFuel(baseFuel, 5 PASS_ENGINE_PARAMETER));

	testMafValue = 0;

	engineConfiguration->cranking.baseFuel = 4;

	printf("*************************************************** getStartingFuel\r\n");
	// NAN in case we have issues with the CLT sensor
	assertEqualsM("getStartingFuel nan", 4, getCrankingFuel3(NAN, 0 PASS_ENGINE_PARAMETER));
	assertEqualsM("getStartingFuel#1", 23.7333, getCrankingFuel3(0, 4 PASS_ENGINE_PARAMETER));
	assertEqualsM("getStartingFuel#2", 18.0419, getCrankingFuel3(8, 15 PASS_ENGINE_PARAMETER));
	assertEqualsM("getStartingFuel#3", 11.2000, getCrankingFuel3(70, 0 PASS_ENGINE_PARAMETER));
	assertEqualsM("getStartingFuel#3", 5.6000, getCrankingFuel3(70, 50 PASS_ENGINE_PARAMETER));
}

extern engine_configuration_s *engineConfiguration;

static void confgiureFordAspireTriggerShape(TriggerShape * s) {
	s->initialize(FOUR_STROKE_CAM_SENSOR, true);

	s->addEvent(53.747, T_SECONDARY, TV_HIGH);
	s->addEvent(121.90, T_SECONDARY, TV_LOW);
	s->addEvent(232.76, T_SECONDARY, TV_HIGH);
	s->addEvent(300.54, T_SECONDARY, TV_LOW);
	s->addEvent(360, T_PRIMARY, TV_HIGH);

	s->addEvent(409.8412, T_SECONDARY, TV_HIGH);
	s->addEvent(478.6505, T_SECONDARY, TV_LOW);
	s->addEvent(588.045, T_SECONDARY, TV_HIGH);
	s->addEvent(657.03, T_SECONDARY, TV_LOW);
	s->addEvent(720, T_PRIMARY, TV_LOW);

	assertEquals(53.747 / 720, s->wave.getSwitchTime(0));
	assertEqualsM("@0", 1, s->wave.getChannelState(1, 0));
	assertEqualsM("@0", 1, s->wave.getChannelState(1, 0));

	assertEqualsM("@1", 0, s->wave.getChannelState(0, 1));
	assertEqualsM("@1", 0, s->wave.getChannelState(1, 1));

	assertEqualsM("@2", 0, s->wave.getChannelState(0, 2));
	assertEqualsM("@2", 1, s->wave.getChannelState(1, 2));

	assertEqualsM("@3", 0, s->wave.getChannelState(0, 3));
	assertEqualsM("@3", 0, s->wave.getChannelState(1, 3));

	assertEqualsM("@4", 1, s->wave.getChannelState(0, 4));
	assertEqualsM("@5", 1, s->wave.getChannelState(1, 5));
	assertEqualsM("@8", 0, s->wave.getChannelState(1, 8));
	assertEquals(121.90 / 720, s->wave.getSwitchTime(1));
	assertEquals(657.03 / 720, s->wave.getSwitchTime(8));

	assertEqualsM("expecting 0", 0, s->wave.findAngleMatch(53.747 / 720.0, s->getSize()));
	assertEqualsM("expecting not found", -1, s->wave.findAngleMatch(53 / 720.0, s->getSize()));
	assertEquals(7, s->wave.findAngleMatch(588.045 / 720.0, s->getSize()));

	assertEqualsM("expecting 0", 0, s->wave.waveIndertionAngle(23.747 / 720.0, s->getSize()));
	assertEqualsM("expecting 1", 1, s->wave.waveIndertionAngle(63.747 / 720.0, s->getSize()));
}

static InjectionEventList ae;

void testAngleResolver(void) {
	printf("*************************************************** testAngleResolver\r\n");

	EngineTestHelper eth(FORD_ASPIRE_1996);
	EXPAND_EngineTestHelper;

	engineConfiguration->globalTriggerAngleOffset = 175;
	assertTrue(engine->engineConfiguration2!=NULL);
	TriggerShape * ts = &engine->triggerShape;
	ts->initializeTriggerShape(NULL PASS_ENGINE_PARAMETER);

	assertEqualsM("index 2", 52.76, ts->eventAngles[3]); // this angle is relation to synch point
	assertEqualsM("time 2", 0.3233, ts->wave.getSwitchTime(2));
	assertEqualsM("index 5", 412.76, ts->eventAngles[6]);
	assertEqualsM("time 5", 0.5733, ts->wave.getSwitchTime(5));

	assertEquals(4, ts->getTriggerShapeSynchPointIndex());

	assertEqualsM("shape size", 10, ts->getSize());

	ae.reset();
	printf("*************************************************** testAngleResolver 0\r\n");
	findTriggerPosition(&ae.add()->injectionStart, -122 PASS_ENGINE_PARAMETER);
	assertEqualsM("size", 1, ae.size);
	assertEquals(2, ae.elements[0].injectionStart.eventIndex);
	assertEquals(0.24, ae.elements[0].injectionStart.angleOffset);

	printf("*************************************************** testAngleResolver 0.1\r\n");
	ae.reset();
	findTriggerPosition(&ae.add()->injectionStart, -80 PASS_ENGINE_PARAMETER);
	assertEquals(2, ae.elements[0].injectionStart.eventIndex);
	assertEquals(42.24, ae.elements[0].injectionStart.angleOffset);

	printf("*************************************************** testAngleResolver 0.2\r\n");
	ae.reset();
	findTriggerPosition(&ae.add()->injectionStart, -54 PASS_ENGINE_PARAMETER);
	assertEquals(2, ae.elements[0].injectionStart.eventIndex);
	assertEquals(68.2400, ae.elements[0].injectionStart.angleOffset);

	printf("*************************************************** testAngleResolver 0.3\r\n");
	ae.reset();
	findTriggerPosition(&ae.add()->injectionStart, -53 PASS_ENGINE_PARAMETER);
	assertEquals(2, ae.elements[0].injectionStart.eventIndex);
	assertEquals(69.24, ae.elements[0].injectionStart.angleOffset);

	printf("*************************************************** testAngleResolver 1\r\n");
	ae.reset();
	findTriggerPosition(&ae.add()->injectionStart, 0 PASS_ENGINE_PARAMETER);
	assertEquals(2, ae.elements[0].injectionStart.eventIndex);
	assertEquals(122.24, ae.elements[0].injectionStart.angleOffset);

	printf("*************************************************** testAngleResolver 2\r\n");
	ae.reset();
	findTriggerPosition(&ae.add()->injectionStart, 56 PASS_ENGINE_PARAMETER);
	assertEquals(2, ae.elements[0].injectionStart.eventIndex);
	assertEquals(178.24, ae.elements[0].injectionStart.angleOffset);

	TriggerShape t;
	confgiureFordAspireTriggerShape(&t);
}

void testPinHelper(void) {
	printf("*************************************************** testPinHelper\r\n");
	assertEquals(0, getElectricalValue(0, OM_DEFAULT));
	assertEquals(1, getElectricalValue(1, OM_DEFAULT));

	assertEquals(0, getElectricalValue(1, OM_INVERTED));
	assertEquals(1, getElectricalValue(0, OM_INVERTED));
}
