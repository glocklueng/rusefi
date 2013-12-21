/**
 * @file	dodge_neon.h
 * @brief	1995 Dodge Neon default engine configuration
 *
 * @date Dec 16, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef DODGE_NEON_H_
#define DODGE_NEON_H_

#if EFI_ENGINE_DODGE_NEON

#define EFI_DEFAULT_CHART_SIZE 90

#define EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR TRUE

#define NUMBER_OF_CYLINDERS 4

#define EFI_SHAFT_POSTION_NEEDS_SECONDARY TRUE

// that's a temporary arrangement
#define TOTAL_TEETH_COUNT 3
#define SKIPPED_TEETH_COUNT 1


#define EFI_ENGINE_ID "Dodge Neon"

#endif /* EFI_ENGINE_DODGE_NEON */

#endif /* DODGE_NEON_H_ */
