/**
 * @file    datalogging.c
 * @brief   Buffered console output stream code
 *
 * Here we have a memory buffer and method related to
 * printing messages into this buffer. The purpose of the
 * buffer is to allow fast, non-blocking, thread-safe logging.
 *
 * The idea is that each interrupt handler would have it's own logging buffer. You can add
 * stuff into this buffer without any locking since it's you own buffer, and once you get
 * the whole message you invoke the scheduleLogging() method which appends your local content
 * into the global logging buffer, from which it is later dispatched to the console by our
 * main console thread.
 *
 * @date Feb 25, 2013
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

#include <stdbool.h>
#include "main.h"
#include "rfiutil.h"
#include "chprintf.h"
#include "chmtx.h"
#include "memstreams.h"
#include "console_io.h"

#define OUTPUT_BUFFER 9000
/**
 * This is the size of the MemoryStream used by chvprintf
 */
#define INTERMEDIATE_LOGGING_BUFFER_SIZE 2000

// we use this magic constant to make sure it's not just a random non-zero int in memory
#define MAGIC_LOGGING_FLAG 45234441

/**
 * This is the buffer into which all the data providers write
 */
#if defined __GNUC__
static char pendingBuffer[OUTPUT_BUFFER] __attribute__((section(".ccm")));
#else
static char pendingBuffer[OUTPUT_BUFFER];
#endif
/**
 * We copy all the pending data into this buffer once we are ready to push it out
 */
static char outputBuffer[OUTPUT_BUFFER];

static MemoryStream intermediateLoggingBuffer;
static uint8_t intermediateLoggingBufferData[INTERMEDIATE_LOGGING_BUFFER_SIZE]; //todo define max-printf-buffer
static bool intermediateLoggingBufferInited = FALSE;

static int validateBuffer(Logging *logging, int extraLen, const char *text) {
	if (logging->buffer == NULL) {
		strcpy(logging->SMALL_BUFFER, "Logging not initialized: ");
		strcat(logging->SMALL_BUFFER, logging->name);
		strcat(logging->SMALL_BUFFER, "/");
		strcat(logging->SMALL_BUFFER, text);
		fatal(logging->SMALL_BUFFER);
		return TRUE;
	}

	int currentLen = loggingSize(logging);
	if (currentLen + extraLen > logging->bufferSize - 1) {
		strcpy(logging->SMALL_BUFFER, "Logging buffer overflow: ");
		strcat(logging->SMALL_BUFFER, logging->name);
		strcat(logging->SMALL_BUFFER, "/");
		strcat(logging->SMALL_BUFFER, text);
		fatal(logging->SMALL_BUFFER);
//		unlockOutputBuffer();
//		resetLogging(logging);
		return TRUE;
	}
	return FALSE;
}

void append(Logging *logging, const char *text) {
	chDbgCheck(text!=NULL, "append NULL");
	int extraLen = strlen(text);
	int errcode = validateBuffer(logging, extraLen, text);
	if (errcode)
		return;
	strcpy(logging->linePointer, text);
	logging->linePointer += extraLen;
}

static void vappendPrintfI(Logging *logging, const char *fmt, va_list arg) {
	intermediateLoggingBuffer.eos = 0; // reset
	chvprintf((BaseSequentialStream *) &intermediateLoggingBuffer, fmt, arg);
	intermediateLoggingBuffer.buffer[intermediateLoggingBuffer.eos] = 0; // need to terminate explicitly
	append(logging, (char *) intermediateLoggingBufferData);
}

void vappendPrintf(Logging *logging, const char *fmt, va_list arg) {
	if (!intermediateLoggingBufferInited) {
		fatal("intermediateLoggingBufferInited not inited!");
		return;
	}
	int is_locked = isLocked();
	int icsr_vectactive = isIsrContext();
	if (is_locked) {
		vappendPrintfI(logging, fmt, arg);
	} else {
		if (icsr_vectactive == 0) {
			chSysLock()
			;
			vappendPrintfI(logging, fmt, arg);
			chSysUnlock()
			;
		} else {
			chSysLockFromIsr()
			;
			vappendPrintfI(logging, fmt, arg);
			chSysUnlockFromIsr()
			;
		}
	}
}

void appendPrintf(Logging *logging, const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vappendPrintf(logging, fmt, ap);
	va_end(ap);
}

// todo: this method does not really belong to this file
char* getCaption(LoggingPoints loggingPoint) {
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
	case LP_MAF:
		return "MAF";
	case LP_MAP:
		return "MAP";
	case LP_MAP_RAW:
		return "MAP_R";
	}
	fatal("No such loggingPoint");
	return NULL;
}

// todo: this method does not really belong to this file
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
	case LP_MAF:
		return "MAF";
	}
	fatal("No such loggingPoint");
	return NULL;
}

void initLoggingExt(Logging *logging, const char *name, char *buffer, int bufferSize) {
	print("Init logging %s\r\n", name);
	logging->name = name;
	logging->buffer = buffer;
	logging->bufferSize = bufferSize;
	resetLogging(logging);
	logging->isInitialized = MAGIC_LOGGING_FLAG;
}

int isInitialized(Logging *logging) {
	return logging->isInitialized == MAGIC_LOGGING_FLAG;
}

void initLogging(Logging *logging, const char *name) {
	initLoggingExt(logging, name, logging->DEFAULT_BUFFER, sizeof(logging->DEFAULT_BUFFER));
}

