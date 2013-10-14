/*
 * tunerstudio.h
 *
 *  Created on: Aug 26, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef TUNERSTUDIO_H_
#define TUNERSTUDIO_H_

#include "fuel_map.h"

#define SIGNATURE "MShift v0.01"

#define TS_SERIAL_SPEED 115200
#define TS_SERIAL_DEVICE &SD3

#define TS_SERIAL_PORT GPIOD
#define TS_SERIAL_TX_PIN 8
#define TS_SERIAL_RX_PIN 9

typedef struct {
	float fuelTable[FUEL_MAF_COUNT][FUEL_RPM_COUNT];
	float fuelKeyBins[FUEL_MAF_COUNT];
	int fuelRpmBins[FUEL_RPM_COUNT];
} EngineConfiguration;

typedef struct {
	int rpm; // as is
	float coolant_temperature;
	float intake_air_temperature;
	float throttle_positon;
	float mass_air_flow;
	float air_fuel_ratio;
	float fuel_load;
} TunerStudioOutputChannels;

#if defined __GNUC__
typedef struct __attribute__((packed)) {
#else
typedef __packed struct {
#endif

short int offset;
unsigned char value;
} TunerStudioWriteRequest;

void startTunerStudioConnectivity(void);
void syncTunerStudioCopy(void);
void updateTunerStudioState(void);

#endif /* TUNERSTUDIO_H_ */
