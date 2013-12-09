/*
 * @file	console_loop.h
 *
 * @date Mar 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef CONSOLE_LOOP_H_
#define CONSOLE_LOOP_H_

void initStatusLoop(void);
void printState(void);
void setFullLog(int value);
void sayOsHello(void);
int hasFatalError(void);

#endif /* CONSOLE_LOOP_H_ */
