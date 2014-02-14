/**
 * @file	test_trigger_decoder.c
 *
 * @date Dec 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "test_trigger_decoder.h"
#include "trigger_decoder.h"

#include "ford_aspire.h"
#include "dodge_neon.h"
#include "ford_1995_inline_6.h"

static void testDodgeNeonDecoder(void) {
	printf("*************************************************** testDodgeNeonDecoder\r\n");
	initTriggerDecoder();
	engine_configuration2_s ec2;
	setDodgeNeonengine_configuration2_s(&ec2);
	trigger_shape_s * shape = &ec2.triggerShape;
	trigger_state_s state;

	assertFalse(state.shaft_is_synchronized);

	int r = 0;
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_UP, r + 60);
	assertFalse(state.shaft_is_synchronized); // still no synchronization

	processTriggerEvent(&state, shape, SHAFT_PRIMARY_DOWN, r + 210);
	assertFalse(state.shaft_is_synchronized); // still no synchronization

	processTriggerEvent(&state, shape, SHAFT_PRIMARY_UP, r + 420);
	assertFalse(state.shaft_is_synchronized); // still no synchronization

	processTriggerEvent(&state, shape, SHAFT_PRIMARY_DOWN, r + 630);
	assertFalse(state.shaft_is_synchronized); // still no synchronization

	printf("2nd camshaft revolution\r\n");
	r = 720;
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_UP, r + 60);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_DOWN, r + 210);
	assertTrue(state.shaft_is_synchronized);
	assertEquals(0, state.current_index);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_UP, r + 420);
	assertEquals(1, state.current_index);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_DOWN, r + 630);
	assertEquals(2, state.current_index);

	printf("3rd camshaft revolution\r\n");
	r = 2 * 720;
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_UP, r + 60);
	assertEqualsM("current index", 3, state.current_index);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_DOWN, r + 210);
	assertTrue(state.shaft_is_synchronized);
	assertEqualsM("current index", 0, state.current_index);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_UP, r + 420);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_DOWN, r + 630);
}

static void test1995FordInline6TriggerDecoder(void) {
	printf("*************************************************** test1995FordInline6TriggerDecoder\r\n");
	initTriggerDecoder();
	engine_configuration2_s ec2;
	setFordInline6_2(&ec2);
	trigger_shape_s * shape = &ec2.triggerShape;
	trigger_state_s state;
	clearTriggerState(&state);

	assertFalseM("shaft_is_synchronized", state.shaft_is_synchronized);
	int r = 0;
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_DOWN, r + 10);
	assertFalseM("shaft_is_synchronized", state.shaft_is_synchronized); // still no synchronization
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_UP, r + 11);
	assertTrue(state.shaft_is_synchronized); // first signal rise synchronize

}


void testTriggerDecoder(void) {
	printf("*************************************************** testTriggerDecoder\r\n");
	testDodgeNeonDecoder();
	test1995FordInline6TriggerDecoder();
}
