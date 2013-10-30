/*
 * engine_configuration.h
 *
 *  Created on: Oct 30, 2013
 *      Author: Andrey
 */

#ifndef ENGINE_CONFIGURATION_H_
#define ENGINE_CONFIGURATION_H_

#include "fuel_map.h"

typedef struct {
	float fuelTable[FUEL_MAF_COUNT][FUEL_RPM_COUNT];
	float fuelKeyBins[FUEL_MAF_COUNT];
	int fuelRpmBins[FUEL_RPM_COUNT];
} EngineConfiguration;


#endif /* ENGINE_CONFIGURATION_H_ */
