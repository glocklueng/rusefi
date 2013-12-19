/**
 * @file	histogram.c
 *
 * @date Dec 18, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "histogram.h"

#define H_ACCURACY 0.05
#define H_CONFIDENCE 0.8
#define BOUND_LENGTH 895
#define LONG_MAX_INT 0x7fffffffffffffffL
#define SBI_SIZE 1000

static int64_t bounds[BOUND_LENGTH];
static int small_bounds_index[1000];

void initHistograms(void) {
	bounds[0] = 0;
	for (int i = 1; i < BOUND_LENGTH; i++) {
		int64_t prev = bounds[i - 1];
		int64_t next = prev + (int64_t) ((double) prev * H_ACCURACY);
		if (next == prev) // Ensure minimum step for small numbers.
			next = prev + 1;
		if (next < prev) // Overflow over Long.MAX_VALUE occurred.
			next = LONG_MAX_INT;
		bounds[i] = next;
	}
	bounds[BOUND_LENGTH - 1] = LONG_MAX_INT;

	for (int i = 0, j = 0; j < SBI_SIZE; i++)
		while (j < bounds[i + 1] && j < SBI_SIZE)
			small_bounds_index[j++] = i;
}

int histogramGetIndex(int64_t value) {
	if (value < 0)
		return 0;
	if (value < SBI_SIZE)
		return small_bounds_index[(int) value];
	int l = small_bounds_index[SBI_SIZE - 1];
	int r = BOUND_LENGTH - 1;
	while (l < r) {
		int m = (l + r) >> 1;
		if (bounds[m] > value)
			r = m - 1;
		else if (bounds[m + 1] <= value)
			l = m + 1;
		else
			return m;
	}
	return l;
}

