/*
 * engine_status.h
 *
 *  Created on: Feb 7, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_STATUS_H_
#define ENGINE_STATUS_H_

#include "global.h"

int isCranking(void);
int findIndex(myfloat array[], int size, float value);
void initEngineContoller(void);

#endif /* ENGINE_STATUS_H_ */
