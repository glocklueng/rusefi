/*
 * engine_configuration.h
 *
 *  Created on: Oct 30, 2013
 *      Author: Andrey
 */

#ifndef ENGINE_CONFIGURATION_H_
#define ENGINE_CONFIGURATION_H_

#include "fuel_map.h"

/**
 *
 */
typedef struct {
	float injectorLag;
	int injBattCorrBins[8];
	float injBattCorr[8];
	float fuelTable[FUEL_MAF_COUNT][FUEL_RPM_COUNT];
	float fuelKeyBins[FUEL_MAF_COUNT];
	int fuelRpmBins[FUEL_RPM_COUNT];
} EngineConfiguration;

/**
 * this part of the structure is separate just because so far
 * these fields are not integrated with Tuner Studio. Step by step :)
 */
typedef struct {
	float injectionLag;
	float tps_idle;
	float tps_wot;
} EngineConfiguration2;


#endif /* ENGINE_CONFIGURATION_H_ */
