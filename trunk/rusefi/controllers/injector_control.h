/*
 * injector_control.h
 *
 *  Created on: Dec 30, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef INJECTOR_CONTROL_H_
#define INJECTOR_CONTROL_H_

void initInjectorsControl();
void pokeControl();
int getInjectionPeriod();
int getCrankingInjectionPeriod();
int getInjectionOffset();
int getInjectionDivider();

#endif /* INJECTOR_CONTROL_H_ */
