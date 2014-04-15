/**
 * @file    injector_central.h
 * @brief	Utility methods related to fuel injection.
 *
 *
 * @date Sep 8, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */


#ifndef INJECTOR_CENTRAL_H_
#define INJECTOR_CENTRAL_H_

#include "signal_executor.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

void initInjectorCentral(void);
int isInjectionEnabled(void);
int isInjectorEnabled(int cylinderId);
void assertCylinderId(int cylinderId, char *msg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INJECTOR_CENTRAL_H_ */
