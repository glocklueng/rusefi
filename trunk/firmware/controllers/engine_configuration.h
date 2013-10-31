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
	float injectorLag;	// size 4, offset 0
	float injectorFlow; // size 4, offset 4
	float battInjectorLagCorrBins[8]; // size 32, offset 8
	float battInjectorLagCorr[8]; // size 32, offset 40
	float cltFuelCorrBins[16]; // size 64, offset 72
	float cltFuelCorr[16]; // size 64, offset 136
	float iatFuelCorrBins[16]; // size 64, offset 200
	float iatFuelCorr[16]; // size 64
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
