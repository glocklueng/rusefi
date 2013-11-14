/*
 * @file	main.h
 * @brief	Test version of main.h
 *
 *  Created on: Oct 17, 2013
 *      Author: Andrey Belomutskiy (C) 2012-2013
 */

#ifndef MAIN_H_
#define MAIN_H_

typedef float myfloat;

#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define fatal(x) printf(x)

#define DEBUG_INTERPOLATION 1

void chDbgAssert(int c, char *msg, void *arg);

void assertEquals(float expected, float actual);

float getIntakeAirTemperature();
float getCoolantTemperature();
float getVBatt();


#endif /* MAIN_H_ */
