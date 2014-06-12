/**
 * @file	tunerstudio.c
 * @brief Integration with EFI Analytics Tuner Studio software
 *
 * todo: merge this file with tunerstudio_algo.c?
 *
 * @date Aug 26, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 *
 * This file is part of rusEfi - see http://rusefi.com
 *
 * rusEfi is free software; you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * rusEfi is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "main.h"

#include "engine_state.h"
#include "tunerstudio.h"
#include "pin_repository.h"

#include "main_trigger_callback.h"
#include "flash_main.h"
#include "usbconsole.h"
#include "map_averaging.h"

#include "tunerstudio_algo.h"
#include "tunerstudio_configuration.h"
#include "malfunction_central.h"
#include "wave_math.h"
#include "console_io.h"

#if EFI_TUNER_STUDIO

#define TS_SERIAL_UART_DEVICE &SD3
#define TS_SERIAL_SPEED 115200

extern SerialUSBDriver SDU1;

BaseSequentialStream * getTsSerialDevice(void) {
	if (isSerialOverUart()) {
		// if console uses UART then TS uses USB
		return (BaseSequentialStream *) &SDU1;
	} else {
		return (BaseSequentialStream *) TS_SERIAL_UART_DEVICE;
	}
}

static Logging logger;

extern engine_configuration_s *engineConfiguration;
extern persistent_config_s configWorkingCopy;
extern persistent_config_container_s persistentState;

extern SerialUSBDriver SDU1;
#define CONSOLE_DEVICE &SDU1

static efitimems_t previousWriteReportMs = 0;

static int ts_serail_ready(void) {
	if (isSerialOverUart()) {
		// TS uses USB when console uses serial
		return is_usb_serial_ready();
	} else {
		// TS uses serial when console uses USB
		return TRUE;
	}
}

static SerialConfig tsSerialConfig = { TS_SERIAL_SPEED, 0, USART_CR2_STOP1_BITS | USART_CR2_LINEN, 0 };

static WORKING_AREA(TS_WORKING_AREA, UTILITY_THREAD_STACK_SIZE);

static int tsCounter = 0;
static int writeCounter = 0;

static short pageId;

static TunerStudioWriteRequest writeRequest;

extern TunerStudioOutputChannels tsOutputChannels;

extern TunerStudioState tsState;

static void printStats(void) {
	if (!isSerialOverUart()) {
		scheduleMsg(&logger, "TS RX on %s%d", portname(TS_SERIAL_RX_PORT), TS_SERIAL_RX_PIN);
		scheduleMsg(&logger, "TS TX on %s%d", portname(TS_SERIAL_TX_PORT), TS_SERIAL_TX_PIN);
	}
	scheduleMsg(&logger, "TunerStudio total/error counter=%d/%d", tsCounter, tsState.errorCounter);
	scheduleMsg(&logger, "TunerStudio H counter=%d", tsState.queryCommandCounter);
	scheduleMsg(&logger, "TunerStudio O counter=%d size=%d", tsState.outputChannelsCommandCounter,
			sizeof(tsOutputChannels));
	scheduleMsg(&logger, "TunerStudio C counter=%d", tsState.readPageCommandsCounter);
	scheduleMsg(&logger, "TunerStudio B counter=%d", tsState.burnCommandCounter);
	scheduleMsg(&logger, "TunerStudio W counter=%d", writeCounter);
	scheduleMsg(&logger, "page 0 size=%d", getTunerStudioPageSize(0));
	scheduleMsg(&logger, "page 1 size=%d", getTunerStudioPageSize(1));
}

void tunerStudioWriteData(const uint8_t * buffer, int size) {
	chSequentialStreamWrite(getTsSerialDevice(), buffer, size);
}

void tunerStudioDebug(char *msg) {
#if EFI_TUNER_STUDIO_VERBOSE
	scheduleMsg(&logger, "%s", msg);
	printStats();
#endif
}

char *getWorkingPageAddr(int pageIndex) {
	switch (pageIndex) {
	case 0:
		return (char*) &configWorkingCopy.engineConfiguration;
	case 1:
		return (char*) &configWorkingCopy.boardConfiguration;
	}
	return NULL;
}

int getTunerStudioPageSize(int pageIndex) {
	switch (pageIndex) {
	case 0:
		return sizeof(configWorkingCopy.engineConfiguration);
	case 1:
		return sizeof(configWorkingCopy.boardConfiguration);
	}
	return 0;

}

/**
 * 'Write' command receives a single value at a given offset
 */
