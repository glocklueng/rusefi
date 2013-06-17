/*
 * wave_math.h
 *
 *  Created on: Dec 25, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef WAVE_MATH_H_
#define WAVE_MATH_H_

#include "time.h"
#include "global.h"

// number of ticks in one period of given frequency (per second)
#define freq2wave(freq) (((myfloat)FREQ_MATH_FREQUENCY) / (freq))

myfloat floatmod(myfloat value, myfloat divider);
int waveState(time_t start, time_t now, myfloat waveLen, myfloat leftSide,
		myfloat rightSide);

// todo: implement a function to work with times considering counter overflow
#define overflowDiff(now, time) ((now) - (time))

#endif /* WAVE_MATH_H_ */
