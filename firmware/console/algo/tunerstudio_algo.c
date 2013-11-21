/*
 * @file	tunerstudio_algo.c
 * @brief	Tuner Studio plain protocol implementation
 *
 *
 * Tuner Studio has a really simple protocol, a minimal implementation
 * capable of displaying current engine state on the gauges would
 * require only two commands: queryCommand and ochGetCommand
 *
 * queryCommand:
 * 		Communication initialization command. TunerStudio sends a single byte H
 * 		ECU response:
 * 			One of the known ECU id strings. We are using "MShift v0.01" id string.
 *
 * ochGetCommand:
 * 		Request for output channels state.TunerStudio sends a single byte O
 * 		ECU response:
 * 			A snapshot of output channels as described in [OutputChannels] section of the .ini file
 * 			The length of this block is 'ochBlockSize' property of the .ini file
 *
 * These two commands are enough to get working gauges. In order to start configuring the ECU using
 * tuner studio, three more commands should be implemented:
 *
 *
 *  Created on: Oct 22, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include <string.h>
#include "tunerstudio_algo.h"
#include "tunerstudio_configuration.h"
#include "engine_configuration.h"

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

TunerStudioState tsState;
TunerStudioOutputChannels tsOutputChannels;
/**
 * this is a local copy of the configuration. Any changes to this copy
 * have no effect until this copy is explicitly propagated to the main working copy
 */
EngineConfiguration tsContstants;

int tunerStudioHandleCommand(short command) {
	if (command == 'H') {
		handleQueryCommand();
	} else if (command == 'O') {
		handleOutputChannelsCommand();
	} else if (command == 'W') {
		handleValueWriteCommand();
	} else if (command == 'B') {
		handleBurnCommand();
	} else if (command == 'C') {
		handlePageReadCommand();
	} else if (command == 't' || command == 'T') {
		handleTestCommand();
	} else {
		tsState.errorCounter++;
		return FALSE;
	}
	return TRUE;
}

void handleQueryCommand(void) {
	tsState.queryCommandCounter++;
	tunerStudioDebug("got H (queryCommand)");
	tunerStudioWriteData(TS_SIGNATURE, strlen(TS_SIGNATURE) + 1);
}

/**
 * @brief 'Output' command sends out a snapshot of current values
 */
void handleOutputChannelsCommand(void) {
	tsState.outputChannelsCommandCounter++;
	// this method is invoked too often to print any debug information
	tunerStudioWriteData((const uint8_t *) &tsOutputChannels, sizeof(TunerStudioOutputChannels));
}

void handlePageReadCommand(void) {
	tsState.readPageCommandsCounter++;
	tunerStudioDebug("got C (Constants)");
	tunerStudioWriteData((const uint8_t *) &tsContstants, sizeof(EngineConfiguration));
}

void handleTestCommand(void) {
	/**
	 * this is NOT a standard TunerStudio command, this is my own
	 * extension of the protocol to simplify troubleshooting
	 */
	tunerStudioDebug("got T (Test)\r\n");
	tunerStudioWriteData("alive\r\n", 7);
}
