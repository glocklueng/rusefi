/**
 * @file	trigger_structure.h
 *
 * @date Dec 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef TRIGGER_STRUCTURE_H_
#define TRIGGER_STRUCTURE_H_

#include "pwm_generator.h"

typedef enum {
	T_PRIMARY = 0,
	T_SECONDARY = 1
} trigger_wheel_e;

typedef struct {
	multi_wave_s wave;
	int size;
} trigger_shape_s;

#endif /* TRIGGER_STRUCTURE_H_ */
