/**
 * @file	rusefi.h
 *
 * @date Dec 25, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef RUSEFI_H_
#define RUSEFI_H_

void runRusEfi(void);
int getVersion(void);
void scheduleReset(void);

// todo: extract this into a separate 'error_handling.h'?
void firmwareError(const char *fmt, ...);

#endif /* RUSEFI_H_ */