void debugInt(Logging *logging, const char *caption, int value) {
	append(logging, caption);
	append(logging, DELIMETER);
	appendPrintf(logging, "%d%s", value, DELIMETER);
}

void appendFloat(Logging *logging, float value, int precision) {
	// todo: this implementation is less than perfect
	switch (precision) {
	case 1:
		appendPrintf(logging, "%..10f", value);
		break;
	case 2:
		appendPrintf(logging, "%..100f", value);
		break;
	case 3:
		appendPrintf(logging, "%..1000f", value);
		break;
	case 4:
		appendPrintf(logging, "%..10000f", value);
		break;
	case 5:
		appendPrintf(logging, "%..100000f", value);
		break;
	case 6:
		appendPrintf(logging, "%..1000000f", value);
		break;

	default:
		appendPrintf(logging, "%f", value);
	}
}

void debugFloat(Logging *logging, const char *caption, float value, int precision) {
	append(logging, caption);
	append(logging, DELIMETER);

	appendFloat(logging, value, precision);
	append(logging, DELIMETER);
}

static char header[16];

/**
 * this method should invoked on the main thread only
 */
static void printWithLength(char *line) {
	/**
	 * this is my way to detect serial port transmission errors
	 * following code is functionally identical to
	 *   print("line:%d:%s\r\n", len, line);
	 * but it is faster because it outputs the whole buffer, not single characters
	 * We need this optimization because when we output larger chunks of data like the wave_chart:
	 * When we work with actual hardware, it is faster to invoke 'chSequentialStreamWrite' for the
	 * whole buffer then to invoke 'chSequentialStreamPut' once per character.
	 */
	int len = strlen(line);
	strcpy(header, "line:");
	char *p = header + strlen(header);
	p = itoa10(p, len);
	*p++ = ':';
	*p++ = '\0';

	p = line;
	p += len;
	*p++ = '\r';
	*p++ = '\n';

	if (!isConsoleReady())
		return;
	consoleOutputBuffer((const int8_t *) header, strlen(header));
	consoleOutputBuffer((const int8_t *) line, p - line);
}

void printLine(Logging *logging) {
	printWithLength(logging->buffer);
	resetLogging(logging);
}

void appendMsgPrefix(Logging *logging) {
	appendPrintf(logging, "msg%s", DELIMETER);
}

void appendMsgPostfix(Logging *logging) {
	append(logging, DELIMETER);
}

void resetLogging(Logging *logging) {
	char *buffer = logging->buffer;
	chDbgCheck(buffer!=NULL, "null buffer");
	logging->linePointer = buffer;
}

/**
 * This method would output a simple console message immediately.
 * This method should only be invoked on main thread because only the main thread can write to the console
 */
void printMsg(Logging *logger, const char *fmt, ...) {
//	resetLogging(logging); // I guess 'reset' is not needed here?
	appendMsgPrefix(logger);

	va_list ap;
	va_start(ap, fmt);
	vappendPrintf(logger, fmt, ap);
	va_end(ap);

	append(logger, DELIMETER);
	printLine(logger);
}

void scheduleMsg(Logging *logging, const char *fmt, ...) {
	resetLogging(logging); // todo: is 'reset' really needed here?
	appendMsgPrefix(logging);

	va_list ap;
	va_start(ap, fmt);
	vappendPrintf(logging, fmt, ap);
	va_end(ap);

	appendMsgPostfix(logging);
	scheduleLogging(logging);
}

// todo: remove this method, replace with 'scheduleMsg'
void scheduleIntValue(Logging *logging, char *msg, int value) {
	resetLogging(logging);

	append(logging, msg);
	append(logging, DELIMETER);
	appendPrintf(logging, "%d", value);
	append(logging, DELIMETER);

	scheduleLogging(logging);
}

void scheduleLogging(Logging *logging) {
	// this could be done without locking
	int newLength = strlen(logging->buffer);

	bool_t alreadyLocked = lockOutputBuffer();
	// I hope this is fast enough to operate under sys lock
	int curLength = strlen(pendingBuffer);
	if (curLength + newLength >= OUTPUT_BUFFER) {
		/**
		 * if no one is consuming the data we have to drop it
		 * this happens in case of serial-over-USB, todo: find a better solution
		 *
		 */
//		strcpy(fatalMessage, "datalogging.c: output buffer overflow: ");
//		strcat(fatalMessage, logging->name);
//		fatal(fatalMessage);
		if (!alreadyLocked)
			unlockOutputBuffer();
		resetLogging(logging);
		return;
	}

	strcat(pendingBuffer, logging->buffer);
	if (!alreadyLocked)
		unlockOutputBuffer();
	resetLogging(logging);
}

uint32_t loggingSize(Logging *logging) {
	return (int) logging->linePointer - (int) (logging->buffer);
}

/**
 * This method actually sends all the pending data to the communication layer
 */
void printPending() {
	lockOutputBuffer();
	// we cannot output under syslock, so another buffer
	strcpy(outputBuffer, pendingBuffer);
	pendingBuffer[0] = 0; // reset pending buffer
	unlockOutputBuffer();

	if (strlen(outputBuffer) > 0)
		printWithLength(outputBuffer);
}

void initIntermediateLoggingBuffer(void) {
	msObjectInit(&intermediateLoggingBuffer, intermediateLoggingBufferData, INTERMEDIATE_LOGGING_BUFFER_SIZE, 0);
	intermediateLoggingBufferInited = TRUE;
}
