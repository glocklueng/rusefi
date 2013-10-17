/*
 * main.h
 *
 *  Created on: Nov 29, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */
#pragma once
#ifndef MAIN_H_
#define MAIN_H_

#include <ch.h>
#include <hal.h>
#include <time.h>

#include "features.h"

#include "global.h"
#include "stm32f4xx_specific.h"

#define CORE_CLOCK 168000000

#define ADC_DEBUG FALSE

// number of SysClock ticks in one ms
#define TICKS_IN_MS  (CH_FREQUENCY / 1000)
#define currentTimeMillis() (chTimeNow() / TICKS_IN_MS)

// number of SysClock ticks in one second
#define SECOND_AS_TICKS (1000 * TICKS_IN_MS)

#define GetCurrentTime() chTimeNow()
#define GetCurrentSec() (chTimeNow() / CH_FREQUENCY)

#define CHIBIOS TRUE

#define Delay(ms) chThdSleepMilliseconds(ms)

#endif /* MAIN_H_ */
