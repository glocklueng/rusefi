/**
 * @file    pwm_generator_logic.h
 *
 * @date Mar 2, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef PWM_GENERATOR_LOGIC_H_
#define PWM_GENERATOR_LOGIC_H_

#include "global.h"
#include "EfiWave.h"
#include "io_pins.h"
#include "scheduler.h"
#include "efiGpio.h"

typedef struct {
	/**
	 * a copy so that all phases are executed on the same period, even if another thread
	 * would be adjusting PWM parameters
	 */
	float periodNt;
	/**
	 * Iteration counter
	 */
	int iteration;
	/**
	 * Start time of current iteration
	 */
	uint64_t startNt;
	int phaseIndex;
} pwm_config_safe_state_s;

class PwmConfig;

typedef void (pwm_cycle_callback)(PwmConfig *state);
typedef void (pwm_gen_callback)(PwmConfig *state, int stateIndex);

/**
 * @brief   Multi-channel software PWM output configuration
 */
class PwmConfig {
public:
	PwmConfig();
	PwmConfig(float *switchTimes, single_wave_s *waves);
	void baseConstructor();
	void init(float *switchTimes, single_wave_s *waves);

	void weComplexInit(const char *msg,
			int phaseCount, float *swithcTimes, int waveCount, pin_state_t **pinStates,
			pwm_cycle_callback *cycleCallback,
			pwm_gen_callback *callback);


	void handleCycleStart();


	OutputPin *outputPins[PWM_PHASE_MAX_WAVE_PER_PWM];
	multi_wave_s multiWave;
	/**
	 * float value of PWM period
	 * PWM generation is not happening while this value is zero
	 */
	float periodNt;

	scheduling_s scheduling;

	pwm_config_safe_state_s safe;
	/**
	 * Number of events in the cycle
	 */
	int phaseCount;

	/**
	 * this callback is invoked before each wave generation cycle
	 */
	pwm_cycle_callback *cycleCallback;

	/**
	 * this main callback is invoked when it's time to switch level on amy of the output channels
	 */
	pwm_gen_callback *stateChangeCallback;
};


class SimplePwm : public PwmConfig {
public:
	SimplePwm();
	void setSimplePwmDutyCycle(float dutyCycle);
	pin_state_t pinStates[2];
	single_wave_s sr[1];
	float _switchTimes[2];
private:
	single_wave_s waveInstance;
};

void copyPwmParameters(PwmConfig *state, int phaseCount, float *switchTimes,
		int waveCount, pin_state_t **pinStates);

#endif /* PWM_GENERATOR_LOGIC_H_ */
