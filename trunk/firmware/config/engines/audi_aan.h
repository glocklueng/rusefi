/**
 * @file	audi_aan.h
 * @brief	Audo AAN default engine configuration
 *
 * @date Nov 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef AUDI_AAN_H_
#define AUDI_AAN_H_

#if EFI_ENGINE_AUDI_AAN

#define EFI_ENGINE_ID "Audi AAN"

#define NUMBER_OF_CYLINDERS 4

#define SHAFT_POSITION_EVENT_COUNT 2

// this should be included after 'SHAFT_POSITION_EVENT_COUNT'. todo - fix this
#include "main_loop.h"

#define CLT_HI_RESISTOR 1500
#define IAT_HI_RESISTOR 2700

#define RPM_MULT 0.5

#define EFI_USE_MULTI_SENSOR_SHAFT_SENSOR TRUE

#endif /* EFI_ENGINE_AUDI_AAN */

#endif /* AUDI_AAN_H_ */
