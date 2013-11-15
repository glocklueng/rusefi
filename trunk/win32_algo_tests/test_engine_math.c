/*
 * @file	test_engine_math.c
 *
 *  Created on: Nov 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "test_engine_math.h"
#include "main.h"
#include "engine_math.h"

void testEngineMath(void) {
	assertEqualsM("@600", 5000, convertAngleToSysticks(600, 90));
	assertEqualsM("@6000", 500, convertAngleToSysticks(6000, 90));
}
