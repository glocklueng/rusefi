/*
 * tunerstudio.c
 *
 *  Created on: Aug 26, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include <ch.h>
#include <hal.h>
#include <string.h>

#include "tunerstudio.h"
#include "pin_repository.h"

#include "rpm_reporter.h"
#include "main_loop.h"
#include "engine.h"
#include "flash_main.h"
#include "rficonsole_logic.h"

extern EngineConfiguration *engineConfiguration;

extern SerialUSBDriver SDU1;
#define CONSOLE_DEVICE &SDU1

static SerialConfig tsSerialConfig = { TS_SERIAL_SPEED, 0, USART_CR2_STOP1_BITS | USART_CR2_LINEN, 0 };

static WORKING_AREA(TS_WORKING_AREA, 512);

static int tsCounter = 0;
static int helloCounter = 0;
static int channelsCounter = 0;
static int constantsCounter = 0;
static int burnCounter = 0;
static int writeCounter = 0;
static int errorCounter = 0;

static TunerStudioWriteRequest writeRequest;

static TunerStudioOutputChannels tsOutputChannels;
#if defined __GNUC__
static EngineConfiguration tsContstants __attribute__((section(".bss2")));
#else
static EngineConfiguration tsContstants;
#endif

char *constantsAsPtr = (char *)&tsContstants;

static void printStats() {
	print("TS RX on %s%d\r\n", portname(TS_SERIAL_PORT), TS_SERIAL_RX_PIN);
	print("TS TX on %s%d\r\n", portname(TS_SERIAL_PORT), TS_SERIAL_TX_PIN);
	print("TunerStudio total/error counter=%d/%d\r\n", tsCounter, errorCounter);
	print("TunerStudio H counter=%d\r\n", helloCounter);
	print("TunerStudio O counter=%d size=%d\r\n", channelsCounter, sizeof(tsOutputChannels));
	print("TunerStudio C counter=%d size=%d\r\n", constantsCounter, sizeof(tsContstants));
	print("TunerStudio B counter=%d size=%d\r\n", burnCounter, sizeof(tsContstants));
	print("TunerStudio W counter=%d\r\n", writeCounter);
}

static void handleHelloCommand(void) {
#if EFI_TUNER_STUDIO_VERBOSE
	print("got H (Hello)\r\n");
	printStats();
#endif
	chSequentialStreamWrite(TS_SERIAL_DEVICE, SIGNATURE, strlen(SIGNATURE) + 1);
}

/**
 * @brief 'Output' command sends out a snapshot of current values
 */
static void handleOutputChannelsCommand(void) {
//  this happends too often	to log it
//	chprintf(CONSOLE_DEVICE, "got O (OutputChannels)\r\n");
	chSequentialStreamWrite(TS_SERIAL_DEVICE, (const uint8_t *)&tsOutputChannels, sizeof(tsOutputChannels));
}


/**
 * 'Write' command recieves a single value at a given offset
 */
static void handleWriteCommand(void) {
#if EFI_TUNER_STUDIO_VERBOSE
	print("got W (Write)\r\n");
	printStats();
#endif

	int size = sizeof(TunerStudioWriteRequest);
	print("Reading %d\r\n", size);

	int recieved = chSequentialStreamRead(TS_SERIAL_DEVICE, (uint8_t *)&writeRequest, size);
	print("got %d\r\n", recieved);

//	unsigned char offset = writeBuffer[0];
//	unsigned char value = writeBuffer[1];
//
	print("offset %d: value=%d\r\n", writeRequest.offset, writeRequest.value);
	constantsAsPtr[writeRequest.offset] = writeRequest.value;
}

/**
 * 'Burn' command is a command to commit the changes
 */
static void handleBurnCommand(void) {

#if EFI_TUNER_STUDIO_VERBOSE
	print("got B (Burn)\r\n");
	printStats();
#endif
	// todo: how about some multi-threading?
	memcpy(engineConfiguration, &tsContstants, sizeof(EngineConfiguration));
	writeToFlash();
}

static void handleConstantsCommand(void) {
#if EFI_TUNER_STUDIO_VERBOSE
	print("got C (Constants)\r\n");
	printStats();
#endif
	chSequentialStreamWrite(TS_SERIAL_DEVICE, (const uint8_t *)&tsContstants, sizeof(EngineConfiguration));
}

static void handleTSCommand(short code) {
	if (code == 'H') {
		helloCounter++;
		handleHelloCommand();
	} else if (code == 'O') {
		channelsCounter++;
		handleOutputChannelsCommand();
	} else if (code == 'W') {
		writeCounter++;
		handleWriteCommand();
	} else if (code == 'B') {
		burnCounter++;
		handleBurnCommand();
	} else if (code == 'C') {
		constantsCounter++;
		handleConstantsCommand();
	} else if (code == 't' || code == 'T') {
		print("got T (Test)\r\n");
		chSequentialStreamWrite(TS_SERIAL_DEVICE, "alive\r\n", 7);
	} else {
		errorCounter++;
		print("got unexpected command %c:%d\r\n", code, code);
	}
}

static msg_t tsThreadEntryPoint(void *arg) {
	(void) arg;
	chRegSetThreadName("tunerstudio thread");

	while (true) {
		short code = (short) chSequentialStreamGet(TS_SERIAL_DEVICE);
		handleTSCommand(code);
		tsCounter++;
	}
	return 0;
}

extern EngineConfiguration *engineConfiguration;

void syncTunerStudioCopy(void) {
	memcpy(&tsContstants, engineConfiguration, sizeof(EngineConfiguration));
}

void startTunerStudioConnectivity(void) {
	mySetPadMode("tunerstudio rx", TS_SERIAL_PORT, TS_SERIAL_RX_PIN, PAL_MODE_ALTERNATE(7));
	mySetPadMode("tunerstudio tx", TS_SERIAL_PORT, TS_SERIAL_TX_PIN, PAL_MODE_ALTERNATE(7));

	sdStart(TS_SERIAL_DEVICE, &tsSerialConfig);

	syncTunerStudioCopy();

	addConsoleAction("tss", printStats);

	chThdCreateStatic(TS_WORKING_AREA, sizeof(TS_WORKING_AREA), NORMALPRIO, tsThreadEntryPoint, NULL);
}

void updateTunerStudioState() {
	tsOutputChannels.rpm = getCurrentRpm();
	tsOutputChannels.coolant_temperature = getCoolantTemperature();
	tsOutputChannels.intake_air_temperature = getIntakeAirTemperature();
	tsOutputChannels.throttle_positon = getTPS();
	tsOutputChannels.mass_air_flow = getMaf();
	tsOutputChannels.air_fuel_ratio = getAfr();
}
