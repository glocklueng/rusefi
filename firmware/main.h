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
#include "engine.h"

#include "ford_aspire.h"
#include "snow_blower.h"
#include "denisvak.h"

float getFuelMs(void);


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
 * @brief   Current system time in milliseconds.
 */
#define currentTimeMillis() (chTimeNow() / TICKS_IN_MS)

#define Delay(ms) chThdSleepMilliseconds(ms)

#endif /* MAIN_H_ */
