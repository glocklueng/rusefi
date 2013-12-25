/**
 * @file	test_trigger_decoder.c
 *
 * @date Dec 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "test_trigger_decoder.h"
#include "trigger_decoder.h"

void testTriggerDecoder(void) {
	printf("*************************************************** testTriggerDecoder\r\n");

	initTriggerDecoder();

	trigger_state_s state;
	trigger_shape_s shape;

	shape.useRiseEdge = FALSE;
	shape.syncRatioFrom = 0.72 * 0.8;
	shape.syncRatioTo = 0.72 * 1.3;

	int r = 0;
	processTriggerEvent(&state, &shape, SHAFT_PRIMARY_UP, r + 60);
	processTriggerEvent(&state, &shape, SHAFT_PRIMARY_DOWN, r + 210);
	processTriggerEvent(&state, &shape, SHAFT_PRIMARY_UP, r + 420);
	processTriggerEvent(&state, &shape, SHAFT_PRIMARY_DOWN, r + 630);

	printf("2nd\r\n");
	r = 720;
	processTriggerEvent(&state, &shape, SHAFT_PRIMARY_UP, r + 60);
	processTriggerEvent(&state, &shape, SHAFT_PRIMARY_DOWN, r + 210);
	assertTrue(state.shaft_is_synchronized);
	assertEquals(0, state.current_index);
	processTriggerEvent(&state, &shape, SHAFT_PRIMARY_UP, r + 420);
	assertEquals(1, state.current_index);
	processTriggerEvent(&state, &shape, SHAFT_PRIMARY_DOWN, r + 630);
	assertEquals(2, state.current_index);

	printf("3rd\r\n");
	r = 2 * 720;
	processTriggerEvent(&state, &shape, SHAFT_PRIMARY_UP, r + 60);
	assertEquals(3, state.current_index);
	processTriggerEvent(&state, &shape, SHAFT_PRIMARY_DOWN, r + 210);
	assertTrue(state.shaft_is_synchronized);
	assertEquals(0, state.current_index);
	processTriggerEvent(&state, &shape, SHAFT_PRIMARY_UP, r + 420);
	processTriggerEvent(&state, &shape, SHAFT_PRIMARY_DOWN, r + 630);

}
