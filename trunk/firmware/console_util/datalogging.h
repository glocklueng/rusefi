/**
 * @file    datalogging.h
 * @brief   Buffered console output stream header
 *
 * @date Feb 25, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
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
	LP_RPM, LP_ECT, LP_IAT, LP_THROTTLE, LP_SECONDS, LP_MAP,LP_MAP_RAW,

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
	volatile int isInitialized;
} Logging;

void lockOutputBuffer(void);
void unlockOutputBuffer(void);

void initIntermediateLoggingBuffer(void);
int loggingSize(Logging *logging);

int isInitialized(Logging *logging);

void initLogging(Logging *logging, char *name);
void initLoggingExt(Logging *logging, char *name, char *buffer, int bufferSize);

void debugInt(Logging *logging, char *caption, int value);
void logInt(Logging *logging, int loggingPoint, int value);

void debugFloat(Logging *logging, char *text, myfloat value, int precision);
void logFloat(Logging *logging, int loggingPoint, myfloat value);
void appendFloat(Logging *logging, myfloat value, int precision);

void resetLogging(Logging *logging);
void printLine(Logging *logging);

void appendMsgPrefix(Logging *logging);
void printSimpleMsg(Logging *logging, char *msg, int value);

void appendPrintf(Logging *logging, const char *fmt, ...);
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
