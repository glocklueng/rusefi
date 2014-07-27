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
#include "event_queue.h"
#include "algo.h"

#include "trigger_central.h"
#include "main_trigger_callback.h"
#include "engine.h"
#include "advance_map.h"
#include "engine_test_helper.h"
#include "speed_density.h"

Engine engine;

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

	initDataStructures(ec);
	resetConfigurationExt(NULL, engineType, ec, &ec2, &persistentConfig.engineConfiguration.bc);

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

	resetConfigurationExt(NULL, DODGE_NEON_1995, ec, &ec2, &persistentConfig.engineConfiguration.bc);
	assertEquals(8, ec2.triggerShape.getTriggerShapeSynchPointIndex());

	trigger_shape_s * shape = &ec2.triggerShape;
	TriggerState state;

	assertFalseM("1 shaft_is_synchronized", state.shaft_is_synchronized);

	int r = 0;
//	processTriggerEvent(&state, shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, r + 60);
//	assertFalseM("2 shaft_is_synchronized", state.shaft_is_synchronized); // still no synchronization

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

static void assertTriggerPosition(event_trigger_position_s *position, int eventIndex, float angleOffset) {
	assertEqualsM("eventIndex", eventIndex, position->eventIndex);
	assertEqualsM("angleOffset", angleOffset, position->angleOffset);
}

static void test1995FordInline6TriggerDecoder(void) {
	printf("*************************************************** test1995FordInline6TriggerDecoder\r\n");

	assertEqualsM("triggerIndex ", 0, getTheAngle(FORD_INLINE_6_1995));

	initTriggerDecoder();

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;

	resetConfigurationExt(NULL, FORD_INLINE_6_1995, ec, &ec2, &persistentConfig.engineConfiguration.bc);
	assertEqualsM("triggerShapeSynchPointIndex", 0, ec2.triggerShape.getTriggerShapeSynchPointIndex());

	trigger_shape_s * shape = &ec2.triggerShape;
	event_trigger_position_s position;
	assertEqualsM("globalTriggerAngleOffset", 0, ec->globalTriggerAngleOffset);
	findTriggerPosition(ec, shape, &position, 0);
	assertTriggerPosition(&position, 0, 0);

	findTriggerPosition(ec, shape, &position, 200);
	assertTriggerPosition(&position, 3, 20);

	findTriggerPosition(ec, shape, &position, 360);
	assertTriggerPosition(&position, 6, 0);


	IgnitionEventList *ecl = &ec2.engineEventConfiguration.ignitionEvents[0];
	assertEqualsM("ignition events size", 6, ecl->size);
	assertEqualsM("event index", 0, ecl->events[0].dwellPosition.eventIndex);
	assertEquals(0, ecl->events[0].dwellPosition.angleOffset);

	assertEqualsM("event index", 10, ecl->events[5].dwellPosition.eventIndex);
	assertEquals(0, ecl->events[5].dwellPosition.angleOffset);

	TriggerState state;

	assertFalseM("shaft_is_synchronized", state.shaft_is_synchronized);
	int r = 10;
	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r);
	assertFalseM("shaft_is_synchronized", state.shaft_is_synchronized); // still no synchronization
	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, ++r);
	assertTrue(state.shaft_is_synchronized); // first signal rise synchronize
	assertEquals(0, state.getCurrentIndex());
	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r++);
	assertEquals(1, state.getCurrentIndex());

	for (int i = 2; i < 10;) {
		state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, r++);
		assertEqualsM("even", i++, state.getCurrentIndex());
		state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r++);
		assertEqualsM("odd", i++, state.getCurrentIndex());
	}

	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, r++);
	assertEquals(10, state.getCurrentIndex());

	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, r++);
	assertEquals(11, state.getCurrentIndex());

	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, r++);
	assertEquals(0, state.getCurrentIndex()); // new revolution

	assertEqualsM("running dwell", 0.5, getSparkDwellMsT(ec, 2000));
}

