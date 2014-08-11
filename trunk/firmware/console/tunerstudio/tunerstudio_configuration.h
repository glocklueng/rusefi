/*
 * @file	tunerstudio_configuration.h
 * @brief	Tuner Studio connectivity configuration
 *
 * In this file the configuration of TunerStudio is defined
 *
 * @date Oct 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef TUNERSTUDIO_CONFIGURATION_H_
#define TUNERSTUDIO_CONFIGURATION_H_

/**
 * please be aware that current "stable" version of TunerStudio does not
 * support 'float' (F32) type. You would need a beta version to handle floats
 */
typedef struct {
	// primary instrument cluster gauges
	int rpm; // size 4, offset 0
	float coolant_temperature; // size 4, offset 4
	float intake_air_temperature; // size 4, offset 8
	float throttle_positon; // size 4, offset 12
	float mass_air_flow; // size 4, offset 16
	float air_fuel_ratio; // size 4, offset 20
	float fuel_load; // size 4, offset 24
	float v_batt; // size 4, offset 28
	short int tpsADC; // size 2, offset 32
	short int alignment; // size 2, offset 34
	float atmospherePressure; // size 4, offset 36
	float manifold_air_pressure; // size 4, offset 40
	int checkEngine; // size 4, offset 44 todo: reduce bits usage? MAYBE
	int needBurn; // 48
	float tCharge; // 52
	float inj_adv; // 56
	float sparkDwell; // 60
	float pulseWidth; // 64
	float warmUpEnrich;	// 68
} TunerStudioOutputChannels;

#endif /* TUNERSTUDIO_CONFIGURATION_H_ */
