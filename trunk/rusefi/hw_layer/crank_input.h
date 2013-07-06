/*
 * chibi_input_capture.h
 *
 *  Created on: Dec 30, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef CRANK_INPUT_H_
#define CRANK_INPUT_H_

#include "main.h"
#include "listener_array.h"

void initInputCapture(void);
void registerCkpListener(IntListener handler, char *msg);
int getCrankEventCounter(void);

#endif /* CRANK_INPUT_H_ */