void testFordAspire(void) {
	printf("*************************************************** testFordAspire\r\n");

	assertEquals(4, getTheAngle(FORD_ASPIRE_1996));

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;
	resetConfigurationExt(NULL, FORD_ASPIRE_1996, ec, &ec2, &persistentConfig.engineConfiguration.bc);
	assertEquals(4, ec2.triggerShape.getTriggerShapeSynchPointIndex());

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
	resetConfigurationExt(NULL, MAZDA_323, ec, &ec2, &persistentConfig.engineConfiguration.bc);
	assertEquals(0, ec2.triggerShape.getTriggerShapeSynchPointIndex());
}

void testMazdaMianaNbDecoder(void) {
	printf("*************************************************** testMazdaMianaNbDecoder\r\n");

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;
	resetConfigurationExt(NULL, MAZDA_MIATA_NB, ec, &ec2, &persistentConfig.engineConfiguration.bc);
	assertEquals(11, ec2.triggerShape.getTriggerShapeSynchPointIndex());

	TriggerState state;
	trigger_shape_s * shape = &ec2.triggerShape;

	int a = 0;
	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, a + 20);
	assertFalseM("0a shaft_is_synchronized", state.shaft_is_synchronized);
	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, a + 340);
	assertFalseM("0b shaft_is_synchronized", state.shaft_is_synchronized);

	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, a + 360);
	assertFalseM("0c shaft_is_synchronized", state.shaft_is_synchronized);
	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, a + 380);
	assertFalseM("0d shaft_is_synchronized", state.shaft_is_synchronized);
	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, a + 400);
	assertTrueM("0e shaft_is_synchronized", state.shaft_is_synchronized);

	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, a + 720);
	assertTrueM("0f shaft_is_synchronized", state.shaft_is_synchronized);

	a = 720;
	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, a + 20);
	assertTrueM("1a shaft_is_synchronized", state.shaft_is_synchronized);
	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, a + 340);
	assertTrueM("1b shaft_is_synchronized", state.shaft_is_synchronized);

	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, a + 360);
	assertTrueM("1c shaft_is_synchronized", state.shaft_is_synchronized);
	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, a + 380);
	assertTrueM("1d shaft_is_synchronized", state.shaft_is_synchronized);
	assertEquals(5, state.getCurrentIndex());

	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, a + 400);
	assertTrueM("1e shaft_is_synchronized", state.shaft_is_synchronized);
	assertEquals(0, state.getCurrentIndex());

	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, a + 720);
	assertTrueM("1f shaft_is_synchronized", state.shaft_is_synchronized);

	event_trigger_position_s position;
	assertEqualsM("globalTriggerAngleOffset", 276, ec->globalTriggerAngleOffset);
	findTriggerPosition(ec, shape, &position, 0);
	assertTriggerPosition(&position, 7, 46);

	findTriggerPosition(ec, shape, &position, 180);
	assertTriggerPosition(&position, 13, 46);

	findTriggerPosition(ec, shape, &position, 360);
	assertTriggerPosition(&position, 17, 46);

	findTriggerPosition(ec, shape, &position, 444);
	assertTriggerPosition(&position, 0, 0);

	findTriggerPosition(ec, shape, &position, 444.1);
	assertTriggerPosition(&position, 0, 0.1);

	findTriggerPosition(ec, shape, &position, 445);
	assertTriggerPosition(&position, 0, 1);

	findTriggerPosition(ec, shape, &position, 494);
	assertTriggerPosition(&position, 3, 0);

	findTriggerPosition(ec, shape, &position, 719);
	assertTriggerPosition(&position, 7, 45);

	ec->globalTriggerAngleOffset = 0;
	findTriggerPosition(ec, shape, &position, 0);
	assertTriggerPosition(&position, 0, 0);

	ec->globalTriggerAngleOffset = 10;
	findTriggerPosition(ec, shape, &position, 0);
	assertTriggerPosition(&position, 0, 10);

	findTriggerPosition(ec, shape, &position, -10);
	assertTriggerPosition(&position, 0, 0);
}

