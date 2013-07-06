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

#include "global.h"
#include "stm32f4xx_specific.h"

#define CORE_CLOCK 168000000

#define RFI_POTEN TRUE

#define RE_CRANK_INPUT TRUE

//#define EFI_WAVE_ANALYZER TRUE
#define EFI_ADC TRUE

#define ADC_SNIFFER FALSE
#define ADC_DEBUG FALSE


#if RE_CRANK_INPUT
//#define CRANK_DRIVER ICUD4
//#define CRANK_INPUT_PORT GPIOB
//#define CRANK_INPUT_PIN 6
//GPIO_AF_TIM4

#define PRIMARY_CRANK_DRIVER ICUD2
#define PRIMARY_CRANK_INPUT_PORT GPIOA
#define PRIMARY_CRANK_INPUT_PIN 5

//#define CRANK_DRIVER ICUD9
//#define CRANK_INPUT_PORT GPIOE
//#define CRANK_INPUT_PIN 5

#define SECONDARY_CRANK_DRIVER ICUD3
#define SECONDARY_CRANK_INPUT_PORT GPIOC
#define SECONDARY_CRANK_INPUT_PIN 6

//#define CRANK_DRIVER ICUD4
//#define CRANK_INPUT_PORT GPIOB
//#define CRANK_INPUT_PIN 6
#endif

#define SPARK_1_PORT GPIOD
#define SPARK_1_PIN 3

#define INJECTOR_1_PORT GPIOB
#define INJECTOR_1_PIN 8

#define INJECTOR_2_PORT GPIOB
#define INJECTOR_2_PIN 9

#define INJECTOR_3_PORT GPIOE
#define INJECTOR_3_PIN 0

#define INJECTOR_4_PORT GPIOE
#define INJECTOR_4_PIN 1

#define IDLE_VALVE_PORT GPIOE
#define IDLE_VALVE_PIN 3

// number of SysClock ticks in one ms
#define TICKS_IN_MS  (CH_FREQUENCY / 1000)
#define currentTimeMillis() (chTimeNow() / TICKS_IN_MS)

#define GetSysclockCounter() chTimeNow()

// number of SysClock ticks in one second
#define SECOND_AS_TICKS (1000 * TICKS_IN_MS)

#define GetCurrentSec() (chTimeNow() / CH_FREQUENCY)

int aspireFilterCkp(int diff, int prevDiff);

#define CHIBIOS TRUE
#define NUMBER_OF_CYLINDERS 4

#endif /* MAIN_H_ */
