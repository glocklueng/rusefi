/**
 * @file	ford_fiesta.h
 *
 * @date Nov 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef FORD_FIESTA_H_
#define FORD_FIESTA_H_
#if EFI_ENGINE_FORD_FIESTA

#include "pwm_generator.h"

#define TOTAL_TEETH_COUNT 36
#define SKIPPED_TEETH_COUNT 1
#define EFI_DEFAULT_CHART_SIZE 180

// this should be included after 'SHAFT_POSITION_EVENT_COUNT'. todo - fix this
#include "main_loop.h"

#define EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR TRUE

#define EFI_ENGINE_ID "Ford Fiesta"

#define NUMBER_OF_CYLINDERS 4

#endif /* EFI_ENGINE_FORD_FIESTA */
#endif /* FORD_FIESTA_H_ */
