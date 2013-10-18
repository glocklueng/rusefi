/*
 *  Created on: Sep 8, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    snow_blower.h
 */

#ifndef SNOW_BLOWER_H_
#define SNOW_BLOWER_H_

#if EFI_ENGINE_SNOW_BLOWER

#define ENGINE_CRANKING_RPM 400

#define NUMBER_OF_CYLINDERS 1

#define EFI_ENGINE_ID "Snow Blower"

#define RPM_MULT (1)

#define getCoolantTemperature() 0
#define getIntakeAirTemperature() 0

#define getMaf() 0
#define getTPS() 0
#define getAfr() 0

#endif /* EFI_ENGINE_SNOW_BLOWER */

#endif /* SNOW_BLOWER_H_ */
