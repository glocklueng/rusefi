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

#include "efifeatures.h"

// todo: implement a function to work with times considering counter overflow
#define overflowDiff(now, time) ((now) - (time))

#endif /* EFITIME_H_ */
