/**
 * @file	trigger_structure.h
 *
 * @date Dec 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef TRIGGER_STRUCTURE_H_
#define TRIGGER_STRUCTURE_H_

#define PWM_PHASE_MAX_COUNT 150
#define PWM_PHASE_MAX_WAVE_PER_PWM 2


/**
 * @brief   PWM configuration for the specific output pin
 */
typedef struct {
	int pinStates[PWM_PHASE_MAX_COUNT];
} single_wave_s;

typedef struct {
	/**
	 * Number of events in the cycle
	 */
	int phaseCount;
	/**
	 * Number of signal wires
	 */
	int waveCount;
	single_wave_s waves[PWM_PHASE_MAX_WAVE_PER_PWM];
	/**
	 * values in the (0..1] range which refer to points within the period at at which pin state should be changed
	 * So, in the simplest case we turn pin off at 0.3 and turn it on at 1 - that would give us a 70% duty cycle PWM
	 */
	myfloat switchTimes[PWM_PHASE_MAX_COUNT];
} multi_wave_s;


typedef enum {
	T_PRIMARY = 0,
	T_SECONDARY = 1
} trigger_wheel_e;

typedef struct {
	multi_wave_s wave;
	int size;
} trigger_shape_s;

#endif /* TRIGGER_STRUCTURE_H_ */
