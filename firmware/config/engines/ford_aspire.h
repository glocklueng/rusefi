/**
 * @file	ford_aspire.h
 * @brief	1996 Ford Aspire default engine configuration
 *
 * @date Aug 30, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 *
 *
 *	Injectors: Denso 195500-2110, 120cc, purple, 13.9 ohms
 *	camshaft position sensor(s): two Hall sensors
 *	single ignition coil(s), low-side driven with 5v pull-up resistor
 */

#ifndef FORD_ASPIRE_H_
#define FORD_ASPIRE_H_

#if EFI_ENGINE_FORD_ASPIRE

#include "global.h"
#include "thermistors.h"
#include "pwm_generator.h"

#define EFI_DEFAULT_CHART_SIZE 90

#include "main_loop.h"

#define EFI_ENGINE_ID "Ford Aspire"

#define NUMBER_OF_CYLINDERS 4

#define ENGINE_HAS_COOLANT_SENSOR TRUE
#define ENGINE_HAS_MAP_SENSOR TRUE

#define EFI_SHAFT_POSTION_NEEDS_SECONDARY TRUE

#endif /* EFI_ENGINE_FORD_ASPIRE */

#endif /* FORD_ASPIRE_H_ */
