/*
 * test_fuel_map.c
 *
 *  Created on: Nov 6, 2013
 *      Author: pc
 */

#include "main.h"
#include "engine_configuration.h"

static EngineConfiguration ec;

EngineConfiguration *engineConfiguration = &ec;

void testFuelMap(void) {
	printf("*************************************************** testFuelMap\r\n");

	setDefaultFuelMap();
	initFuelMap();
	assertEquals(2.9334, getBaseFuel(1398, 2.15));
}
