/*
 * advance.h
 *
 * @date Mar 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ADVANCE_H_
#define ADVANCE_H_

#define AD_LOAD_COUNT 16
#define AD_RPM_COUNT 16

float getAdvance(int rpm, float engineLoad);
void prepareTimingMap(void);

#endif /* ADVANCE_H_ */
