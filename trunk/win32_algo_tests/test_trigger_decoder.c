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

static void testDodgeNeonDecoder(void) {
	printf("*************************************************** testDodgeNeonDecoder\r\n");
	initTriggerDecoder();


	engine_configuration2_s ec2;
	setFordAspireengine_configuration2_s(&ec2);

	trigger_shape_s * shape = &ec2.triggerShape;
	trigger_state_s state;

	shape->syncRatioFrom = 0.72 * 0.8;
	shape->syncRatioTo = 0.72 * 1.3;

	int r = 0;
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_UP, r + 60);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_DOWN, r + 210);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_UP, r + 420);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_DOWN, r + 630);

	printf("2nd\r\n");
	r = 720;
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_UP, r + 60);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_DOWN, r + 210);
	assertTrue(state.shaft_is_synchronized);
	assertEquals(0, state.current_index);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_UP, r + 420);
	assertEquals(1, state.current_index);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_DOWN, r + 630);
	assertEquals(2, state.current_index);

	printf("3rd\r\n");
	r = 2 * 720;
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_UP, r + 60);
	assertEquals(3, state.current_index);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_DOWN, r + 210);
	assertTrue(state.shaft_is_synchronized);
	assertEquals(0, state.current_index);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_UP, r + 420);
	processTriggerEvent(&state, shape, SHAFT_PRIMARY_DOWN, r + 630);
}

static void test1995FordInline6TriggerDecoder(void) {
	printf("*************************************************** test1995FordInline6TriggerDecoder\r\n");

}


void testTriggerDecoder(void) {
	printf("*************************************************** testTriggerDecoder\r\n");
	testDodgeNeonDecoder();
	test1995FordInline6TriggerDecoder();
}
