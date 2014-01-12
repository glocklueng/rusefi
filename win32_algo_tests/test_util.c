/**
 * @file	test_util.c
 *
 * @date Dec 8, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include <stdlib.h>
#include <string.h>

#include "test_util.h"
#include "cyclic_buffer.h"
#include "main.h"
#include "histogram.h"

#include "malfunction_central.h"
#include "rficonsole_logic.h"

static cyclic_buffer sb;

void testCyclicBuffer(void) {
	print("*************************************** testCyclicBuffer\r\n");

	cbInit(&sb);
	cbAdd(&sb, 10);

	assertEquals(10, cbSum(&sb, 3));

	cbAdd(&sb, 2);
	assertEquals(12, cbSum(&sb, 2));
}

void testHistogram(void) {
	print("******************************************* testHistogram\r\n");

	initHistograms();

	assertEquals(80, histogramGetIndex(239));
	assertEquals(223, histogramGetIndex(239239));
	assertEquals(364, histogramGetIndex(239239239));

	histogram_s h;

	resetHistogram(&h, "test");

	int result[5];
	assertEquals(0, hsReport(&h, result));

	hsAdd(&h, 10);
	assertEquals(1, hsReport(&h, result));
	assertEquals(10, result[0]);

	// let's add same value one more time
	hsAdd(&h, 10);
	assertEquals(2, hsReport(&h, result));
	assertEquals(10, result[0]);
	assertEquals(10, result[1]);

	hsAdd(&h, 10);
	hsAdd(&h, 10);
	hsAdd(&h, 10);

	hsAdd(&h, 1000);
	hsAdd(&h, 100);

	assertEquals(5, hsReport(&h, result));

	assertEquals(5, result[0]);
	assertEquals(10, result[1]);
	assertEquals(10, result[2]);
	assertEquals(100, result[3]);
	// values are not expected to be exactly the same, it's the shape what matters
	assertEquals(1011, result[4]);
}

void testMalfunctionCentral(void) {
	print("******************************************* testMalfunctionCentral\r\n");
	initMalfunctionCentral();

	error_codes_set_s localCopy;

	// on start-up error storage should be empty
	getErrorCodes(&localCopy);
	assertEquals(0, localCopy.count);

	obd_code_e code = OBD_Engine_Coolant_Temperature_Circuit_Malfunction;

	// this should not crash
	removeError(code);

	// let's add one error and validate
	addError(code);
	getErrorCodes(&localCopy);
	assertEquals(1, localCopy.count);
	assertEquals(code, localCopy.error_codes[0]);

	// let's add same error one more time
	print("adding same code again\r\n");
	addError(code);
	getErrorCodes(&localCopy);
	// same code should be only present in the set once
	assertEquals(1, localCopy.count);

	code = OBD_Intake_Air_Temperature_Circuit_Malfunction;
	addError(code);
	getErrorCodes(&localCopy);
	// todo:	assertEquals(2, localCopy.count);

	for (int code = 0; code < 100; code++) {
		addError((obd_code_e) code);
	}
	getErrorCodes(&localCopy);
	assertEquals(MAX_ERROR_CODES_COUNT, localCopy.count);

	// now we have full array and code below present
	removeError(code);
	getErrorCodes(&localCopy);
	assertEquals(MAX_ERROR_CODES_COUNT - 1, localCopy.count);
}

void sendOutConfirmation(char *value, int i) {
	// test implementation
}

static int lastInteger = -1;
static int lastInteger2 = -1;

static void testEchoI(int param) {
	lastInteger = param;
}

static void testEchoII(int param, int param2) {
	lastInteger = param;
	lastInteger2 = param2;
}

static char *lastFirst = NULL;
static char *lastThird = NULL;

static void testEchoSSS(char *first, char *second, char *third) {
	lastFirst = first;
	lastThird = third;
}

#define UNKNOWN_COMMAND "dfadasdasd"

static char confirmation[200];

extern int consoleActionCount;
extern TokenCallback consoleActions[CONSOLE_MAX_ACTIONS];

void handleConsoleLine2(char *line) {
	line = validateSecureLine(line);
	if (line == NULL)
		return; // error detected

	int lineLength = strlen(line);
	if (lineLength > 100) {
		// todo: better max size logic
		// todo: better reaction to excessive line
		return;
	}

	strcpy(confirmation, "confirmation_");
	strcat(confirmation, line);
	strcat(confirmation, ":");

	int firstTokenLength = tokenLength(line);

//	print("processing [%s] with %d actions\r\n", line, consoleActionCount);

	if (firstTokenLength == lineLength) {
		// no-param actions are processed here
		for (int i = 0; i < consoleActionCount; i++) {
			TokenCallback *current = &consoleActions[i];
			if (strEqual(line, current->token)) {
				// invoke callback function by reference
				(*current->callback)();
				// confirmation happens after the command to avoid conflict with command own output
				sendOutConfirmation(confirmation, lineLength);
				return;
			}
		}
	} else {
		char *ptr = line + firstTokenLength;
		ptr[0] = 0; // change space into line end
		ptr++; // start from next symbol

		for (int i = 0; i < consoleActionCount; i++) {
			TokenCallback *current = &consoleActions[i];
			if (strEqual(line, current->token)) {
				handleActionWithParameter(current, ptr);
				// confirmation happens after the command to avoid conflict with command own output
				sendOutConfirmation(confirmation, lineLength);
				return;
			}
		}
	}
	sendOutConfirmation("unknown command", 0);
	sendOutConfirmation(confirmation, -1);
	helpCommand();
}



void testConsoleLogic(void) {
	print("******************************************* testConsoleLogic\r\n");
	resetConsoleActions();

	helpCommand();

	char *ptr = validateSecureLine(UNKNOWN_COMMAND);
	assertEquals(0, strcmp(UNKNOWN_COMMAND, ptr));
	assertEquals(10, tokenLength(UNKNOWN_COMMAND));

	// handling invalid token should work
	handleConsoleLine2("sdasdafasd asd");

	print("addConsoleActionI\r\n");
	addConsoleActionI("echoi", testEchoI);
//	handleConsoleLine("echoi 239");
//	assertEquals(239, lastInteger);

//	print("addConsoleActionII\r\n");
//	handleConsoleLine("echoii 22 239");
//	assertEquals(22, lastInteger);
//	assertEquals(239, lastInteger2);

//	addConsoleActionII("echoii", testEchoII);
//	addConsoleActionSSS("echosss", testEchoSSS);
//
//
//
//	handleConsoleLine("echosss 111 222 333");
//	assertEquals(111, atoi(lastFirst));
//	assertEquals(333, atoi(lastThird));
}

void testGpsParser() {
	//parseNeo6m("$GPGLL,1234.34240,N,01234.44218,W,013141.00,A,A*7A");
}

