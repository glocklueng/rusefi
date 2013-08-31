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

static SerialConfig tsSerialConfig = { TS_SERIAL_SPEED, 0, USART_CR2_STOP1_BITS | USART_CR2_LINEN, 0 };

static WORKING_AREA(TS_WORKING_AREA, 512);

extern SerialUSBDriver SDU1;
#define CONSOLE_DEVICE &SDU1

TunerStudioOutputChannels tsOutputChannels;
// values from this array are not used yet
static char constants[128];

static void handleHelloCommand() {
//	chprintf(CONSOLE_DEVICE, "got H (Hello)\r\n");
	chSequentialStreamWrite(TS_SERIAL_DEVICE, SIGNATURE, strlen(SIGNATURE) + 1);
}

static void handleOutputChannelsCommand() {
//  this happends too often	to log it
//	chprintf(CONSOLE_DEVICE, "got O (OutputChannels)\r\n");
	chSequentialStreamWrite(TS_SERIAL_DEVICE, &tsOutputChannels, sizeof(tsOutputChannels));
}

static void handleConstantsCommand() {
//	chprintf(CONSOLE_DEVICE, "got C (Constants)\r\n");
	chSequentialStreamWrite(TS_SERIAL_DEVICE, constants, 128);
}

static void handleTSCommand(short code) {
	if (code == 'H') {
		handleHelloCommand();
	} else if (code == 'O') {
		handleOutputChannelsCommand();
	} else if (code == 'C') {
		handleConstantsCommand();
	} else {
//		chprintf(CONSOLE_DEVICE, "got unexpected command %c:%d\r\n", code, code);
	}
}

static msg_t tsThreadEntryPoint(void *arg) {
	(void) arg;
	chRegSetThreadName("tunerstudio thread");

	while (true) {
		short code = (short) chSequentialStreamGet(TS_SERIAL_DEVICE);
		handleTSCommand(code);
	}
	return 0;
}

void startTunerStudioConnectivity(void) {
	palSetPadMode(TS_SERIAL_PORT, TS_SERIAL_RX_PIN, PAL_MODE_ALTERNATE(7));
	palSetPadMode(TS_SERIAL_PORT, TS_SERIAL_TX_PIN, PAL_MODE_ALTERNATE(7));

	sdStart(TS_SERIAL_DEVICE, &tsSerialConfig);

	chThdCreateStatic(TS_WORKING_AREA, sizeof(TS_WORKING_AREA), NORMALPRIO, tsThreadEntryPoint, NULL);
}
