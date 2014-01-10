/**
 * @file    datalogging.c
 * @brief   Buffered console output stream code
 *
 * Here we have a memory buffer and method related to
 * printing messages into this buffer. The purpose of the
 * buffer is to allow fast, non-blocking, thread-safe logging.
 *
 * @date Feb 25, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "datalogging.h"
#include "rfiutil.h"
#include "chprintf.h"
#include "chmtx.h"
#include "memstreams.h"

#define OUTPUT_BUFFER 5000
/**
 * This is the size of the MemoryStream used by chvprintf
 */
#define INTERMEDIATE_LOGGING_BUFFER_SIZE 2000

// we use this magic constant to make sure it's not just a random non-zero int in memory
#define MAGIC_LOGGING_FLAG 45234441

/**
 * This is the buffer into which all the data providers write
 */
static char pendingBuffer[OUTPUT_BUFFER];
/**
 * We copy all the pending data into this buffer once we are ready to push it out
 */
static char outputBuffer[OUTPUT_BUFFER];
/**
 * ... and we need another buffer for to make the message with with control sum
 * TODO: if needed we can eliminate this buffer by making some space in the start
 * of the 'outputBuffer' into which we would put the control sum when time comes
 */
static char ioBuffer[OUTPUT_BUFFER];

static MemoryStream intermediateLoggingBuffer;
static uint8_t intermediateLoggingBufferData[INTERMEDIATE_LOGGING_BUFFER_SIZE]; //todo define max-printf-buffer
static bool intermediateLoggingBufferInited = FALSE;

static int validateBuffer(Logging *logging, int extraLen, char *text) {
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
		return TRUE;
	}
	return FALSE;
}

static void append(Logging *logging, char *text) {
	chDbgAssert(text!=NULL, "append NULL", 0);
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

static void vappendPrintf(Logging *logging, const char *fmt, va_list arg) {
	if (!intermediateLoggingBufferInited) {
		fatal("intermediateLoggingBufferInited not inited!");
		return;
	}
	int isLocked = dbg_lock_cnt != 0;
	uint32_t icsr_vectactive = SCB->ICSR & 0x1fU;
	if (isLocked) {
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

void initLoggingExt(Logging *logging, char *name, char *buffer, int bufferSize) {
	print("Init logging\r\n");
	logging->name = name;
	logging->buffer = buffer;
	logging->bufferSize = bufferSize;
	resetLogging(logging);
	logging->isInitialized = MAGIC_LOGGING_FLAG;
}

int isInitialized(Logging *logging) {
	return logging->isInitialized == MAGIC_LOGGING_FLAG;
}

void initLogging(Logging *logging, char *name) {
	initLoggingExt(logging, name, logging->DEFAULT_BUFFER, sizeof(logging->DEFAULT_BUFFER));
}

void debugInt(Logging *logging, char *caption, int value) {
	append(logging, caption);
	append(logging, DELIMETER);
	appendPrintf(logging, "%d%s", value, DELIMETER);
}

void appendFloat(Logging *logging, myfloat value, int precision) {
	// todo: this implementation is less than perfect
	switch (precision) {
	case 1:
	  appendPrintf(logging, "%..10f",  value);
	  break;
	case 2:
	  appendPrintf(logging, "%..100f",  value);
	  break;
	case 3:
	  appendPrintf(logging, "%..1000f",  value);
	  	  break;
	case 4:
	  appendPrintf(logging, "%..10000f",  value);
	  	  break;
	case 5:
	  appendPrintf(logging, "%..100000f",  value);
	  	  break;
	case 6:
	  appendPrintf(logging, "%..1000000f",  value);
	  	  break;

	default:
	  appendPrintf(logging, "%f",  value);
	}
}

void debugFloat(Logging *logging, char *caption, myfloat value, int precision) {
	append(logging, caption);
	append(logging, DELIMETER);

	appendFloat(logging, value, precision);
	append(logging, DELIMETER);
}
/*
void logInt(Logging *logging, LoggingPoints loggingPoint, int value) {
	char *caption = getCaption(loggingPoint);
	debugInt(logging, caption, value);
}

void logFloat(Logging *logging, LoggingPoints loggingPoint, myfloat value) {
	debugFloat(logging, getCaption(loggingPoint), value, 2);
}
*/

static void commonSimpleMsg(Logging *logging, char *msg, int value) {
	resetLogging(logging);
	appendMsgPrefix(logging);
	appendPrintf(logging, "%s%d%s", msg, value, DELIMETER);
}

void consoleOutputBuffer(const int8_t *buf, int size);

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
	strcpy(ioBuffer, "line:");
	char *p = ioBuffer + strlen(ioBuffer);
	p = itoa(p, len);
	*p++ = ':';
	strcpy(p, line);
	p += len;
	*p++ = '\r';
	*p++ = '\n';

	if (!is_serial_ready())
		return;
	consoleOutputBuffer((const int8_t *)ioBuffer, p - ioBuffer);
}

void printLine(Logging *logging) {
	printWithLength(logging->buffer);
	resetLogging(logging);
}

void appendMsgPrefix(Logging *logging) {
	appendPrintf(logging, "msg%s", DELIMETER);
}

void resetLogging(Logging *logging) {
	char *buffer = logging->buffer;
	chDbgAssert(buffer!=NULL, "null buffer", 0);
	logging->linePointer = buffer;
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
	appendPrintf(logging, "%d", value);
	append(logging, DELIMETER);

	scheduleLogging(logging);
}

void scheduleLogging(Logging *logging) {
	// this could be done without locking
	int newLength = strlen(logging->buffer);

	lockOutputBuffer();
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
		unlockOutputBuffer();
		resetLogging(logging);
		return;
	}

	strcat(pendingBuffer, logging->buffer);
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
