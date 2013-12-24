/*
 * @file	test_engine_math.c
 *
 *  Created on: Nov 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "test_engine_math.h"
#include "main.h"
#include "engine_math.h"
#include "engine_configuration.h"

extern EngineConfiguration2 *engineConfiguration2;

void testEngineMath(void) {
	printf("*************************************************** testEngineMath\r\n");

	engineConfiguration2->rpmMultiplier = 0.5;

	assertEqualsM("600 RPM", 5000, convertAngleToSysticks(600, 90));
	assertEqualsM("6000 RPM", 499, convertAngleToSysticks(6000, 90));
}
