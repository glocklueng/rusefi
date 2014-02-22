/**
 * @file    flash_main.c
 * @brief	Higher-level logic of saving data into internal flash memory
 *
 *
 * @date Sep 19, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include <ch.h>
#include <hal.h>
#include <string.h>
#include "flash_main.h"
#include "eficonsole.h"
#include "flash.h"
#include "rusefi.h"

#include "tunerstudio.h"
#include "engine_controller.h"

#include "datalogging.h"

#include "audi_aan.h"
#include "dodge_neon.h"
#include "ford_aspire.h"
#include "ford_fiesta.h"
#include "ford_1995_inline_6.h"
#include "snow_blower.h"
#include "nissan_primera.h"
#include "honda_accord.h"
#include "GY6_139QMB.h"

static engine_type_e defaultEngineType = FORD_ASPIRE_1996;

static Logging logger;

#if defined __GNUC__
static FlashState flashState __attribute__((section(".ccm")));
#else
static FlashState flashState;
#endif

engine_configuration_s *engineConfiguration = &flashState.configuration;
extern engine_configuration2_s * engineConfiguration2;

#define FLASH_ADDR 0x08060000

#define FLASH_USAGE sizeof(FlashState)

void writeToFlash(void) {
	flashState.version = FLASH_DATA_VERSION;
	scheduleSimpleMsg(&logger, "FLASH_DATA_VERSION=", flashState.version);
	crc result = calc_crc((const crc*) &flashState.configuration, sizeof(engine_configuration_s));
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
		scheduleSimpleMsg(&logger, "Unexpected flash version: ", state->version);
		return FALSE;
	}
	crc result = calc_crc((const crc*) &state->configuration, sizeof(engine_configuration_s));
	if (result != state->value) {
		scheduleSimpleMsg(&logger, "CRC got: ", result);
		scheduleSimpleMsg(&logger, "CRC expected: ", state->value);
	}
	return result == state->value;
}

void resetConfiguration(engine_type_e engineType) {
	resetConfigurationExt(engineType, engineConfiguration, engineConfiguration2);

#if EFI_TUNER_STUDIO
	syncTunerStudioCopy();
#endif
}

static void readFromFlash(void) {

	flashRead(FLASH_ADDR, (char *) &flashState, FLASH_USAGE);
	engineConfiguration->firmwareVersion = getVersion();

	setDefaultNonPersistentConfiguration(engineConfiguration2);

	if (!isValid(&flashState)) {
		scheduleSimpleMsg(&logger, "Not valid flash state, setting default", 0);
		resetConfiguration(defaultEngineType);
	} else {
		scheduleSimpleMsg(&logger, "Got valid state from flash!", 0);
		applyNonPersistentConfiguration(engineConfiguration, engineConfiguration2, engineConfiguration->engineType);
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
