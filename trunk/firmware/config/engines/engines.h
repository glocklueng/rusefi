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
#if EFI_SUPPORT_DODGE_NEON
	/**
	 * 1995 Dodge Neon
	 * http://rusefi.com/forum/viewtopic.php?t=360
	 */
	DODGE_NEON_1995 = 2,
#endif /* EFI_SUPPORT_DODGE_NEON */
#if EFI_SUPPORT_FORD_ASPIRE
	/**
	 * 1996 1.3 Ford Aspire
	 * http://rusefi.com/forum/viewtopic.php?t=375
	 */
	FORD_ASPIRE_1996 = 3,
#endif /* EFI_SUPPORT_FORD_ASPIRE */
#if EFI_SUPPORT_FORD_FIESTA
	/**
	 * 36-1 toothed wheel engine
	 * http://rusefi.com/forum/viewtopic.php?t=282
	 */
	FORD_FIESTA = 4,
#endif /* EFI_SUPPORT_FORD_FIESTA */
#if EFI_SUPPORT_NISSAN_PRIMERA
	NISSAN_PRIMERA = 5,
#endif /* EFI_SUPPORT_NISSAN_PRIMERA */
} engine_type_e;

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
