/*
 *  Created on: Sep 8, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    injector_central.h
 */

#ifndef INJECTOR_CENTRAL_H_
#define INJECTOR_CENTRAL_H_

void initInjectorCentral(void);
int isInjectorEnabled(int cylinderId);
void assertCylinderId(int cylinderId, char *msg);

#endif /* INJECTOR_CENTRAL_H_ */