static void testTriggerDecoder(const char *msg, engine_type_e type, int synchPointIndex) {
	printf("*************************************************** %s\r\n", msg);

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;
	assertEquals(0, ec2.triggerShape.getTriggerShapeSynchPointIndex());

	resetConfigurationExt(NULL, type, ec, &ec2, &persistentConfig.engineConfiguration.bc);

	assertEquals(synchPointIndex, ec2.triggerShape.getTriggerShapeSynchPointIndex());
}

static void testRoverV8(void) {
	testTriggerDecoder("testRoverV8", ROVER_V8, 0);
}

static void testMiniCooper(void) {
	testTriggerDecoder("testMiniCooper", MINI_COOPER_R50, 121);
}

static void testFordEscortGt(void) {
}

void testGY6_139QMB(void) {
	printf("*************************************************** testGY6_139QMB\r\n");

	persistent_config_s persistentConfig;
	engine_configuration_s *ec = &persistentConfig.engineConfiguration;
	engine_configuration2_s ec2;
	resetConfigurationExt(NULL, GY6_139QMB, ec, &ec2, &persistentConfig.engineConfiguration.bc);

	TriggerState state;
	assertFalseM("shaft_is_synchronized", state.shaft_is_synchronized);

	trigger_shape_s * shape = &ec2.triggerShape;

	assertFalseM("shaft_is_synchronized", state.shaft_is_synchronized);
	assertEquals(0, state.getCurrentIndex());

	int now = 0;
	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_UP, now++);
	assertTrueM("shaft_is_synchronized", state.shaft_is_synchronized);
	assertEquals(0, state.getCurrentIndex());

	state.decodeTriggerEvent(shape, &ec->triggerConfig, SHAFT_PRIMARY_DOWN, now++);
	assertTrueM("shaft_is_synchronized", state.shaft_is_synchronized);
	assertEquals(1, state.getCurrentIndex());
}

extern EventQueue schedulingQueue;

