/*
 * wave_math.c
 *
 * @date Dec 25, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "wave_math.h"

//#define LOOPS_TIME(value, divider) (((int)((value) / (divider))) * (divider))

myfloat floatmod(myfloat value, myfloat divider) {
	// number of full cycles
	int loopsNumber = value / divider;
	// total time of full cycles
	myfloat loopsTime = loopsNumber * divider;

	return value - loopsTime;
}

/**
 * @param waveLen length of each wave, in ticks
 */
int waveState(time_t start, time_t now, myfloat waveLen, myfloat leftSide,
		myfloat rightSide) {
	/**
	 * number of ticks since start of thread
	 */
	myfloat time = now - start;
	myfloat mod = floatmod(time, waveLen);
	return mod >= waveLen * leftSide && mod < waveLen * rightSide;
}
