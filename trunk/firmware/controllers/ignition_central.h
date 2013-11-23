/**
 * @file	ignition_central.h
 * @brirf	TODO
 *
 *  Created on: Nov 15, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef IGNITION_CENTRAL_H_
#define IGNITION_CENTRAL_H_

void initIgnitionCentral(void);
void scheduleSparkOut(int igniterId, int offsetSysTicks, int lengthSysTicks);

#endif /* IGNITION_CENTRAL_H_ */
