/*
 *  Created on: Oct 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    denisvak.h
 *
 * 		This file should only be included from engine.h
 */

#include "features.h"
#include "pwm_generator.h"

#ifndef DENISVAK_H_
#define DENISVAK_H_

#if EFI_ENGINE_DENISVAK

#define SHAFT_POSITION_EVENT_COUNT (58 * 2)

#include "main_loop.h"

#define TOTAL_TEETH_COUNT 60

#define EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR TRUE

#define RPM_MULT (1)

#define EFI_ENGINE_ID "DenisVak"

#define ENGINE_CRANKING_RPM 400

#define NUMBER_OF_CYLINDERS 4

#define getCoolantTemperature() 0
#define getIntakeAirTemperature() 0

#define getMaf() 0
#define getTPS() 0
#define getAfr() 0

void confgiureShaftPositionEmulatorShape(PwmConfig *state);

#define PRIMARY_SHAFT_POSITION_INPUT_DRIVER ICUD4
#define PRIMARY_SHAFT_POSITION_INPUT_PORT GPIOB
#define PRIMARY_SHAFT_POSITION_INPUT_PIN 7
#define PRIMARY_SHAFT_POSITION_INPUT_CHANNEL ICU_CHANNEL_2

#define INJECTOR_1_PORT GPIOD
#define INJECTOR_1_PIN 3

#define INJECTOR_2_PORT GPIOD
#define INJECTOR_2_PIN 0

#define INJECTOR_3_PORT GPIOD
#define INJECTOR_3_PIN 2

#define INJECTOR_4_PORT GPIOD
#define INJECTOR_4_PIN 1

#if EFI_EMULATE_POSITION_SENSORS
#define PRIMARY_SHAFT_POSITION_EMULATION_PIN 4
#define PRIMARY_SHAFT_POSITION_EMULATION_PORT GPIOD
#endif /* EFI_EMULATE_POSITION_SENSORS */

#define SPARK_1_PORT GPIOD
#define SPARK_1_PIN 7

void configureInjection(InjectionConfiguration *injectionConfiguration);

#endif /* EFI_ENGINE_DENISVAK */

#endif /* DENISVAK_H_ */
