/**
 * @file	histogram.h
 *
 * @date Dec 18, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include <stdint.h>

#define BOUND_LENGTH 895

typedef struct {
	int64_t total_value;
	int64_t total_count;
	int values[BOUND_LENGTH];
} histogram_s;

void initHistograms(void);
int histogramGetIndex(int64_t value);
void resetHistogram(histogram_s *h);

#endif /* HISTOGRAM_H_ */
