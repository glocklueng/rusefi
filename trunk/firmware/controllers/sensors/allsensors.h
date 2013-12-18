/**
 * @file    allsensors.h
 * @brief
 *
 * This file should have been called 'sensors.h' but there is some conflict
 * with standard win32 header :(
 *
 *
 * @date Nov 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include "main.h"
#include "tps.h"
#include "map.h"
#include "maf.h"
#include "ego.h"
#include "voltage.h"
#include "thermistors.h"

void initSensors(void);
#endif /*SENSORS_H_*/
