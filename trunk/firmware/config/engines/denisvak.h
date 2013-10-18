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

#define INJECTOR_1_PORT GPIOB
#define INJECTOR_1_PIN 8

#define INJECTOR_2_PORT GPIOB
#define INJECTOR_2_PIN 9

#define INJECTOR_3_PORT GPIOE
#define INJECTOR_3_PIN 1

#define INJECTOR_4_PORT GPIOE
#define INJECTOR_4_PIN 0

#endif /* EFI_ENGINE_DENISVAK */

#endif /* DENISVAK_H_ */
