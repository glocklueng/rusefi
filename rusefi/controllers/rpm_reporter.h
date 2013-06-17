/*
 * rpm_reporter.h
 *
 *  Created on: Jan 1, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef RPM_REPORTER_H_
#define RPM_REPORTER_H_

int getCurrentRpm(void);
void initAspireTachometer(void);
void reportRpmValue(void);
void pokeRpmStatus(void);
void onFilteredEvent(int ckpEventType);

#endif /* RPM_REPORTER_H_ */
