/**
 * @file    injector_central.h
 * @brief	Utility methods related to fuel injection.
 *
 *
 *  Created on: Sep 8, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */


#ifndef INJECTOR_CENTRAL_H_
#define INJECTOR_CENTRAL_H_

void initInjectorCentral(void);
int isInjectorEnabled(int cylinderId);
void assertCylinderId(int cylinderId, char *msg);
void scheduleFuelInjection(int offsetSysTicks, int lengthSysTicks, int cylinderId);

#endif /* INJECTOR_CENTRAL_H_ */
