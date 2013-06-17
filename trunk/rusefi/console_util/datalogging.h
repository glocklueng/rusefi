/*
 * datalogging.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef DATALOGGING_H_
#define DATALOGGING_H_

#include "global.h"

typedef enum {
	LP_RPM, LP_ECT, LP_IAT, LP_THROTTLE, LP_SECONDS, LP_MAP,

} LoggingPoints;

typedef struct {
	char SMALL_BUFFER[40];
	char LINE_BUFFER[500];
	char* linePointer;
} Logging;

void msgChar(Logging *logging, char *text);

void msgInt(Logging *logging, char *caption, int value);
void debugInt(Logging *logging, char *caption, int value);
void debugFloat(Logging *logging, char *text, myfloat value, int precision);

void logInt(Logging *logging, int loggingPoint, int value);
void logFloat(Logging *logging, int loggingPoint, myfloat value);

void logStartLine(Logging *logging);
void printLine(Logging *logging);

void printSimpleMsg(Logging *logging, char *msg, int value);
void queueSimpleMsg(Logging *logging, char *msg, int value);
void logPending(Logging *logging);
void printPending();

#endif /* DATALOGGING_H_ */
