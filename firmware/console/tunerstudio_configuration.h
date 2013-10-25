/*
 * @file	tunerstudio_configuration.h
 * @brief	Tuner Studio connectivity configuration
 *
 * In this file the configuration of TunerStudio is defined
 *
 *  Created on: Oct 22, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef TUNERSTUDIO_CONFIGURATION_H_
#define TUNERSTUDIO_CONFIGURATION_H_

#include "fuel_map.h"

/**
 * please be aware that current "stable" version of TunerStudio does not
 * support 'float' (F32) type. You would need a beta version to handle floats
 */
typedef struct {
	int rpm;
	float coolant_temperature;
	float intake_air_temperature;
	float throttle_positon;
	float mass_air_flow;
	float air_fuel_ratio;
	float fuel_load;
} TunerStudioOutputChannels;

// todo: this structure definition should be moved somewhere else
typedef struct {
	float fuelTable[FUEL_MAF_COUNT][FUEL_RPM_COUNT];
	float fuelKeyBins[FUEL_MAF_COUNT];
	int fuelRpmBins[FUEL_RPM_COUNT];
} EngineConfiguration;

#endif /* TUNERSTUDIO_CONFIGURATION_H_ */
