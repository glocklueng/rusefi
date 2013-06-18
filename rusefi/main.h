/*
 * main.h
 *
 *  Created on: Nov 29, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <ch.h>
#include <hal.h>
#include <time.h>

#include "global.h"
#include "stm32f4xx_specific.h"

#define CORE_CLOCK 168000000

#define RE_CRANK_INPUT TRUE

#define EFI_WAVE TRUE
#define EFI_ADC TRUE

//#define WAVE_ANALYZER TRUE

#define ADC_SNIFFER FALSE
#define ADC_DEBUG FALSE


#if RE_CRANK_INPUT
//#define CRANK_DRIVER ICUD4
//#define CRANK_INPUT_PORT GPIOB
//#define CRANK_INPUT_PIN 6
//GPIO_AF_TIM4

#define CRANK_DRIVER ICUD2
#define CRANK_INPUT_PORT GPIOA
#define CRANK_INPUT_PIN 5
#define CRANK_AF GPIO_AF_TIM2

//#define CRANK_DRIVER ICUD3
//#define CRANK_INPUT_PORT GPIOC
//#define CRANK_INPUT_PIN 6
//#define CRANK_AF GPIO_AF_TIM3

//#define CRANK_DRIVER ICUD4
//#define CRANK_INPUT_PORT GPIOB
//#define CRANK_INPUT_PIN 6
//#define CRANK_AF GPIO_AF_TIM4

#endif

#define INJECTOR_1_PORT GPIOC
#define INJECTOR_1_PIN 11

#define IDLE_VALVE_PORT GPIOE
#define IDLE_VALVE_PIN 5


#define TICKS_IN_MS  (CH_FREQUENCY / 1000)
#define currentTimeMillis() (chTimeNow() / TICKS_IN_MS)

#define GetSysclockCounter() chTimeNow()

// number of SysClock ticks in one ms
#define MS_DIVIDER (CH_FREQUENCY / 1000)
// number of SysClock ticks in one second
#define SECOND_AS_TICKS (1000 * MS_DIVIDER)

#define GetCurrentSec() (chTimeNow() / CH_FREQUENCY)

int aspireFilterCkp(int diff, int prevDiff);

#define CHIBIOS TRUE

#endif /* MAIN_H_ */
