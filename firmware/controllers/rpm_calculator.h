/**
 * @file    rpm_calculator.h
 * @brief   Shaft position sensor(s) decoder header
 *
 *  Created on: Jan 1, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef RPM_REPORTER_H_
#define RPM_REPORTER_H_

/**
 * @brief   Initialize RPM calculator
 */
void initRpmCalculator(void);
/**
 * @brief   Current RPM
 */
int getCurrentRpm(void);
int isRunning(void);

#endif /* RPM_REPORTER_H_ */
