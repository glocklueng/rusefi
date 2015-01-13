/**
 * @file efitime.h
 *
 * By the way, there are 86400000 milliseconds in a day
 *
 * @date Apr 14, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef EFITIME_H_
#define EFITIME_H_

#include <stdint.h>
#include "efifeatures.h"
#include "rusefi_types.h"

#define US_PER_SECOND 1000000
#define US_PER_SECOND_LL 1000000LL

#define MS2US(MS_TIME) ((MS_TIME) * 1000)

#define US_TO_TI_TEMP 10

// todo: implement a function to work with times considering counter overflow
#define overflowDiff(now, time) ((now) - (time))

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/**
 * 64-bit counter of microseconds (1/1 000 000 of a second) since MCU reset
 *
 * By using 64 bit, we can achieve a very precise timestamp which does not overflow.
 * The primary implementation counts the number of CPU cycles from MCU reset.
 *
 * WARNING: you should use getTimeNowNt where possible for performance reasons.
 * The heaviest part is '__aeabi_ildivmod' - non-native 64 bit division
 */
efitimeus_t getTimeNowUs(void);

/**
 * 64-bit counter CPU cycles since MCU reset
 */
efitick_t getTimeNowNt(void);

uint64_t getHalTimer(void);

/**
 * @brief   Returns the number of milliseconds since the board initialization.
 */
efitimems_t currentTimeMillis(void);

/**
 * @brief   Current system time in seconds.
 */
int getTimeNowSeconds(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EFITIME_H_ */
