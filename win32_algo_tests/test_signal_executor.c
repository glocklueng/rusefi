/**
 * @file	test_signal_executor.c
 *
 * @date Nov 28, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

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
}
