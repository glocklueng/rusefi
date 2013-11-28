/**
 * @file    dist_emulator.h
 * @brief   Position sensor(s) emulation header
 *
 *  Created on: Dec 9, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef DIST_EMULATOR_H_
#define DIST_EMULATOR_H_

#include "main.h"
#include "wave_math.h"
#include "pwm_generator.h"

/**
 * this is RPM. 10000 rpm is only 166Hz, 800 rpm is 13Hz
 */
#define DEFAULT_EMULATION_RPM 1200

void initShaftPositionEmulator(void);
void setRevolutionPeriod(int value);

#if EFI_EMULATE_POSITION_SENSORS
void configureShaftPositionEmulatorShape(PwmConfig *state);
#endif /* EFI_EMULATE_POSITION_SENSORS */

#endif /* DIST_EMULATOR_H_ */
