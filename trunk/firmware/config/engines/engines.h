/*
 * engine.h
 *
 * @date Aug 30, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "boards.h"
#include "features.h"

typedef enum {
	AUDI_AAN = 1,
	DODGE_NEON_1995 = 2,
	/**
	 * 1996 1.3 Ford Aspire
	 * http://rusefi.com/forum/viewtopic.php?t=375
	 */
#if EFI_SUPPORT_FORD_ASPIRE
	FORD_ASPIRE_1996 = 3,
#endif /* EFI_SUPPORT_FORD_ASPIRE */
	FORD_FIESTA = 4,
	NISSAN_PRIMERA = 5,
} engine_type_e;

/**
 * 1995 Dodge Neon
 * http://rusefi.com/forum/viewtopic.php?t=360
 */
//#define EFI_ENGINE_DODGE_NEON TRUE

#define EFI_ENGINE_FORD_ASPIRE TRUE

/**
 * 36-1 toothed wheel engine
 * http://rusefi.com/forum/viewtopic.php?t=282
 */
//#define EFI_ENGINE_FORD_FIESTA TRUE

//#define EFI_ENGINE_SNOW_BLOWER TRUE

/**
 * 5 cylinder engine!
 */
//#define EFI_ENGINE_AUDI_AAN TRUE

/**
 * 60-2 toothed wheel engine
 */
//#define EFI_ENGINE_DENISVAK TRUE

#endif /* ENGINE_H_ */
