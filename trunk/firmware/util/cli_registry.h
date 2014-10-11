/**
 * @file    cli_registry.h
 * @brief   Command-line interface commands registry
 *
 * @date Nov 15, 2012
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef RFICONSOLE_LOGIC_H_
#define RFICONSOLE_LOGIC_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define CONSOLE_MAX_ACTIONS 128

typedef enum {
	NO_PARAMETER,
	NO_PARAMETER_P,
	ONE_PARAMETER,
	FLOAT_PARAMETER,
	STRING_PARAMETER,
	STRING2_PARAMETER,
	STRING2_PARAMETER_P,
	STRING3_PARAMETER,
	STRING5_PARAMETER,
	TWO_INTS_PARAMETER,
	TWO_INTS_PARAMETER_P,
	FLOAT_FLOAT_PARAMETER,
	FLOAT_FLOAT_PARAMETER_P,
} action_type_e;

typedef struct {
	const char *token;
	action_type_e parameterType;
	void (*callback)(void);
	void *param;
} TokenCallback;

//void addDefaultConsoleActions(void);
//void handleActionWithParameter(TokenCallback *current, char *parameter);
int tokenLength(const char *msgp);

typedef void (*VoidPtr)(void*);


typedef void (*Void)(void);
typedef void (*VoidInt)(int);
typedef void (*VoidFloat)(float);
typedef void (*VoidFloatFloat)(float, float);
typedef void (*VoidIntInt)(int, int);
typedef void (*VoidCharPtr)(const char *);

typedef void (*VoidCharPtrCharPtr)(const char *, const char *);
typedef void (*VoidCharPtrCharPtrVoidPtr)(const char *, const char *, void*);

typedef void (*VoidCharPtrCharPtrCharPtr)(const char *, const char *, const char *);
typedef void (*VoidCharPtrCharPtrCharPtrCharPtrCharPtr)(const char *, const char *, const char *, const char *, const char *);

char *validateSecureLine(char *line);
void resetConsoleActions(void);
void helpCommand(void);
void initConsoleLogic(void);
void handleConsoleLine(char *line);
int findEndOfToken(const char *line);


void addConsoleAction(const char *token, Void callback);
void addConsoleActionP(const char *token, VoidPtr callback, void *param);

void addConsoleActionI(const char *token, VoidInt callback);
void addConsoleActionII(const char *token, VoidIntInt callback);
void addConsoleActionF(const char *token, VoidFloat callback);
void addConsoleActionFF(const char *token, VoidFloatFloat callback);
void addConsoleActionS(const char *token, VoidCharPtr callback);

void addConsoleActionSS(const char *token, VoidCharPtrCharPtr callback);
void addConsoleActionSSP(const char *token, VoidCharPtrCharPtrVoidPtr callback, void *param);

void addConsoleActionSSS(const char *token, VoidCharPtrCharPtrCharPtr callback);
void addConsoleActionSSSSS(const char *token, VoidCharPtrCharPtrCharPtrCharPtrCharPtr callback);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RFICONSOLE_H_ */
