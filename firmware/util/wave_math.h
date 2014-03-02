/*
 * wave_math.h
 *
 * @date Dec 25, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef WAVE_MATH_H_
#define WAVE_MATH_H_

#include "global.h"

// number of ticks in one period of given frequency (per second)
#define frequency2period(freq) (((float)CH_FREQUENCY) / (freq))

float floatmod(float value, float divider);
int waveState(time_t start, time_t now, float waveLen, float leftSide,
		float rightSide);

// todo: implement a function to work with times considering counter overflow
#define overflowDiff(now, time) ((now) - (time))

#endif /* WAVE_MATH_H_ */
