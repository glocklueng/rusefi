/**
 * @file    flash_main.c
 * @brief	Higher-level logic of saving data into internal flash memory
 *
 *
 * @date Sep 19, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include <ch.h>
#include <hal.h>
#include <string.h>
#include "flash_main.h"
#include "rficonsole.h"
#include "flash.h"
#include "print.h"

#include "tunerstudio.h"
#include "engine_controller.h"

#include "datalogging.h"

static Logging logger;

#if defined __GNUC__
static FlashState flashState __attribute__((section(".ccm")));
#else
static FlashState flashState;
#endif

EngineConfiguration *engineConfiguration = &flashState.configuration;

#define FLASH_ADDR 0x08060000

#define FLASH_USAGE sizeof(FlashState)

void writeToFlash(void) {
	flashState.version = FLASH_DATA_VERSION;
	scheduleSimpleMsg(&logger, "FLASH_DATA_VERSION=", flashState.version);
	crc result = calc_crc((const crc*) &flashState.configuration, sizeof(EngineConfiguration));
	flashState.value = result;
	scheduleSimpleMsg(&logger, "Reseting flash=", FLASH_USAGE);
	flashErase(FLASH_ADDR, FLASH_USAGE);
	scheduleSimpleMsg(&logger, "Flashing with CRC=", result);
	result = flashWrite(FLASH_ADDR, (const char *) &flashState, FLASH_USAGE);
	scheduleSimpleMsg(&logger, "Flashed: ", result);
}

static int isValid(FlashState *state) {
	if (state->version != FLASH_DATA_VERSION) {
		scheduleSimpleMsg(&logger, "Not valid flash version: ", state->version);
		return FALSE;
	}
	crc result = calc_crc((const crc*) &state->configuration, sizeof(EngineConfiguration));
	if (result != state->value) {
		scheduleSimpleMsg(&logger, "CRC got: ", result);
		scheduleSimpleMsg(&logger, "CRC expected: ", state->value);
	}
	return result == state->value;
}

static void resetConfiguration(void) {
	/**
	 * Let's apply global defaults first
	 */
	setDefaultConfiguration(engineConfiguration);
	/**
	 * And override them with engine-specific defaults
	 */
	setDefaultEngineConfiguration(engineConfiguration);

#if EFI_TUNER_STUDIO
	syncTunerStudioCopy();
#endif
}

static void readFromFlash(void) {
	flashRead(FLASH_ADDR, (char *) &flashState, FLASH_USAGE);

	if (!isValid(&flashState)) {
		scheduleSimpleMsg(&logger, "Not valid flash state, setting default", 0);
		resetConfiguration();
		return;
	} else {
		scheduleSimpleMsg(&logger, "Got valid state from flash!", 0);
	}
}

static void doPrintConfiguration(void) {
	printConfiguration(engineConfiguration);
}

void initFlash(void) {
	initLogging(&logger, "Flash memory");
	print("initFlash()\r\n");

	addConsoleAction("showconfig", doPrintConfiguration);

	addConsoleAction("readconfig", readFromFlash);
	addConsoleAction("writeconfig", writeToFlash);
	addConsoleAction("resetconfig", resetConfiguration);

	readFromFlash();
}
