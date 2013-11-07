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


	initFuelMap();
	assertEquals(11, getBaseFuel(1398, 2.15));

}
