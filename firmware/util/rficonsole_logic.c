/*
 * @date Nov 15, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    rficonsole_logic.c
 * @brief   Console interactive shell code
 *
 * Here we have a data structure which holds all the dynamically-registered
 * command line interface action names & callback. This logic is invoked in
 * user context by the console thread - see consoleThreadThreadEntryPoint
 */

#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "rficonsole_logic.h"

static int consoleActionCount = 0;
static TokenCallback consoleActions[CONSOLE_MAX_ACTIONS];

void resetConsoleActions(void) {
	consoleActionCount = 0;
}

static void doAddAction(char *token, int type, Void callback) {
	if (consoleActionCount == CONSOLE_MAX_ACTIONS) {
		fatal("Too many console actions\r\n");
		return;
	}
	TokenCallback *current = &consoleActions[consoleActionCount++];
	current->token = token;
	current->parameterType = type;
	current->callback = callback;
}

/**
 * @brief	Register console action without parameters
 */
void addConsoleAction(char *token, Void callback) {
	doAddAction(token, NO_PARAMETER, callback);
}

/**
 * @brief	Register a console command with one Integer parameter
 */
void addConsoleActionI(char *token, VoidInt callback) {
	doAddAction(token, ONE_PARAMETER, (Void) callback);
}

/**
 * @brief	Register a console command with two Integer parameters
 */
void addConsoleActionII(char *token, VoidIntInt callback) {
	doAddAction(token, TWO_INTS_PARAMETER, (Void) callback);
}

void addConsoleActionS(char *token, VoidCharPtr callback) {
	doAddAction(token, STRING_PARAMETER, (Void) callback);
}

void addConsoleActionSSS(char *token, VoidCharPtrCharPtrCharPtr callback) {
	doAddAction(token, STRING3_PARAMETER, (Void) callback);
}

void addConsoleActionF(char *token, VoidFloat callback) {
	doAddAction(token, FLOAT_PARAMETER, (Void) callback);
}

// string to integer
static int atoi(char *string) {
	// todo: use stdlib '#include <stdlib.h> '
	int len = strlen(string);
	if (len == 0)
		return -ERROR_CODE;
	if (string[0] == '-')
		return -atoi(string + 1);
	int result = 0;

	for (int i = 0; i < len; i++) {
		char ch = string[i];
		if (ch < '0' || ch > '9') {
			return ERROR_CODE;
		}
		int c = ch - '0';
		result = result * 10 + c;
	}

	return result;
}

static int indexOf(char *string, char ch) {
	// todo: there should be a standard function for this
	int len = strlen(string);
	for (int i = 0; i < len; i++) {
		if (string[i] == ch)
			return i;
	}
	return -1;
}

// string to float
static float atof(char *string) {
	// todo: is there a standard function?
	// todo: create a unit test
	int dotIndex = indexOf(string, '.');
	if (dotIndex == -1) {
		// just an integer
		int result = atoi(string);
		return (float) result;
	}
	string[dotIndex] = 0;
	int integerPart = atoi(string);
	string += (dotIndex + 1);
	int decimalLen = strlen(string);
	int decimal = atoi(string);
	float divider = 1.0;
	// todo: reuse 'pow10' function which we have anyway
	for (int i = 0; i < decimalLen; i++)
		divider = divider * 10.0;
	return integerPart + decimal / divider;
}

/**
 * @brief This function prints out a list of all available commands
 */
static void help(void) {
	print("%d actions available:\r\n", consoleActionCount);
	for (int i = 0; i < consoleActionCount; i++) {
		TokenCallback *current = &consoleActions[i];
		print("  %s: %d parameters\r\n", current->token, current->parameterType);
	}
}

/**
 * @brief This is just a test function
 */
static void echo(int value) {
	print("got value: %d\r\n", value);
}

void addDefaultConsoleActions() {
	addConsoleAction("help", &help);
	addConsoleActionI("echo", &echo);
}

void handleActionWithParameter(TokenCallback *current, char *parameter) {
	if (current->parameterType == STRING_PARAMETER) {
		VoidCharPtr callbackS = (VoidCharPtr) current->callback;
		(*callbackS)(parameter);
		return;
	}

	if (current->parameterType == STRING3_PARAMETER) {
		int spaceIndex = indexOf(parameter, ' ');
		if (spaceIndex == -1)
			return;
		parameter[spaceIndex] = 0;
		char * firstParam = parameter;

		parameter += spaceIndex + 1;
		spaceIndex = indexOf(parameter, ' ');
		if (spaceIndex == -1)
			return;
		parameter[spaceIndex] = 0;
		char * secondParam = parameter;
		parameter += spaceIndex + 1;
		char * thirdParam = parameter;

		VoidCharPtrCharPtrCharPtr callbackS = (VoidCharPtrCharPtrCharPtr) current->callback;
		(*callbackS)(firstParam, secondParam, thirdParam);
		return;

	}

	if (current->parameterType == TWO_INTS_PARAMETER) {
		int spaceIndex = indexOf(parameter, ' ');
		if (spaceIndex == -1)
			return;
		parameter[spaceIndex] = 0;
		int value1 = atoi(parameter);
		parameter += spaceIndex + 1;
		int value2 = atoi(parameter);
		VoidIntInt callbackS = (VoidIntInt) current->callback;
		(*callbackS)(value1, value2);
		return;
	}

	if (current->parameterType == FLOAT_PARAMETER) {
		float value = atof(parameter);
		VoidFloat callbackF = (VoidFloat) current->callback;

		// invoke callback function by reference
		(*callbackF)(value);
		return;
	}

	int value = atoi(parameter);
	if (value == ERROR_CODE) {
		print("invalid integer [%s]\r\n", parameter);
		return;
	}

	VoidInt callback1 = (VoidInt) current->callback;

	// invoke callback function by reference
	(*callback1)(value);

}

/**
 * @return Number of space-separated tokens in the string
 */
 int tokenLength(char *msgp) {
	int result = 0;
	while (*msgp) {
		char ch = *msgp++;
		if (ch == ' ')
			break;
		result++;
	}
	return result;
}

static int strEqual(char *str1, char *str2) {
	// todo: there must be a standard function?!
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	if (len1 != len2)
		return FALSE;
	for (int i = 0; i < len1; i++)
		if (str1[i] != str2[i])
			return FALSE;
	return TRUE;
}

void initConsoleLogic() {
}

char *validateSecureLine(char *line) {
	if (line == NULL)
		return NULL;
	if (strncmp("sec!", line, 4) == 0) {
		// COM protocol looses bytes, this is a super-naive error detection

		print("sec mode [%s]\r\n", line);
		line += 4;
		print("sec mode [%s]\r\n", line);

		char *divider = line;
		while (*divider != '!') {
			if (*divider == '\0') {
				print("Divider not found [%s]\r\n", line);
				return NULL;
			}
			divider++;
		}
		*divider++ = 0; // replacing divider symbol with zero
		int expectedLength = atoi(line);
		line = divider;
		int actualLength = strlen(line);
		if (expectedLength != actualLength) {
			print("Error detected: expected %d but got %d in [%s]\r\n", expectedLength, actualLength, line);
			return NULL;
		}
	}
	return line;
}

static char confirmation[200];

void sendOutConfirmation(char *value, int i);

/**
 * @brief This function takes care of one command line once we have it
 */
void handleConsoleLine(char *line) {
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
	help();
}
