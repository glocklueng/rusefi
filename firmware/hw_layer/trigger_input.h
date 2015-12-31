/**
 * @file	trigger_input.h
 * @brief	Position sensor hardware layer
 *
 * @date Dec 30, 2012
 * @author Andrey Belomutskiy, (c) 2012-2016
 */

#ifndef CRANK_INPUT_H_
#define CRANK_INPUT_H_

#include "engine.h"

void turnOnTriggerInputPins(Logging *sharedLogger);
void applyNewTriggerInputPins(void);

#endif /* CRANK_INPUT_H_ */
