/**
 * @file	test_sensors.c
 *
 * @date Dec 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "thermistors.h"

static ThermistorConf tc;

void testSensors(void) {

	tc.resistance_1 = 9500;
	tc.temp_1 = 32;

	tc.resistance_2 = 2100;
	tc.temp_2 = 75;

	tc.resistance_3 = 1000;
	tc.temp_3 = 120;

	prepareThermistorCurve(&tc);

	assertEquals(-0.003, tc.s_h_a);
	assertEquals(0.001, tc.s_h_b);
	assertEquals(0.0, tc.s_h_c);
}
