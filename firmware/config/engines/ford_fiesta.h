/*
 * @file	ford_fiesta.h
 *
 *  Created on: Nov 22, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef FORD_FIESTA_H_
#define FORD_FIESTA_H_
#if EFI_ENGINE_FORD_FIESTA

#include "pwm_generator.h"

#define TOTAL_TEETH_COUNT 36
#define SKIPPED_TEETH_COUNT 1
#define SHAFT_POSITION_EVENT_COUNT ((TOTAL_TEETH_COUNT - SKIPPED_TEETH_COUNT) * 2)

#define EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR TRUE

#define RPM_MULT (1)

#define EFI_ENGINE_ID "Ford Fiesta"

#define NUMBER_OF_CYLINDERS 4

#define ENGINE_CRANKING_RPM 400

void confgiureShaftPositionEmulatorShape(PwmConfig *state);

#endif /* EFI_ENGINE_FORD_FIESTA */
#endif /* FORD_FIESTA_H_ */
