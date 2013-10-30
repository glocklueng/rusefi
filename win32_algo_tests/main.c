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

#include "main.h"

#include "test_idle_controller.h"
#include "test_interpolation_3d.h"
#include "test_find_index.h"

static float absF(float value) {
	return value > 0 ? value : -value;
}

void assertEqualsM(char *msg, float expected, float actual) {
	float delta = absF(actual - expected);
	if (delta > 0.0001) {
		printf("delta: %.7f\r\n", delta);
		printf("Unexpected: %s %.4f while expected %.4f\r\n", msg, actual, expected);
		exit(-1);
	}
	printf("Validated%s: %f\r\n", msg, expected);
}

void assertEquals(float expected, float actual) {
	assertEqualsM("", expected, actual);
}

int main(void) {

	testInterpolate3d();
	testFindIndex();

	printf("Success\r\n");
	return EXIT_SUCCESS;
}

