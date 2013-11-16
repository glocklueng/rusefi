/*
 * main.h
 *
 *  Created on: Nov 29, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */
#pragma once
#ifndef MAIN_H_
#define MAIN_H_

#include <time.h>

#include "global.h"
#include "features.h"
#include "engines.h"

#include "ford_aspire.h"
#include "snow_blower.h"
#include "denisvak.h"

#include "datalogging.h"

float getFuelMs(int rpm);

void warning(char *msg, float value);

#include "stm32f4xx_specific.h"

#define CORE_CLOCK 168000000

/**
 * number of SysClock ticks in one ms
 */
#define TICKS_IN_MS  (CH_FREQUENCY / 1000)

/**
 * @brief   Current system time in seconds.
 */
#define chTimeNowSeconds() (chTimeNow() / CH_FREQUENCY)

/**
 * @brief   Returns the number of milliseconds since the board initialization.
 */
#define currentTimeMillis() (chTimeNow() / TICKS_IN_MS)

#define Delay(ms) chThdSleepMilliseconds(ms)

void fatal3(char *msg, char *file, int line);
#define fatal(x) (fatal3(x, __FILE__, __LINE__));

#endif /* MAIN_H_ */
