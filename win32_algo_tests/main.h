/**
 * @file	main.h
 * @brief	Test version of main.h
 *
 *  Created on: Oct 17, 2013
 *      Author: Andrey Belomutskiy (C) 2012-2013
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <math.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "efilib.h"

#include "global.h"
#include "boards.h"
#include "engines.h"

typedef int bool_t;

void fatal(char* x);
void chDbgAssert(int c, char *msg, void *arg);

void print(const char *fmt, ...);

#define TICKS_IN_MS 100

#define DEBUG_INTERPOLATION 1

#define chDbgCheck(x, y) chDbgAssert(x, y, NULL)

void assertEqualsM(char *msg, float expected, float actual);
void assertEquals(float expected, float actual);
void assertTrue(float actual);
void assertTrueM(char *msg, float actual);
void assertFalse(float actual);
void assertFalseM(char *msg, float actual);

float getIntakeAirTemperature(void);
float getCoolantTemperature(void);
float getVBatt(void);
float getMaf(void);

#define systicks2ms(x) (0)

void warning(char *msg, float value);

#ifdef __cplusplus
}
#endif


#endif /* MAIN_H_ */
