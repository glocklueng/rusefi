/*
 * @file	signal_executor_single_timer_algo.c
 *
 * @date Nov 28, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "signal_executor.h"
#include "utlist.h"

/**
 * @brief Output list
 *
 * List of all active output signals
 * This is actually the head of the list.
 * When the list is empty (initial state) the head of the list should be NULL.
 * This is by design.
 */
OutputSignal *st_output_list = NULL;

void registerSignal(OutputSignal *signal) {
	LL_APPEND(st_output_list, signal);
}

