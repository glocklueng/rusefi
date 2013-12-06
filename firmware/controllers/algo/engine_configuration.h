/**
 * @file	engine_configuration.h
 * @brief	Main engine configuration data structure.
 *
 * @date Oct 30, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_CONFIGURATION_H_
#define ENGINE_CONFIGURATION_H_

#include "fuel_map.h"
#include "thermistors.h"

#define CLT_CURVE_SIZE 16
#define IAT_CURVE_SIZE 16
#define VBAT_INJECTOR_CURVE_SIZE 8

/**
 * @brief	Engine configuration.
 * 		Values in this data structure are adjustable and persisted in on-board flash RAM.
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
	short int crankingRpm;   // size 2, offset 334

	ThermistorConf cltThermistorConf; // size 40 (10*4), offset 336
	ThermistorConf iatThermistorConf; // size 40, offset 376

	float fuelTable[FUEL_MAF_COUNT][FUEL_RPM_COUNT]; // size 3036, offset 414
	float fuelKeyBins[FUEL_MAF_COUNT]; // offset 3450
	float fuelRpmBins[FUEL_RPM_COUNT]; // offset 3542

} EngineConfiguration;

/**
 * this part of the structure is separate just because so far
 * these fields are not integrated with Tuner Studio. Step by step :)
 */
typedef struct {
	float ignitonOffset;
	Thermistor iat;
	Thermistor clt;
} EngineConfiguration2;

void setDefaultConfiguration(EngineConfiguration *engineConfiguration);
void printConfiguration(EngineConfiguration *engineConfiguration);

#endif /* ENGINE_CONFIGURATION_H_ */
