/*
 * fuel_map.h
 *
 *  Created on: May 27, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef FUEL_MAP_H_
#define FUEL_MAP_H_

void prepareFuelMap(void);

float getBaseFuel(int rpm, float key);
float getIatCorrection(float iat);
float getInjectorLag(float vBatt);
float getCltCorrection(float clt);
float getFuel(int rpm, float key);

#define FUEL_RPM_COUNT 23
#define FUEL_MAF_COUNT 33

#endif /* FUEL_MAP_H_ */
