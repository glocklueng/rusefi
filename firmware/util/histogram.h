/**
 * @file	histogram.h
 *
 * @date Dec 18, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include <stdint.h>

void initHistograms(void);
int histogramGetIndex(int64_t value);

#endif /* HISTOGRAM_H_ */
