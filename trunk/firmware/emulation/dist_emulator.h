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
#include "pwm_generator.h"

typedef enum {
	T_PRIMARY = 0,
	T_SECONDARY = 1
} trigger_wheel_e;

typedef struct {
	multi_wave_s wave;
	int currentIndex;
} trigger_simulator_s;

void triggerSimulatorInit(trigger_simulator_s *trigger);
void triggerAddEvent(trigger_simulator_s *trigger, float angle, trigger_wheel_e waveIndex, int state);

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
