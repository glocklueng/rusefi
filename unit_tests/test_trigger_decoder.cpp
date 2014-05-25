/**
 * @file	test_trigger_decoder.cpp
 *
 * @date Dec 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "test_trigger_decoder.h"
#include "trigger_decoder.h"
#include "engine_math.h"

#include "ford_aspire.h"
#include "dodge_neon.h"
#include "ford_1995_inline_6.h"
#include "mazda_323.h"
#include "rpm_calculator.h"

#include "trigger_central.h"
#include "main_trigger_callback.h"

extern int timeNow;

extern "C" {
void sendOutConfirmation(char *value, int i);
}

void sendOutConfirmation(char *value, int i) {
	// test implementation
}

int getTheAngle(engine_type_e engineType) {
	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;

	resetConfigurationExt(NULL, engineType, ec, &ec2, &persistentConfig.boardConfiguration);

	trigger_shape_s * shape = &ec2.triggerShape;
	return findTriggerZeroEventIndex(shape, &ec->triggerConfig);
}

static void testDodgeNeonDecoder(void) {
	printf("*************************************************** testDodgeNeonDecoder\r\n");
	initTriggerDecoder();

	assertEqualsM("trigger zero index", 8, getTheAngle(DODGE_NEON_1995));

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;

	resetConfigurationExt(NULL, DODGE_NEON_1995, ec, &ec2, &persistentConfig.boardConfiguration);

	trigger_shape_s * shape = &ec2.triggerShape;
	TriggerState state;
//
//	assertFalseM("1 shaft_is_synchronized", state.shaft_is_synchronized);
//
//	int r = 0;
//	processTriggerEvent(&state, shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, r + 60);
//	assertFalseM("2 shaft_is_synchronized", state.shaft_is_synchronized); // still no synchronization
//
//	processTriggerEvent(&state, shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r + 210);
//	assertFalseM("3 shaft_is_synchronized", state.shaft_is_synchronized); // still no synchronization
//
//	processTriggerEvent(&state, shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, r + 420);
//	assertFalseM("4 shaft_is_synchronized", state.shaft_is_synchronized); // still no synchronization
//
//	processTriggerEvent(&state, shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r + 630);
//	assertFalse(state.shaft_is_synchronized); // still no synchronization
//
//	printf("2nd camshaft revolution\r\n");
//	r = 720;
//	processTriggerEvent(&state, shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, r + 60);
//	processTriggerEvent(&state, shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r + 210);
//	assertTrue(state.shaft_is_synchronized);
//	assertEquals(0, state.current_index);
//	processTriggerEvent(&state, shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, r + 420);
//	assertEquals(1, state.current_index);
//	processTriggerEvent(&state, shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r + 630);
//	assertEquals(2, state.current_index);
//
//	printf("3rd camshaft revolution\r\n");
//	r = 2 * 720;
//	processTriggerEvent(&state, shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, r + 60);
//	assertEqualsM("current index", 3, state.current_index);
//	processTriggerEvent(&state, shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r + 210);
//	assertTrue(state.shaft_is_synchronized);
//	assertEqualsM("current index", 0, state.current_index);
//	processTriggerEvent(&state, shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, r + 420);
//	processTriggerEvent(&state, shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r + 630);
}

static void test1995FordInline6TriggerDecoder(void) {
	printf("*************************************************** test1995FordInline6TriggerDecoder\r\n");

	assertEqualsM("triggerIndex ", 0, getTheAngle(FORD_INLINE_6_1995));

	initTriggerDecoder();

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;

	resetConfigurationExt(NULL, FORD_INLINE_6_1995, ec, &ec2, &persistentConfig.boardConfiguration);

	ActuatorEventList *ecl = &ec2.engineEventConfiguration.ignitionEvents[0];
	assertEqualsM("ignition events size", 6, ecl->size);
	assertEqualsM("event index", 0, ecl->events[0].position.eventIndex);
	assertEquals(0, ecl->events[0].position.angleOffset);

	assertEqualsM("event index", 10, ecl->events[5].position.eventIndex);
	assertEquals(0, ecl->events[5].position.angleOffset);

	TriggerState state;

	trigger_shape_s * shape = &ec2.triggerShape;
	assertFalseM("shaft_is_synchronized", state.shaft_is_synchronized);
	int r = 10;
	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r);
	assertFalseM("shaft_is_synchronized", state.shaft_is_synchronized); // still no synchronization
	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, ++r);
	assertTrue(state.shaft_is_synchronized); // first signal rise synchronize
	assertEquals(0, state.getCurrentIndex());
	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r++);
	assertEquals(1, state.getCurrentIndex());

	for (int i = 2; i < 10;) {
		state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, r++);
		assertEqualsM("even", i++, state.getCurrentIndex());
		state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r++);
		assertEqualsM("odd", i++, state.getCurrentIndex());
	}

	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, r++);
	assertEquals(10, state.getCurrentIndex());

	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r++);
	assertEquals(11, state.getCurrentIndex());

	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, r++);
	assertEquals(0, state.getCurrentIndex()); // new revolution

	assertEqualsM("running dwell", 0.5, getSparkDwellMsT(ec, 2000));
}

void testFordAspire(void) {
	printf("*************************************************** testFordAspire\r\n");

	assertEquals(4, getTheAngle(FORD_ASPIRE_1996));

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;
	resetConfigurationExt(NULL, FORD_ASPIRE_1996, ec, &ec2, &persistentConfig.boardConfiguration);

	assertEquals(800, ec->fuelRpmBins[0]);
	assertEquals(7000, ec->fuelRpmBins[15]);

	ec->crankingChargeAngle = 65;
	ec->crankingTimingAngle = 31;

	assertEqualsM("cranking dwell", 54.166670, getSparkDwellMsT(ec, 200));
	assertEqualsM("running dwell", 4, getSparkDwellMsT(ec, 2000));

	assertEqualsM("higher rpm dwell", 3.25, getSparkDwellMsT(ec, 6000));
}

void testMazda323(void) {
	printf("*************************************************** testMazda323\r\n");

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;
	resetConfigurationExt(NULL, MAZDA_323, ec, &ec2, &persistentConfig.boardConfiguration);

}

void testMazdaMianaNbDecoder(void) {
	printf("*************************************************** testMazdaMianaNbDecoder\r\n");

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;
	resetConfigurationExt(NULL, MAZDA_MIATA_NB, ec, &ec2, &persistentConfig.boardConfiguration);

	TriggerState state;
	trigger_shape_s * shape = &ec2.triggerShape;

	int a = 0;
	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, a + 20);
	assertFalseM("0a shaft_is_synchronized", state.shaft_is_synchronized);
	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, a + 340);
	assertFalseM("0b shaft_is_synchronized", state.shaft_is_synchronized);

	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, a + 360);
	assertFalseM("0c shaft_is_synchronized", state.shaft_is_synchronized);
	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, a + 380);
	assertFalseM("0d shaft_is_synchronized", state.shaft_is_synchronized);
	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, a + 400);
	assertTrueM("0e shaft_is_synchronized", state.shaft_is_synchronized);

	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, a + 720);
	assertTrueM("0f shaft_is_synchronized", state.shaft_is_synchronized);

	a = 720;
	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, a + 20);
	assertTrueM("1a shaft_is_synchronized", state.shaft_is_synchronized);
	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, a + 340);
	assertTrueM("1b shaft_is_synchronized", state.shaft_is_synchronized);

	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, a + 360);
	assertTrueM("1c shaft_is_synchronized", state.shaft_is_synchronized);
	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, a + 380);
	assertTrueM("1d shaft_is_synchronized", state.shaft_is_synchronized);
	assertEquals(5, state.getCurrentIndex());

	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, a + 400);
	assertTrueM("1e shaft_is_synchronized", state.shaft_is_synchronized);
	assertEquals(0, state.getCurrentIndex());

	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, a + 720);
	assertTrueM("1f shaft_is_synchronized", state.shaft_is_synchronized);

}

static void testMiniCooper(void) {
	printf("*************************************************** testMiniCooper\r\n");

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;
	resetConfigurationExt(NULL, MINI_COOPER_R50, ec, &ec2, &persistentConfig.boardConfiguration);

}

static void testFordEscortGt(void) {
	printf("*************************************************** testFordEscortGt\r\n");

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;
	resetConfigurationExt(NULL, FORD_ESCORT_GT, ec, &ec2, &persistentConfig.boardConfiguration);
}

void testGY6_139QMB(void) {
	printf("*************************************************** testGY6_139QMB\r\n");

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;
	resetConfigurationExt(NULL, GY6_139QMB, ec, &ec2, &persistentConfig.boardConfiguration);

	TriggerState state;
	assertFalseM("shaft_is_synchronized", state.shaft_is_synchronized);

	trigger_shape_s * shape = &ec2.triggerShape;

	assertFalseM("shaft_is_synchronized", state.shaft_is_synchronized);
	assertEquals(0, state.getCurrentIndex());

	int now = 0;
	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, now++);
	assertTrueM("shaft_is_synchronized", state.shaft_is_synchronized);
	assertEquals(0, state.getCurrentIndex());

	state.processTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, now++);
	assertTrueM("shaft_is_synchronized", state.shaft_is_synchronized);
	assertEquals(1, state.getCurrentIndex());
}

static void testRpmCalculator(void) {
	printf("*************************************************** testRpmCalculator\r\n");

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;

	resetConfigurationExt(NULL, FORD_INLINE_6_1995, ec, &ec2, &persistentConfig.boardConfiguration);

	ec->triggerConfig.totalToothCount = 4;
	initializeTriggerShape(NULL, ec, &ec2);
	incrementGlobalConfigurationVersion();

	configuration_s configuration = { ec, &ec2 };

	TriggerCentral triggerCentral;

	timeNow = 0;

	RpmCalculator rpmState;
	assertEquals(0, rpmState.rpm);
	triggerCentral.addEventListener((ShaftPositionListener) &shaftPositionCallback, "rpm reporter", &rpmState);

	for (int i = 0; i < 12; i++) {
		timeNow += 5000; // 5ms
		triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_UP, timeNow);
		timeNow += 5000;
		triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_DOWN, timeNow);
	}
	assertEqualsM("RPM", 3000, rpmState.rpm);

	assertEqualsM("index #1", 7, triggerCentral.triggerState.getCurrentIndex());


	MainTriggerCallback triggerCallbackInstance;
	triggerCallbackInstance.init(ec, &ec2);
	triggerCentral.addEventListener((ShaftPositionListener)&onTriggerEvent, "main loop", &triggerCallbackInstance);
	timeNow += 5000; // 5ms
	triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_UP, timeNow);
	assertEqualsM("index #2", 0, triggerCentral.triggerState.getCurrentIndex());


}

void testTriggerDecoder(void) {
	printf("*************************************************** testTriggerDecoder\r\n");

	engine_configuration2_s ec2;

	initializeSkippedToothTriggerShapeExt(&ec2, 2, 0);
	assertEqualsM("shape size", ec2.triggerShape.getSize(), 4);
	assertEquals(ec2.triggerShape.wave.switchTimes[0], 0.25);
	assertEquals(ec2.triggerShape.wave.switchTimes[1], 0.5);
	assertEquals(ec2.triggerShape.wave.switchTimes[2], 0.75);
	assertEquals(ec2.triggerShape.wave.switchTimes[3], 1);

	testDodgeNeonDecoder();
	testFordAspire();
	test1995FordInline6TriggerDecoder();
	testMazdaMianaNbDecoder();
	testGY6_139QMB();
	testFordEscortGt();
	testMiniCooper();

//	testMazda323();

	testRpmCalculator();
}

