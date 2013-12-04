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
#include "utlist.h"

extern OutputSignal *st_output_list;

void testSignalExecutor() {
	OutputSignal s1;
	OutputSignal s2;

	registerSignal(&s1);
	registerSignal(&s2);

	OutputSignal *out;
	int count;
	LL_COUNT(st_output_list, out, count);
	assertEquals(2, count);

	initOutputSignalBase(&s1);
	scheduleOutputBase(&s1, 10, 100);

	long now = 1;
	assertEquals(99, toggleSignalIfNeeded(&s1, now));
	now = 100;
	assertEquals(10, toggleSignalIfNeeded(&s1, now));

	now = 300; // let's see what happends if the handler is late
	//assertEquals(10, toggleSignalIfNeeded(&s1, now));
}
