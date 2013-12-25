/**
 * @file	toothed_wheel_emulator.h
 * @brief	Missing-tooth wheel signal emulator
 *
 * @date Nov 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef TOOTHED_WHEEL_EMULATOR_H_
#define TOOTHED_WHEEL_EMULATOR_H_

#include "dist_emulator.h"

void skippedToothTriggerShape(trigger_shape_s *s, int totalTeethCount, int skippedCount);

#endif /* TOOTHED_WHEEL_EMULATOR_H_ */
