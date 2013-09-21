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

#define TS_FLOAT_MULT 100

typedef struct {
	char fuelTable[FUEL_MAF_COUNT][FUEL_RPM_COUNT];
	char mapBins[FUEL_MAF_COUNT];
	char fuelRpmBins[FUEL_RPM_COUNT];
} EngineConfiguration;

typedef struct {
	int rpm; // as is
	int coolant_temperature; // packed float
	int intake_air_temperature; // packed float
	int throttle_positon; // packed float
	int mass_air_flow; // packed float
	int air_fuel_ratio; // packed float
	int fuel_load; // packed float
} TunerStudioOutputChannels;

typedef struct __attribute__((packed)) {
	short int offset;
	unsigned char value;
} TunerStudioWriteRequest;

void startTunerStudioConnectivity(void);
void updateTunerStudioState(void);

#endif /* TUNERSTUDIO_H_ */
