/*
 * datalogging.c
 *
 *  Created on: Feb 25, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include <string.h>
#include "datalogging.h"
#include "rficonsole_logic.h"
#include "rfiutil.h"

#define	TAB_MODE	FALSE

#if TAB_MODE
#define DELIMETER	"\t"
#else
#define DELIMETER	","
#endif

static char* getCaption(int loggingPoint) {
	switch (loggingPoint) {
	case LP_RPM:
		return "RPM";
	case LP_THROTTLE:
		return "TP";
	case LP_IAT:
		return "MAT";
	case LP_ECT:
		return "CLT";
	case LP_SECONDS:
		return "SecL";
	case LP_MAP:
		return "MAP";
	}
	fatal("No such loggingPoint");
	return NULL ;
}

static char* get2ndCaption(int loggingPoint) {
	switch (loggingPoint) {
	case LP_RPM:
		return "RPM";
	case LP_THROTTLE:
		return "%";
	case LP_IAT:
		return "°F";
	case LP_ECT:
		return "°F";
	case LP_SECONDS:
		return "s";
	case LP_MAP:
		return "MAP";
	}
	fatal("No such loggingPoint");
	return NULL ;
}


static void append(Logging *logging, char *text) {
//	print("%s", text);
	strcpy(logging->linePointer, text);
	logging->linePointer += strlen(text);
}

void msgChar(Logging *logging, char *text) {
	append(logging, text);
}

void msgInt(Logging *logging, char *caption, int value) {
	append(logging, caption);

	char *p = itoa_signed(logging->SMALL_BUFFER, value, 10);
	*p = 0;
	append(logging, logging->SMALL_BUFFER);
	append(logging, DELIMETER);
}

void debugInt(Logging *logging, char *caption, int value) {
#if TAB_MODE
	if (lineNumber == 0) {
		append(logging, caption);
		append(logging, DELIMETER);
	}
#else
	append(logging, caption);
	append(logging, DELIMETER);
#endif

#if TAB_MODE
	if(lineNumber > 0) {
#endif
	char *p = itoa_signed(logging->SMALL_BUFFER, value, 10);
	*p = 0;
	append(logging, logging->SMALL_BUFFER);
	append(logging, DELIMETER);
#if TAB_MODE
}
#endif
}

void debugFloat(Logging *logging, char *text, myfloat value, int precision) {
#if TAB_MODE
	if (lineNumber == 0) {
		append(text);
		append(DELIMETER);
	}
#else
	append(logging, text);
	append(logging, DELIMETER);
#endif

#if TAB_MODE
	if(lineNumber > 0) {
#endif
	ftoa(logging->SMALL_BUFFER, value, precision);
	append(logging, logging->SMALL_BUFFER);
	append(logging, DELIMETER);
#if TAB_MODE
}
#endif
}

void logInt(Logging *logging, int loggingPoint, int value) {
	char *caption = getCaption(loggingPoint);
	debugInt(logging, caption, value);
}

void logFloat(Logging *logging, int loggingPoint, myfloat value) {
	debugFloat(logging, getCaption(loggingPoint), value, 1);
}

void logStartLine(Logging *logging) {
	logging->linePointer = logging->LINE_BUFFER;
}

void printLine(Logging *logging) {
//	lineNumber++;
	int len = strlen(logging->LINE_BUFFER);
	print("line:%d:%s\r\n", len, logging->LINE_BUFFER);
}

volatile Logging *pending = NULL;

static void commonSimpleMsg(Logging *logging, char *msg, int value) {
	logStartLine(logging);
	append(logging, "msg");
	append(logging, DELIMETER);
	msgInt(logging, msg, value);
}

void printSimpleMsg(Logging *logging, char *msg, int value) {
	commonSimpleMsg(logging, msg, value);
	printLine(logging);
}

void queueSimpleMsg(Logging *logging, char *msg, int value) {
	commonSimpleMsg(logging, msg, value);
	logPending(logging);
}

void logPending(Logging *logging) {
	pending = logging;
}

void printPending() {
	Logging *p = pending;
	if (p != NULL ) {
		pending = NULL;
		printLine(p);
	}
}
