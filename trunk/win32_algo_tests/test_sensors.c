/**
 * @file	test_sensors.c
 *
 * @date Dec 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "thermistors.h"
#include "map.h"

static ThermistorConf tc;

static void testMapDecoding() {
	assertEquals(-6.64, getMAPValueHonda_Denso183(0));
	assertEquals(31.244, getMAPValueHonda_Denso183(1));
}

void testSensors(void) {
	print("************************************************** testSensors\r\n");
	testMapDecoding();
	setThermistorConfiguration(&tc, 32, 9500, 75, 2100, 120, 1000);

	prepareThermistorCurve(&tc);

	assertEquals(-0.003, tc.s_h_a);
	assertEquals(0.001, tc.s_h_b);
	assertEquals(0.0, tc.s_h_c);

	float t = convertResistanceToKelvinTemperature(2100, &tc);
	assertEquals(75 + KELV, t);
}
