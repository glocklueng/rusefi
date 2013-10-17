/*
 * rpm_reporter.h
 *
 *  Created on: Jan 1, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    rpm_reporter.h
 * @brief   Shaft position sensor(s) decoder header
 */

#ifndef RPM_REPORTER_H_
#define RPM_REPORTER_H_

/**
 * @brief   Initialize position sensor decoder
 */
void initTachometer(void);
/**
 * @brief   Current RPM
 */
int getCurrentRpm(void);
int isRunning(void);

#endif /* RPM_REPORTER_H_ */
