/**
 * @file efitime.h
 *
 * By the way, there are 86400000 milliseconds in a day
 *
 * @date Apr 14, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef EFITIME_H_
#define EFITIME_H_

#include <stdint.h>
#include "efifeatures.h"

/**
 * integer time in milliseconds
 * 32 bit 4B / 1000 = 4M seconds = 1111.11 hours = 46 days.
 * Please restart your ECU every 46 days? :)
 */
typedef uint32_t efitimems_t;

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

// todo: implement a function to work with times considering counter overflow
#define overflowDiff(now, time) ((now) - (time))

/**
 * 64-bit counter of microseconds (1/1 000 000 of a second) since MCU reset
 *
 * By using 64 bit, we can achive a very precise timestamp which does not overflow.
 * The primary implementation counts the number of CPU cycles from MCU reset.
 */
uint64_t getTimeNowUs(void);

efitimems_t getTimeNowMs(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EFITIME_H_ */
