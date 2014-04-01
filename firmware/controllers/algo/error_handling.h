/**
 * @file	error_handling.h
 *
 * @date Mar 6, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ERROR_HANDLING_H_
#define ERROR_HANDLING_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

//#include "obd_error_codes.h"

/**
 * Something is wrong, but we can live with it: some minor sensor is disconnected
 * or something like that
 *
 */
int warning(const char *fmt, ...);
/**
 * Something really bad had happened - firmware cannot function
 *
 * todo: better method name?
 */
void firmwareError(const char *fmt, ...);

int hasFatalError(void);
void fatal3(char *msg, char *file, int line);
#define fatal(x) (fatal3(x, __FILE__, __LINE__));

void initErrorHandling(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* ERROR_HANDLING_H_ */
