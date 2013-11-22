/*
 * engine_configuration.h
 *
 *  Created on: Oct 30, 2013
 *      Author: Andrey
 */

#ifndef ENGINE_CONFIGURATION_H_
#define ENGINE_CONFIGURATION_H_

#include "fuel_map.h"

#define CLT_CURVE_SIZE 16
#define IAT_CURVE_SIZE 16
#define VBAT_INJECTOR_CURVE_SIZE 8

/**
 *
 */
typedef struct {
	float injectorLag;	// size 4, offset 0
	float injectorFlow; // size 4, offset 4
	float battInjectorLagCorrBins[VBAT_INJECTOR_CURVE_SIZE]; // size 32, offset 8
	float battInjectorLagCorr[VBAT_INJECTOR_CURVE_SIZE]; // size 32, offset 40

	float cltFuelCorrBins[CLT_CURVE_SIZE]; // size 64, offset 72
	float cltFuelCorr[CLT_CURVE_SIZE]; // size 64, offset 136

	float iatFuelCorrBins[IAT_CURVE_SIZE]; // size 64, offset 200
	float iatFuelCorr[IAT_CURVE_SIZE]; // size 64, offset 264

	short int rpmHardLimit; // size 2, offset 328

	short int tpsMin; // size 2, offset 330
	short int tpsMax; // size 2, offset 332
	short int fake;   // size 2, offset 334       for alignment

	float fuelTable[FUEL_MAF_COUNT][FUEL_RPM_COUNT]; // size 3036, offset 336
	float fuelKeyBins[FUEL_MAF_COUNT]; // offset 3372
	float fuelRpmBins[FUEL_RPM_COUNT]; // offset 3504

} EngineConfiguration;

/**
 * this part of the structure is separate just because so far
 * these fields are not integrated with Tuner Studio. Step by step :)
 */
typedef struct {
  int unused;
} EngineConfiguration2;


#endif /* ENGINE_CONFIGURATION_H_ */
