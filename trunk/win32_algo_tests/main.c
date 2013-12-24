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
#include <stdarg.h>

#include "main.h"

#include "test_idle_controller.h"
#include "test_interpolation_3d.h"
#include "test_find_index.h"
#include "test_fuel_map.h"
#include "test_engine_math.h"
#include "test_event_registry.h"
#include "test_sensors.h"
#include "test_signal_executor.h"
#include "test_util.h"
#include "engine_configuration.h"

static EngineConfiguration ec;
EngineConfiguration *engineConfiguration = &ec;

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

static EngineConfiguration2 ec2;
EngineConfiguration2 *engineConfiguration2 = &ec2;

int main(void) {

	testInterpolate3d();
	testFindIndex();
	testInterpolate2d();
	testFuelMap();
	testEngineMath();
	testEventRegistry();
	testSensors();
	testCyclicBuffer();

	testSignalExecutor();

	testHistogram();

	printf("Success\r\n");
	return EXIT_SUCCESS;
}

void warning(char *msg, float value) {
	printf("Warning: %s %f\r\n", msg, value);
}

void print(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
}

