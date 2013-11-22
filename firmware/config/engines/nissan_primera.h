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

#define SKIPPED_TEETH_COUNT 2

#define SHAFT_POSITION_EVENT_COUNT ((TOTAL_TEETH_COUNT - SKIPPED_TEETH_COUNT) * 2)

#include "main_loop.h"


#define EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR TRUE

#define RPM_MULT (1)

#define EFI_ENGINE_ID "DenisVak"

#define NUMBER_OF_CYLINDERS 4

void configureShaftPositionEmulatorShape(PwmConfig *state);

void configureEngineEventHandler(EventHandlerConfiguration *config);

#define CLT_HI_RESISTOR 1500
// todo: this value is way off! I am pretty sure temp coeffs are off also
#define IAT_HI_RESISTOR 2700

#endif /* EFI_ENGINE_DENISVAK */

#endif /* DENISVAK_H_ */
