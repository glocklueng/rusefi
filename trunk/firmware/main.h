/**
 * @file	main.h
 *
 * @date Nov 29, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */
#pragma once
#ifndef MAIN_H_
#define MAIN_H_

#include <math.h>
#include "rficonsole.h"
#include "rficonsole_logic.h"

#include "global.h"
#include "features.h"
#include "engines.h"

#include "datalogging.h"

#include "stm32f4xx_specific.h"

// todo: access some existing configuration field
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

void warning(char *msg, float value);
void updateHD44780lcd(void);
int hasFatalError(void);
void fatal3(char *msg, char *file, int line);
#define fatal(x) (fatal3(x, __FILE__, __LINE__));
int systicks2ms(int systicks);

void lockAnyContext(void);
void unlockAnyContext(void);


#endif /* MAIN_H_ */
