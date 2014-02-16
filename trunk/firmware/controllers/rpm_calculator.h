/**
 * @file    rpm_calculator.h
 * @brief   Shaft position sensor(s) decoder header
 *
 * @date Jan 1, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef RPM_REPORTER_H_
#define RPM_REPORTER_H_

#include <time.h>

typedef struct {
	volatile int rpm;
	volatile time_t lastRpmEventTime;
	/**
	 * This counter is incremented with each revolution of one of the shafts. Could be
	 * crankshaft could be camshaft.
	 */
	volatile int revolutionCounter;
} rpm_s;

/**
 * @brief   Initialize RPM calculator
 */
void initRpmCalculator(void);
/**
 * @brief   Current RPM
 */
int getRpm(void);
int getRevolutionCounter(void);
float getCrankshaftAngle(time_t time);
int isRunning(void);

#endif /* RPM_REPORTER_H_ */
