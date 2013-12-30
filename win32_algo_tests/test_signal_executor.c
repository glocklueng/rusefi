/**
 * @file	test_signal_executor.c
 *
 * @date Nov 28, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include <time.h>
#include "main.h"

#include "signal_executor.h"
#include "signal_executor_single_timer_algo.h"
#include "test_signal_executor.h"
#include "io_pins.h"
#include "utlist.h"

extern OutputSignal *st_output_list;

static io_pin_e testLastToggledPin;
static int testToggleCounter;

void setOutputPinValue(io_pin_e pin, int value) {
	// this is a test implementation of the method - we use it to see what's going on
	testLastToggledPin = pin;
	testToggleCounter++;
}


void testSignalExecutor() {
	print("*************************************** testSignalExecutor\r\n");

	OutputSignal s1;
	OutputSignal s2;

	registerSignal(&s1);
	registerSignal(&s2);

	OutputSignal *out;
	int count;
	LL_COUNT(st_output_list, out, count);
	assertEquals(2, count);

	s1.io_pin = 0;
	initOutputSignalBase(&s1);
	scheduleOutputBase(&s1, 10, 100);

	long now = 1;
	testToggleCounter = 0;
	assertEquals(99, toggleSignalIfNeeded(&s1, now));
	assertEquals(0, testToggleCounter);

	now = 100;
	testToggleCounter = 0;
	assertEquals(10, toggleSignalIfNeeded(&s1, now));
	assertEquals(1, testToggleCounter);

	now = 300; // let's see what happens if the handler is late
	testToggleCounter = 0;
	assertEquals(100, toggleSignalIfNeeded(&s1, now));
	assertEquals(1, testToggleCounter);
}
