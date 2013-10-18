/*
 * engine.h
 *
 *  Created on: Aug 30, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "features.h"

#if EFI_ENGINE_DENISVAK
#include "denisvak_mcu.h"
#endif

#if EFI_ENGINE_FORD_ASPIRE
#include "ford_aspire_mcu.h"
#endif

#if EFI_ENGINE_SNOW_BLOWER
#include "snow_blower_mcu.h"
#endif

#endif /* ENGINE_H_ */
