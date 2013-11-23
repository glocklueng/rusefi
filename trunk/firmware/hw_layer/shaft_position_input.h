/**
 * @file	shaft_position_input.h
 * @brief	Position sensor hardware layer
 *
 *  Created on: Dec 30, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef CRANK_INPUT_H_
#define CRANK_INPUT_H_

#include "main.h"
#include "ckp_events.h"

typedef struct {
	/**
	 * TRUE if we know where we are
	 */
	unsigned char shaft_is_synchronized;

	int current_index;

#if EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR
	int toothed_previous_duration;
//	int toothed_current_duration;
	int toothed_previous_time;


#endif


} ShaftPositionState;

typedef void (*ShaftPositionListener)(ShaftEvents signal, int index);

void initShaftPositionInputCapture(void);
void registerShaftPositionListener(ShaftPositionListener handler, char *msg);
int getCrankEventCounter(void);

#endif /* CRANK_INPUT_H_ */
