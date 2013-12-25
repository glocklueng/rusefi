/**
 * @file    dist_emulator.h
 * @brief   Position sensor(s) emulation header
 *
 * @date Dec 9, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef DIST_EMULATOR_H_
#define DIST_EMULATOR_H_

#include "main.h"
#include "wave_math.h"

#include "trigger_structure.h"
#include "engine_configuration.h"

void triggerShapeInit(trigger_shape_s *trigger);
void triggerAddEvent(trigger_shape_s *trigger, float angle, trigger_wheel_e waveIndex, int state);

/**
 * this is RPM. 10000 rpm is only 166Hz, 800 rpm is 13Hz
 */
#define DEFAULT_EMULATION_RPM 1200

void initShaftPositionEmulator(void);
void setRevolutionPeriod(int value);

#if EFI_EMULATE_POSITION_SENSORS
void configureShaftPositionEmulatorShape(PwmConfig *state, EngineConfiguration2 * engineConfiguration2);
#endif /* EFI_EMULATE_POSITION_SENSORS */

#endif /* DIST_EMULATOR_H_ */
