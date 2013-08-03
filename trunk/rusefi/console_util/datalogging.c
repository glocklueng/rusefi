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
#include "print.h"

#define OUTPUT_BUFFER 5000

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
	return NULL;
}

static char* get2ndCaption(int loggingPoint) {
	switch (loggingPoint) {
	case LP_RPM:
		return "RPM";
	case LP_THROTTLE:
		return "%";
	case LP_IAT:
		return "�F";
	case LP_ECT:
		return "�F";
	case LP_SECONDS:
		return "s";
	case LP_MAP:
		return "MAP";
	}
	fatal("No such loggingPoint");
	return NULL;
}

static int validateBuffer(Logging *logging, int extraLen, char *text) {
	if (logging->buffer == NULL) {
		strcpy(logging->SMALL_BUFFER, "Logging not initialized: ");
		strcat(logging->SMALL_BUFFER, logging->name);
		strcpy(logging->SMALL_BUFFER, "/");
		strcat(logging->SMALL_BUFFER, text);
		fatal(logging->SMALL_BUFFER);
		return TRUE;
	}

	int currentLen = (int) logging->linePointer - (int) (logging->buffer);
	if (currentLen + extraLen > logging->bufferSize - 1) {
		strcpy(logging->SMALL_BUFFER, "Logging buffer overflow: ");
		strcat(logging->SMALL_BUFFER, logging->name);
		strcpy(logging->SMALL_BUFFER, "/");
		strcat(logging->SMALL_BUFFER, text);
		fatal(logging->SMALL_BUFFER);
		return TRUE;
	}
	return FALSE;
}

void append(Logging *logging, char *text) {
	int extraLen = strlen(text);
	int errcode = validateBuffer(logging, extraLen, text);
	if (errcode)
		return;
//	print("%s", text);
	strcpy(logging->linePointer, text);
	logging->linePointer += extraLen;
}

void initLogging(Logging *logging, char *name, char *buffer, int bufferSize) {
	logging->name = name;
	logging->buffer = buffer;
	logging->bufferSize = bufferSize;
	resetLogging(logging);
}

void appendInt(Logging *logging, int value) {
	itoa(logging->SMALL_BUFFER, value);
	append(logging, logging->SMALL_BUFFER);
}

void msgInt(Logging *logging, char *caption, int value) {
	append(logging, caption);
	appendInt(logging, value);
	append(logging, DELIMETER);
}

void debugInt2(Logging *logging, char *caption, int captionSuffix, int value) {
	append(logging, caption);
	itoa(logging->SMALL_BUFFER, captionSuffix);
	append(logging, logging->SMALL_BUFFER);
	append(logging, DELIMETER);

	itoa(logging->SMALL_BUFFER, value);
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
	itoa(logging->SMALL_BUFFER, value);
	append(logging, logging->SMALL_BUFFER);
	append(logging, DELIMETER);
#if TAB_MODE
}
#endif
}

void debugFloat2(Logging *logging, char *caption, int captionSuffix, myfloat value, int precision) {
	append(logging, caption);
	itoa(logging->SMALL_BUFFER, captionSuffix);
	append(logging, logging->SMALL_BUFFER);
	append(logging, DELIMETER);

	ftoa(logging->SMALL_BUFFER, value, precision);
	append(logging, logging->SMALL_BUFFER);
	append(logging, DELIMETER);
}

void debugFloat(Logging *logging, char *caption, myfloat value, int precision) {
#if TAB_MODE
	if (lineNumber == 0) {
		append(text);
		append(DELIMETER);
	}
#else
	append(logging, caption);
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

void resetLogging(Logging *logging) {
	logging->linePointer = logging->buffer;
}

static char ioBuffer[OUTPUT_BUFFER];

/**
 * this method should invoked on the main thread only
 */
static void printWithLength(char *line) {
	/**
	 * this is my way to detect serial port transmission errors
	 * following code is functionally identical to
	 *   print("line:%d:%s\r\n", len, line);
	 * but it is faster because it outputs the whole buffer, not single characters
	 */
	int len = strlen(line);
	strcpy(ioBuffer, "line:");
	char *p = ioBuffer + strlen(ioBuffer);
	p = itoa(p, len);
	*p++ = ':';
	strcpy(p, line);
	p += len;
	*p++ = '\r';
	*p++ = '\n';

	consoleOututBuffer(ioBuffer, p - ioBuffer);
}

void printLine(Logging *logging) {
	printWithLength(logging->buffer);
	resetLogging(logging);
}

static void commonSimpleMsg(Logging *logging, char *msg, int value) {
	resetLogging(logging);
	append(logging, "msg");
	append(logging, DELIMETER);
	msgInt(logging, msg, value);
}

/**
 * This method would output a simple console message immediately.
 * This method should only be invoked on main thread because only the main thread can write to the console
 */
void printSimpleMsg(Logging *logging, char *msg, int value) {
	commonSimpleMsg(logging, msg, value);
	printLine(logging);
}

/**
 * This method places a simple console message into the buffer for later output by the main thread
 * TODO: detect current threadId and merge this method with printSimpleMsg?
 */
void scheduleSimpleMsg(Logging *logging, char *msg, int value) {
	commonSimpleMsg(logging, msg, value);
	scheduleLogging(logging);
}


void scheduleIntValue(Logging *logging, char *msg, int value) {
	resetLogging(logging);

	append(logging, msg);
	append(logging, DELIMETER);
	appendInt(logging, value);
	append(logging, DELIMETER);

	scheduleLogging(logging);
}

static char pendingBuffer[OUTPUT_BUFFER];

void lockOutputBuffer();
void unlockOutputBuffer();

static char fatalMessage[200];

void scheduleLogging(Logging *logging) {
	// this could be done without locking
	int newLength = strlen(logging->buffer);

	lockOutputBuffer();
	// I hope this is fast enough to operate under sys lock
	int curLength = strlen(pendingBuffer);
	if (curLength + newLength >= OUTPUT_BUFFER) {
		// this happens in case of serial-over-USB, todo: find a better solution
//		strcpy(fatalMessage, "datalogging.c: output buffer overflow: ");
//		strcat(fatalMessage, logging->name);
//		fatal(fatalMessage);
		unlockOutputBuffer();
		return;
	}

	strcat(pendingBuffer, logging->buffer);
	unlockOutputBuffer();
	resetLogging(logging);
}

static char outputBuffer[OUTPUT_BUFFER];

void printPending() {
	lockOutputBuffer();
	// we cannot output under syslock, so another buffer
	strcpy(outputBuffer, pendingBuffer);
	pendingBuffer[0] = 0; // reset pending buffer
	unlockOutputBuffer();

	if (strlen(outputBuffer) > 0)
		printWithLength(outputBuffer);
}
