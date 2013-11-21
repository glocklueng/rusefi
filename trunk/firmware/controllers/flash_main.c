/*
 * @file    flash_main.c
 * @brief	Higher-level logic of saving data into internal flash memory
 *
 *
 *  Created on: Sep 19, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include <ch.h>
#include <hal.h>
#include <string.h>
#include "flash_main.h"
#include "rficonsole.h"
#include "flash.h"
#include "print.h"

#include "tunerstudio.h"

#include "datalogging.h"

static Logging logger;

#if defined __GNUC__
static FlashState flashState __attribute__((section(".bss2")));
#else
static FlashState flashState;
#endif

EngineConfiguration *engineConfiguration = &flashState.configuration;

#define FLASH_ADDR 0x08060000

#define FLASH_USAGE sizeof(FlashState)

void writeToFlash(void) {
	flashState.version = FLASH_DATA_VERSION;
	scheduleSimpleMsg(&logger, "FLASH_DATA_VERSION=", flashState.version);
	crc result = calc_crc((const crc*) &flashState.configuration,
			sizeof(EngineConfiguration));
	flashState.value = result;
	scheduleSimpleMsg(&logger, "Reseting flash=", FLASH_USAGE);
	flashErase(FLASH_ADDR, FLASH_USAGE);
	scheduleSimpleMsg(&logger, "Flashing with CRC=", result);
	result = flashWrite(FLASH_ADDR, (const char *) &flashState, FLASH_USAGE);
	scheduleSimpleMsg(&logger, "Flashed: ", result);
}

static void printIntArray(int array[], int size) {
	for (int j = 0; j < size; j++)
		print("%d ", array[j]);
	print("\r\n");
}

static void printFloatArray(char *prefix, float array[], int size) {
	print(prefix);
	for (int j = 0; j < size; j++)
		print("%f ", array[j]);
	print("\r\n");
}

static void printConfiguration(void) {
	for (int k = 0; k < FUEL_MAF_COUNT; k++) {
		print("line %d (%f): ", k, engineConfiguration->fuelKeyBins[k]);
		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
			print("%f ", engineConfiguration->fuelTable[k][r]);
		}
		print("\r\n");
	}

	printFloatArray("RPM bin: ", engineConfiguration->fuelRpmBins, FUEL_RPM_COUNT);

	printFloatArray("Y bin: ", engineConfiguration->fuelKeyBins, FUEL_MAF_COUNT);

	printFloatArray("CLT: ", engineConfiguration->cltFuelCorr, CLT_CURVE_SIZE);
	printFloatArray("CLT bins: ", engineConfiguration->cltFuelCorrBins, CLT_CURVE_SIZE);

	printFloatArray("IAT: ", engineConfiguration->iatFuelCorr, IAT_CURVE_SIZE);
	printFloatArray("IAT bins: ", engineConfiguration->iatFuelCorrBins, IAT_CURVE_SIZE);

	printFloatArray("vBatt: ", engineConfiguration->battInjectorLagCorr, VBAT_INJECTOR_CURVE_SIZE);
	printFloatArray("vBatt bins: ", engineConfiguration->battInjectorLagCorrBins, VBAT_INJECTOR_CURVE_SIZE);

}

static int isValid(FlashState *state) {
	if (state->version != FLASH_DATA_VERSION) {
		scheduleSimpleMsg(&logger, "Not valid flash version: ", state->version);
		return FALSE;
	}
	crc result = calc_crc((const crc*) &state->configuration,
			sizeof(EngineConfiguration));
	if (result != state->value) {
		scheduleSimpleMsg(&logger, "CRC got: ", result);
		scheduleSimpleMsg(&logger, "CRC expected: ", state->value);
	}
	return result == state->value;
}

static void setDefaultConfiguration(void) {
	engineConfiguration->injectorLag = 0.5;

	for (int i = 0; i < IAT_CURVE_SIZE; i++) {
		engineConfiguration->iatFuelCorrBins[i] = -40 + i * 10;
		engineConfiguration->iatFuelCorr[i] = 1;
	}

	for (int i = 0; i < CLT_CURVE_SIZE; i++) {
		engineConfiguration->cltFuelCorrBins[i] = -40 + i * 10;
		engineConfiguration->cltFuelCorr[i] = 1;
	}

	for (int i = 0; i < VBAT_INJECTOR_CURVE_SIZE; i++) {
		engineConfiguration->battInjectorLagCorrBins[i] = 12 - VBAT_INJECTOR_CURVE_SIZE / 2 + i;
		engineConfiguration->battInjectorLagCorr[i] = 1;
	}
	engineConfiguration->tpsMin = 0;
	engineConfiguration->tpsMax = 1023;
	setDefaultFuelMap();

#if EFI_TUNER_STUDIO
	syncTunerStudioCopy();
#endif
}

static void readFromFlash(void) {
	flashRead(FLASH_ADDR, (char *) &flashState, FLASH_USAGE);

	if (!isValid(&flashState)) {
		scheduleSimpleMsg(&logger, "Not valid flash state, setting default", 0);
		setDefaultConfiguration();
		return;
	} else {
		scheduleSimpleMsg(&logger, "Got valid state from flash!", 0);
	}
}

void initFlash(void) {
	initLogging(&logger, "Flash memory", logger.DEFAULT_BUFFER,
			sizeof(logger.DEFAULT_BUFFER));
	print("initFlash()\r\n");

	addConsoleAction("showconfig", printConfiguration);

	addConsoleAction("readconfig", readFromFlash);
	addConsoleAction("writeconfig", writeToFlash);
	addConsoleAction("resetconfig", setDefaultConfiguration);

	readFromFlash();
}
