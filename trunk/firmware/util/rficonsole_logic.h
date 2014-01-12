/*
 * @date Nov 15, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    rficonsole_logic.h
 * @brief   Console interactive shell header
 */

#ifndef RFICONSOLE_LOGIC_H_
#define RFICONSOLE_LOGIC_H_

#define ERROR_CODE -11223344
#define CONSOLE_MAX_ACTIONS 42

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

typedef void (*Void)(void);
typedef void (*VoidInt)(int);
typedef void (*VoidFloat)(float);
typedef void (*VoidIntInt)(int, int);
typedef void (*VoidCharPtr)(char *);
typedef void (*VoidCharPtrCharPtrCharPtr)(char *, char *, char *);

void resetConsoleActions(void);
void initConsoleLogic(void);
void handleConsoleLine(char *line);
void addConsoleAction(char *token, Void callback);
void addConsoleActionI(char *token, VoidInt callback);
void addConsoleActionII(char *token, VoidIntInt callback);
void addConsoleActionF(char *token, VoidFloat callback);
void addConsoleActionS(char *token, VoidCharPtr callback);
void addConsoleActionSSS(char *token, VoidCharPtrCharPtrCharPtr callback);

#endif /* RFICONSOLE_H_ */
