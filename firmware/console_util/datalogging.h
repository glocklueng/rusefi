/*
 *  Created on: Feb 25, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    datalogging.h
 * @brief   Buffered console output stream header
 */


#ifndef DATALOGGING_H_
#define DATALOGGING_H_

#include "global.h"

#define	TAB_MODE	FALSE

#if TAB_MODE
#define DELIMETER	"\t"
#else
#define DELIMETER	","
#endif

typedef enum {
	LP_RPM, LP_ECT, LP_IAT, LP_THROTTLE, LP_SECONDS, LP_MAP,

} LoggingPoints;

// todo: migrate to external buffer so that different instances have different
// size of buffers?
typedef struct {
	char *name;
	char SMALL_BUFFER[40];
	// todo: explicitly default buffer externally so that we do not have default_buffer where we do not need it?
	char DEFAULT_BUFFER[200];
	char *buffer;
	char *linePointer;
	int bufferSize;
} Logging;

void lockOutputBuffer(void);
void unlockOutputBuffer(void);

void initIntermediateLoggingBuffer(void);

void initLogging(Logging *logging, char *name, char *buffer, int bufferSize);

void msgInt(Logging *logging, char *caption, int value);
void debugInt(Logging *logging, char *caption, int value);

void debugFloat(Logging *logging, char *text, myfloat value, int precision);
void debugFloat2(Logging *logging, char *caption, int captionSuffix, myfloat value, int precision);

void logInt(Logging *logging, int loggingPoint, int value);
void logFloat(Logging *logging, int loggingPoint, myfloat value);

void resetLogging(Logging *logging);
void printLine(Logging *logging);

void printSimpleMsg(Logging *logging, char *msg, int value);

void append(Logging *logging, char *text);
void appendInt(Logging *logging, int value);

/**
 * this method copies the line into the intermediate buffer for later output by
 * the main thread
 */
void scheduleLogging(Logging *logging);
void scheduleSimpleMsg(Logging *logging, char *msg, int value);

void scheduleIntValue(Logging *logging, char *msg, int value);

/**
 * this should only be invoked by the 'main' thread in order to keep the console safe
 */
void printPending(void);

#endif /* DATALOGGING_H_ */
