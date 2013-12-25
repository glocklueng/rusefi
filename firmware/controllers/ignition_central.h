/**
 * @file	ignition_central.h
 * @brief	TODO
 *
 * @date Nov 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef IGNITION_CENTRAL_H_
#define IGNITION_CENTRAL_H_

void initIgnitionCentral(void);
void scheduleSparkOut(int igniterId, int offsetSysTicks, int lengthSysTicks);

#endif /* IGNITION_CENTRAL_H_ */
