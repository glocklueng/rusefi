/*
 *  Created on: Sep 19, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    flash_main.c
 */

#include <ch.h>
#include <hal.h>
#include <string.h>
#include "flash_main.h"
#include "rficonsole.h"
#include "flash.h"

#include "datalogging.h"

static Logging log;

static FlashState flashState __attribute__((section(".bss2")));
//static FlashState fs_write;

EngineConfiguration *engineConfiguration = &flashState.configuration;

#define FLASH_ADDR 0x08060000

#define FLASH_USAGE sizeof(FlashState)

void writeToFlash(void) {
	flashState.version = FLASH_DATA_VERSION;
	scheduleSimpleMsg(&log, "FLASH_DATA_VERSION=", flashState.version);
	crc result = calc_crc(&flashState.configuration, sizeof(EngineConfiguration));
	flashState.value = result;
	scheduleSimpleMsg(&log, "Reseting flash=", FLASH_USAGE);
	flashErase(FLASH_ADDR, FLASH_USAGE);
	scheduleSimpleMsg(&log, "Flashing with CRC=", result);
	result = flashWrite(FLASH_ADDR, (const char *) &flashState, FLASH_USAGE);
	scheduleSimpleMsg(&log, "Flashed: ", result);
}

static void printConfiguration() {
	for (int i = 0; i < FUEL_RPM_COUNT; i++) {
		print("line %d: ", i);
		for (int j = 0; j < FUEL_RPM_COUNT; j++) {
			print("%d ", engineConfiguration->fuelTable[i][j]);
		}
		print("\r\n");
	}

	print("RPM bin: ");
	for (int j = 0; j < FUEL_RPM_COUNT; j++) {
		print("%d ", engineConfiguration->fuelRpmBins[j]);
	}
	print("\r\n");
}

static int isValid(FlashState *state) {
	if (state->version != FLASH_DATA_VERSION) {
		scheduleSimpleMsg(&log, "Not valid flash version: ", state->version);
		return FALSE;
	}
	crc result = calc_crc(&state->configuration, sizeof(EngineConfiguration));
	if (result != state->value) {
		scheduleSimpleMsg(&log, "CRC got: ", result);
		scheduleSimpleMsg(&log, "CRC expected: ", state->value);
	}
	return result == state->value;
}

extern float fuel_rpm_bins[];

static void setDefaultConfiguration() {
	for (int i = 0; i < FUEL_MAF_COUNT; i++)
		engineConfiguration->mapBins[i] = i;
	for (int i = 0; i < FUEL_RPM_COUNT; i++)
		engineConfiguration->fuelRpmBins[i] = 5 * i;//fuel_rpm_bins[i];
	for (int i = 0; i < FUEL_MAF_COUNT; i++) {
		for (int j = 0; j < FUEL_RPM_COUNT; j++) {
			engineConfiguration->fuelTable[i][j] = j;
		}
	}
}

static void readFromFlash() {
	flashRead(FLASH_ADDR, (char *) &flashState, FLASH_USAGE);

	if (!isValid(&flashState)) {
		scheduleSimpleMsg(&log, "Not valid flash state, setting default", 0);
		setDefaultConfiguration();
		return;
	} else {
		scheduleSimpleMsg(&log, "Got valid state from flash!", 0);
	}
}

void initFlash(void) {
	initLogging(&log, "Idle Valve Control", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));
	print("initFlash()\r\n");

	addConsoleAction("showconfig", printConfiguration);

	addConsoleAction("readconfig", readFromFlash);
	addConsoleAction("writeconfig", writeToFlash);

	readFromFlash();
}