static void testRpmCalculator(void) {
	printf("*************************************************** testRpmCalculator\r\n");

	EngineTestHelper eth(FORD_INLINE_6_1995);

	engine_configuration_s *ec = &eth.persistentConfig.engineConfiguration;

	engine_configuration2_s *ec2 = &eth.ec2;

	ec->triggerConfig.customTotalToothCount = 8;
	eth.initTriggerShapeAndRpmCalculator();

	configuration_s configuration = { ec, ec2 };
	timeNow = 0;
	assertEquals(0, eth.rpmState.rpm());

	eth.fireTriggerEvents();
	assertEqualsM("RPM", 1500, eth.rpmState.rpm());

	assertEqualsM("index #1", 15, eth.triggerCentral.triggerState.getCurrentIndex());


	static MainTriggerCallback triggerCallbackInstance;
	triggerCallbackInstance.init(&eth.engine, ec2);
	eth.triggerCentral.addEventListener((ShaftPositionListener)&onTriggerEvent, "main loop", &triggerCallbackInstance);

	engine.rpmCalculator = &eth.rpmState;
	prepareTimingMap();

	timeNow += 5000; // 5ms
	eth.triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_UP, timeNow);
	assertEqualsM("index #2", 0, eth.triggerCentral.triggerState.getCurrentIndex());
	assertEqualsM("queue size", 2, schedulingQueue.size());
	assertEqualsM("ev 1", 695000, schedulingQueue.getForUnitText(0)->momentUs);
	assertEqualsM("ev 2", 245000, schedulingQueue.getForUnitText(1)->momentUs);
	schedulingQueue.clear();

	timeNow += 5000;
	eth.triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_DOWN, timeNow);
	timeNow += 5000; // 5ms
	eth.triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_UP, timeNow);
	timeNow += 5000;
	eth.triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_DOWN, timeNow);
	assertEqualsM("index #3", 3, eth.triggerCentral.triggerState.getCurrentIndex());
	assertEqualsM("queue size 3", 4, schedulingQueue.size());
	assertEquals(258333, schedulingQueue.getForUnitText(0)->momentUs);
	assertEquals(257833, schedulingQueue.getForUnitText(1)->momentUs);
	assertEqualsM("ev 5", 708333, schedulingQueue.getForUnitText(2)->momentUs);
	assertEqualsM("3/3", 258333, schedulingQueue.getForUnitText(3)->momentUs);
	schedulingQueue.clear();

	timeNow += 5000;
	eth.triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_DOWN, timeNow);
	timeNow += 5000; // 5ms
	eth.triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_UP, timeNow);
	timeNow += 5000; // 5ms
	eth.triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_UP, timeNow);
	assertEqualsM("index #4", 6, eth.triggerCentral.triggerState.getCurrentIndex());
	assertEqualsM("queue size 4", 4, schedulingQueue.size());
	assertEqualsM("4/0", 271666, schedulingQueue.getForUnitText(0)->momentUs);
	schedulingQueue.clear();

	timeNow += 5000;
	eth.triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_DOWN, timeNow);
	assertEqualsM("queue size 5", 1, schedulingQueue.size());
	assertEqualsM("5/1", 284500, schedulingQueue.getForUnitText(0)->momentUs);
	schedulingQueue.clear();

	timeNow += 5000; // 5ms
	eth.triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_UP, timeNow);
	assertEqualsM("queue size 6", 3, schedulingQueue.size());
	assertEqualsM("6/0", 285000, schedulingQueue.getForUnitText(0)->momentUs);
	assertEqualsM("6/1", 735000, schedulingQueue.getForUnitText(1)->momentUs);
	assertEqualsM("6/0", 285000, schedulingQueue.getForUnitText(2)->momentUs);
	schedulingQueue.clear();

	timeNow += 5000;
	eth.triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_DOWN, timeNow);
	assertEqualsM("queue size 7", 0, schedulingQueue.size());
	schedulingQueue.clear();

	timeNow += 5000; // 5ms
	eth.triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_UP, timeNow);
	assertEqualsM("queue size 8", 4, schedulingQueue.size());
	assertEqualsM("8/0", 298333, schedulingQueue.getForUnitText(0)->momentUs);
	assertEqualsM("8/1", 297833, schedulingQueue.getForUnitText(1)->momentUs);
	assertEqualsM("8/2", 748333, schedulingQueue.getForUnitText(2)->momentUs);
	assertEqualsM("8/3", 298333, schedulingQueue.getForUnitText(3)->momentUs);
	schedulingQueue.clear();

	timeNow += 5000;
	eth.triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_DOWN, timeNow);
	assertEqualsM("queue size 9", 0, schedulingQueue.size());
	schedulingQueue.clear();

	timeNow += 5000; // 5ms
	eth.triggerCentral.handleShaftSignal(&configuration, SHAFT_PRIMARY_UP, timeNow);
	assertEqualsM("queue size 10", 0, schedulingQueue.size());
	schedulingQueue.clear();
}

void testTriggerDecoder(void) {
	printf("*************************************************** testTriggerDecoder\r\n");

	engine_configuration2_s ec2;

	initializeSkippedToothTriggerShapeExt(&ec2.triggerShape, 2, 0, FOUR_STROKE_CAM_SENSOR);
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
	testTriggerDecoder("testFordEscortGt", FORD_ESCORT_GT, 0);
	testMiniCooper();
	testRoverV8();
	testTriggerDecoder("testCitroen", CITROEN_TU3JP, 0);
	testTriggerDecoder("testFordEscortGt", FORD_ESCORT_GT, 0);
	testTriggerDecoder("testAccordCd", HONDA_ACCORD_CD, 0);

	testMazda323();

	testRpmCalculator();
}
