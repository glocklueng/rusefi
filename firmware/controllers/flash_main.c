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

static engine_type_e defaultEngineType = FORD_ASPIRE_1996;

static Logging logger;

#if defined __GNUC__
static FlashState flashState __attribute__((section(".ccm")));
#else
static FlashState flashState;
#endif

EngineConfiguration *engineConfiguration = &flashState.configuration;
extern EngineConfiguration2 * engineConfiguration2;

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
	time_t now = chTimeNow();
	result = flashWrite(FLASH_ADDR, (const char *) &flashState, FLASH_USAGE);
	scheduleSimpleMsg(&logger, "Flash programmed in (ms): ", chTimeNow() - now);
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

static void applyNonPersistentConfiguration(engine_type_e engineType) {
	switch (engineConfiguration->engineType) {
	case FORD_ASPIRE_1996:
		setFordAspireEngineConfiguration2(engineConfiguration2);
		break;
	case FORD_FIESTA:
		setFordFiestaEngineConfiguration2(engineConfiguration2);
		break;
	default:
		fatal("Unexpected engine type")
		;
	}

}

void resetConfiguration(engine_type_e engineType) {
	/**
	 * Let's apply global defaults first
	 */
	setDefaultConfiguration(engineConfiguration);
	engineConfiguration->engineType = engineType;
	/**
	 * And override them with engine-specific defaults
	 */
	switch (engineType) {
	case FORD_ASPIRE_1996:
		setFordAspireEngineConfiguration(engineConfiguration);
		break;
	case FORD_FIESTA:
		setFordFiestaDefaultEngineConfiguration(engineConfiguration);
		break;
	default:
		fatal("Unexpected engine type")
		;
	}
	applyNonPersistentConfiguration(engineType);

#if EFI_TUNER_STUDIO
	syncTunerStudioCopy();
#endif
}

static void readFromFlash(void) {

	flashRead(FLASH_ADDR, (char *) &flashState, FLASH_USAGE);
	setDefaultNonPersistentConfiguration(engineConfiguration2);

	if (!isValid(&flashState)) {
		scheduleSimpleMsg(&logger, "Not valid flash state, setting default", 0);
		resetConfiguration(defaultEngineType);
	} else {
		scheduleSimpleMsg(&logger, "Got valid state from flash!", 0);
		applyNonPersistentConfiguration(engineConfiguration->engineType);
	}
}

static void doPrintConfiguration(void) {
	printConfiguration(engineConfiguration, engineConfiguration2);
}

static void doResetConfiguration(void) {
	resetConfiguration(engineConfiguration->engineType);
}

void initFlash(void) {
	initLogging(&logger, "Flash memory");
	print("initFlash()\r\n");

	addConsoleAction("showconfig", doPrintConfiguration);

	addConsoleAction("readconfig", readFromFlash);
	addConsoleAction("writeconfig", writeToFlash);
	addConsoleAction("resetconfig", doResetConfiguration);

	readFromFlash();
}
