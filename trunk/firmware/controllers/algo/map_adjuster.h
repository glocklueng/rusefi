/*
 * map_adjuster.h
 *
 *  Created on: Jul 23, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef MAP_ADJUSTER_H_
#define MAP_ADJUSTER_H_

void initMapAdjuster(void);
int runMapAdjustments(void (*callback)(int, float, float));

void addAfr(int rpm, float key, float afr);
float getMultiplier(int rpm, float key);

#endif /* MAP_ADJUSTER_H_ */
