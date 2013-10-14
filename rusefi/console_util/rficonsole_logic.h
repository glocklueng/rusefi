/*
 *  Created on: Nov 15, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    rficonsole_logic.h
 * @brief   Console interactive shell header
 */

#ifndef RFICONSOLE_LOGIC_H_
#define RFICONSOLE_LOGIC_H_

#define ERROR_CODE -11223344
#define CONSOLE_MAX_ACTIONS 32

#ifndef FALSE
#define FALSE       0
#endif
#ifndef TRUE
#define TRUE        (!FALSE)
#endif

typedef enum {
	NO_PARAMETER = 0,
	ONE_PARAMETER = 1,
	FLOAT_PARAMETER = 2,
	STRING_PARAMETER = 3,
	TWO_INTS_PARAMETER = 4,
} ACTION_PARAMETER_TYPE;

typedef struct {
	char *token;
	int parameterType;
	void (*callback)(void);
} TokenCallback;

void addDefaultConsoleActions(void);
void print(const char *fmt, ...);
int systicks2ms(int systicks);

typedef void (*Void)();
typedef void (*VoidInt)(int);
typedef void (*VoidFloat)(float);
typedef void (*VoidIntInt)(int, int);
typedef void (*VoidCharPtr)(char *);

void initConsoleLogic(void);
void handleConsoleLine(char *line);
void addConsoleAction(char *token, Void callback);
void addConsoleAction1(char *token, VoidInt callback);
void addConsoleAction2I(char *token, VoidIntInt callback);
void addConsoleActionF(char *token, VoidFloat callback);
void addConsoleActionS(char *token, VoidCharPtr callback);

void fatal3(char *msg, char *file, int line);

#define fatal(x) (fatal3(x, __FILE__, __LINE__));


#endif /* RFICONSOLE_H_ */
