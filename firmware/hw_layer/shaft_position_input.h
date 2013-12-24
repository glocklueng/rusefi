/**
 * @file	shaft_position_input.h
 * @brief	Position sensor hardware layer
 *
 * @date Dec 30, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef CRANK_INPUT_H_
#define CRANK_INPUT_H_

#include "main.h"
#include "trigger_structure.h"

typedef void (*ShaftPositionListener)(ShaftEvents signal, int index);

void initShaftPositionInputCapture(void);
void registerShaftPositionListener(ShaftPositionListener handler, char *msg);
int getCrankEventCounter(void);
int isSignalDecoderError(void);

#endif /* CRANK_INPUT_H_ */