void handleValueWriteCommand(void) {
	writeCounter++;

	//tunerStudioDebug("got W (Write)"); // we can get a lot of these

	int recieved = chSequentialStreamRead(getTsSerialDevice(), (uint8_t * )&pageId, 2);
	if (recieved != 2) {
		tsState.errorCounter++;
		return;
	}
#if EFI_TUNER_STUDIO_VERBOSE
//	scheduleMsg(&logger, "Page number %d\r\n", pageId); // we can get a lot of these
#endif

	int size = sizeof(TunerStudioWriteRequest);
//	scheduleMsg(&logger, "Reading %d\r\n", size);

	recieved = chSequentialStreamRead(getTsSerialDevice(), (uint8_t * )&writeRequest, size);
//	scheduleMsg(&logger, "got %d", recieved);

//	unsigned char offset = writeBuffer[0];
//	unsigned char value = writeBuffer[1];
//

	efitimems_t nowMs = currentTimeMillis();
	if (nowMs - previousWriteReportMs > 5) {
		previousWriteReportMs = nowMs;
//		scheduleMsg(&logger, "page %d offset %d: value=%d", pageId, writeRequest.offset, writeRequest.value);
	}

	getWorkingPageAddr(pageId)[writeRequest.offset] = writeRequest.value;

//	scheduleMsg(&logger, "va=%d", configWorkingCopy.boardConfiguration.idleValvePin);
}

void handlePageReadCommand(void) {
	tsState.readPageCommandsCounter++;
	tunerStudioDebug("got C (Constants)");
	int recieved = chSequentialStreamRead(getTsSerialDevice(), (uint8_t * )&pageId, 2);
	if (recieved != 2) {
		tsState.errorCounter++;
		return;
	}
#if EFI_TUNER_STUDIO_VERBOSE
	scheduleMsg(&logger, "Page number %d", pageId);
#endif

	tunerStudioWriteData((const uint8_t *) getWorkingPageAddr(pageId), getTunerStudioPageSize(pageId));
}

/**
 * 'Burn' command is a command to commit the changes
 */
void handleBurnCommand(void) {
	tsState.burnCommandCounter++;

	tunerStudioDebug("got B (Burn)");

	int recieved = chSequentialStreamRead(getTsSerialDevice(), (uint8_t * )&pageId, 2);
	if (recieved != 2) {
		tsState.errorCounter++;
		return;
	}
#if EFI_TUNER_STUDIO_VERBOSE
	scheduleMsg(&logger, "Page number %d\r\n", pageId);
#endif

	// todo: how about some multi-threading?
	memcpy(&persistentState.persistentConfiguration, &configWorkingCopy, sizeof(persistent_config_s));

	scheduleMsg(&logger, "va1=%d", configWorkingCopy.boardConfiguration.idleValvePin);
	scheduleMsg(&logger, "va2=%d", persistentState.persistentConfiguration.boardConfiguration.idleValvePin);

	writeToFlash();
	incrementGlobalConfigurationVersion();
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
//			scheduleSimpleMsg(&logger, "ts channel is now ready ", hTimeNow());
		}

		short command = (short) chSequentialStreamGet(getTsSerialDevice());
		int success = tunerStudioHandleCommand(command);
		if (!success && command != 0)
			print("got unexpected TunerStudio command %c:%d\r\n", command, command);

		tsCounter++;
	}
#if defined __GNUC__
	return 0;
#endif
}

void syncTunerStudioCopy(void) {
	memcpy(&configWorkingCopy, &persistentState.persistentConfiguration, sizeof(persistent_config_s));
}

void startTunerStudioConnectivity(void) {
	initLogging(&logger, "tuner studio");
	if (isSerialOverUart()) {
		print("TunerStudio over USB serial");
		usb_serial_start();
	} else {

		print("TunerStudio over USART");
		mySetPadMode("tunerstudio rx", TS_SERIAL_RX_PORT, TS_SERIAL_RX_PIN, PAL_MODE_ALTERNATE(TS_SERIAL_AF));
		mySetPadMode("tunerstudio tx", TS_SERIAL_TX_PORT, TS_SERIAL_TX_PIN, PAL_MODE_ALTERNATE(TS_SERIAL_AF));

		sdStart(TS_SERIAL_UART_DEVICE, &tsSerialConfig);
	}

	syncTunerStudioCopy();

	addConsoleAction("tsinfo", printStats);

	chThdCreateStatic(TS_WORKING_AREA, sizeof(TS_WORKING_AREA), NORMALPRIO, tsThreadEntryPoint, NULL);
}

#endif /* EFI_TUNER_STUDIO */
