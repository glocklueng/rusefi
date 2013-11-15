/*
 ============================================================================
 Name        : main.c
 Author      : Andrey Belomutskiy 
 Copyright   : (c) 2012-2013
 Description : First step towards unit-testing rusEfi algorithms on win32
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "main.h"

#include "test_idle_controller.h"
#include "test_interpolation_3d.h"
#include "test_find_index.h"
#include "test_fuel_map.h"
#include "test_engine_math.h"

static float absF(float value) {
	return value > 0 ? value : -value;
}

void assertEqualsM(char *msg, float expected, float actual) {
	if (isnan(actual) && !isnan(expected)) {
		printf("Unexpected: %s %.4f while expected %.4f\r\n", msg, actual,
				expected);
		exit(-1);
	}

	float delta = absF(actual - expected);
	if (delta > 0.0001) {
		printf("delta: %.7f\r\n", delta);
		printf("Unexpected: %s %.4f while expected %.4f\r\n", msg, actual,
				expected);
		exit(-1);
	}
	printf("Validated%s: %f\r\n", msg, expected);
}

void assertEquals(float expected, float actual) {
	assertEqualsM("", expected, actual);
}

void chDbgAssert(int c, char *msg, void *arg) {
	if (!c) {
		printf("assert failed: %s\r\n", msg);
		exit(-1);
	}
}

int main(void) {

	testInterpolate3d();
	testFindIndex();
	testInterpolate2d();
	testFuelMap();
	testEngineMath();

	printf("Success\r\n");
	return EXIT_SUCCESS;
}

