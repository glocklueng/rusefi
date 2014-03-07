/**
 * @file	error_handling.h
 *
 * @date Mar 6, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ERROR_HANDLING_H_
#define ERROR_HANDLING_H_

int warning(const char *fmt, ...);
void firmwareError(const char *fmt, ...);

int hasFatalError(void);
void fatal3(char *msg, char *file, int line);
#define fatal(x) (fatal3(x, __FILE__, __LINE__));

#endif /* ERROR_HANDLING_H_ */
