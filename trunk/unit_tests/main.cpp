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
#include "error_handling.h"

extern "C"
{

#include "map_resize.h"
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
#include "engine_math.h"
}

#include "test_trigger_decoder.h"

static engine_configuration_s ec;
engine_configuration_s *engineConfiguration = &ec;

static float absF(float value) {
	return value > 0 ? value : -value;
}

uint64_t getTimeNowUs(void) {
	return 0;
}

void assertEqualsM(char *msg, float expected, float actual) {
	if (cisnan(actual) && !cisnan(expected)) {
		printf("Unexpected: %s %.4f while expected %.4f\r\n", msg, actual, expected);
		exit(-1);
	}

	float delta = absF(actual - expected);
	if (delta > 0.0001) {
		printf("delta: %.7f\r\n", delta);
		printf("Unexpected: %s %.4f while expected %.4f\r\n", msg, actual, expected);
		exit(-1);
	}
	printf("Validated %s: %f\r\n", msg, expected);
}

void assertEquals(float expected, float actual) {
	assertEqualsM("", expected, actual);
}

void assertTrueM(char *msg, float actual) {
	assertEqualsM(msg, TRUE, actual);
}

void assertTrue(float actual) {
	assertTrueM("", actual);
}

void assertFalseM(char *msg, float actual) {
	assertEqualsM(msg, FALSE, actual);
}

void assertFalse(float actual) {
	assertFalseM("", actual);
}

void chDbgAssert(int c, char *msg, void *arg) {
	if (!c) {
		printf("assert failed: %s\r\n", msg);
		exit(-1);
	}
}

static engine_configuration2_s ec2;
engine_configuration2_s *engineConfiguration2 = &ec2;

int main(void) {
	testOverflow64Counter();
	testInterpolate3d();
	testFindIndex();
	testInterpolate2d();
	testGpsParser();
	testFuelMap();
	testEngineMath();
	testEventRegistry();
	testSensors();
	testCyclicBuffer();

	testSignalExecutor();

	testHistogram();

	testTriggerDecoder();

	testMalfunctionCentral();

	testConsoleLogic();

	testAngleResolver();

	testPinHelper();
	testSetTableValue();

	printf("Success 20130418\r\n");

//	resizeMap();

	return EXIT_SUCCESS;
}


int warning(obd_code_e code, const char *fmt, ...) {
	printf("Warning: %s\r\n", fmt);
}

void firmwareError(const char *fmt, ...) {
	  printf(fmt);
	  exit(-1);
}

void print(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
}

void fatal3(char *msg, char *file, int line) {
  printf(msg);
  exit(-1);
}

int warning(const char *fmt, ...) {
	 printf(fmt);
	 exit(-1);
}
