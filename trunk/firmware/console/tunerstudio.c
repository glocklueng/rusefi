/**
 * @file	tunerstudio.c
 * @brief
 *
 * @date Aug 26, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include <string.h>
#include "main.h"

#include "allsensors.h"
#include "tunerstudio.h"
#include "pin_repository.h"

#include "rpm_calculator.h"
#include "main_loop.h"
#include "flash_main.h"
#include "rficonsole_logic.h"
#include "usbconsole.h"
#include "map_averaging.h"

#include "tunerstudio_algo.h"
#include "tunerstudio_configuration.h"

#if EFI_TUNER_STUDIO

static Logging logger;

extern EngineConfiguration *engineConfiguration;

extern SerialUSBDriver SDU1;
#define CONSOLE_DEVICE &SDU1

#if EFI_TUNER_STUDIO_OVER_USB
#define ts_serail_ready() is_usb_serial_ready()
#else
#define ts_serail_ready() TRUE
static SerialConfig tsSerialConfig = {TS_SERIAL_SPEED, 0, USART_CR2_STOP1_BITS | USART_CR2_LINEN, 0};
#endif /* EFI_TUNER_STUDIO_OVER_USB */

static WORKING_AREA(TS_WORKING_AREA, 512);

static int tsCounter = 0;
static int writeCounter = 0;

static TunerStudioWriteRequest writeRequest;

extern TunerStudioOutputChannels tsOutputChannels;

extern EngineConfiguration tsContstants;

char *constantsAsPtr = (char *) &tsContstants;

extern TunerStudioState tsState;

static void printStats(void) {
#if EFI_TUNER_STUDIO_OVER_USB
#else
	print("TS RX on %s%d\r\n", portname(TS_SERIAL_PORT), TS_SERIAL_RX_PIN);
	print("TS TX on %s%d\r\n", portname(TS_SERIAL_PORT), TS_SERIAL_TX_PIN);
#endif /* EFI_TUNER_STUDIO_OVER_USB */
	print("TunerStudio total/error counter=%d/%d\r\n", tsCounter, tsState.errorCounter);
	print("TunerStudio H counter=%d\r\n", tsState.queryCommandCounter);
	print("TunerStudio O counter=%d size=%d\r\n", tsState.outputChannelsCommandCounter, sizeof(tsOutputChannels));
	print("TunerStudio C counter=%d size=%d\r\n", tsState.readPageCommandsCounter, sizeof(tsContstants));
	print("TunerStudio B counter=%d size=%d\r\n", tsState.burnCommandCounter, sizeof(tsContstants));
	print("TunerStudio W counter=%d\r\n", writeCounter);
}

void tunerStudioWriteData(const uint8_t * buffer, int size) {
	chSequentialStreamWrite(TS_SERIAL_DEVICE, buffer, size);
}

void tunerStudioDebug(char *msg) {
#if EFI_TUNER_STUDIO_VERBOSE
	print("%s\r\n", msg);
	printStats();
#endif
}

/**
 * 'Write' command receives a single value at a given offset
 */
void handleValueWriteCommand(void) {
	writeCounter++;

	tunerStudioDebug("got W (Write)");

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
void handleBurnCommand(void) {
	tsState.burnCommandCounter++;

	tunerStudioDebug("got B (Burn)");

	// todo: how about some multi-threading?
	memcpy(engineConfiguration, &tsContstants, sizeof(EngineConfiguration));
	writeToFlash();
}

static msg_t tsThreadEntryPoint(void *arg) {
	(void) arg;
	chRegSetThreadName("tunerstudio thread");

	int wasReady = FALSE;
	while (true) {
		int isReady = ts_serail_ready();
		if (!isReady) {
			chThdSleepMilliseconds(10);
			wasReady = FALSE;
			continue;
		}
		if (!wasReady) {
			wasReady = TRUE;
//			scheduleSimpleMsg(&logger, "ts channel is now ready ", chTimeNow());
		}

		short command = (short) chSequentialStreamGet(TS_SERIAL_DEVICE);
		int success = tunerStudioHandleCommand(command);
		if (!success)
			print("got unexpected command %c:%d\r\n", command, command);

		tsCounter++;
	}
	return 0;
}

extern EngineConfiguration *engineConfiguration;

void syncTunerStudioCopy(void) {
	memcpy(&tsContstants, engineConfiguration, sizeof(EngineConfiguration));
}

void startTunerStudioConnectivity(void) {
	initLogging(&logger, "tuner studio");
#if EFI_TUNER_STUDIO_OVER_USB
	print("TunerStudio over USB serial");
	usb_serial_start();
#else
	print("TunerStudio over USART");
	mySetPadMode("tunerstudio rx", TS_SERIAL_PORT, TS_SERIAL_RX_PIN, PAL_MODE_ALTERNATE(7));
	mySetPadMode("tunerstudio tx", TS_SERIAL_PORT, TS_SERIAL_TX_PIN, PAL_MODE_ALTERNATE(7));

	sdStart(TS_SERIAL_DEVICE, &tsSerialConfig);
#endif

	syncTunerStudioCopy();

	addConsoleAction("tss", printStats);

	chThdCreateStatic(TS_WORKING_AREA, sizeof(TS_WORKING_AREA), NORMALPRIO, tsThreadEntryPoint, NULL );
}

void updateTunerStudioState() {
	tsOutputChannels.rpm = getCurrentRpm();
	tsOutputChannels.coolant_temperature = getCoolantTemperature();
	tsOutputChannels.intake_air_temperature = getIntakeAirTemperature();
	tsOutputChannels.throttle_positon = getTPS();
	tsOutputChannels.mass_air_flow = getMaf();
	tsOutputChannels.air_fuel_ratio = getAfr();
	tsOutputChannels.v_batt = getVBatt();
	tsOutputChannels.tpsADC= getTPSAdc();
	tsOutputChannels.atmospherePressure = getAtmosphericPressure();
}

#endif /* EFI_TUNER_STUDIO */
