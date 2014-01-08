/**
 * @file    dist_emulator.c
 * @brief   Position sensor(s) emulation code
 *
 * This file is mostly about initialization, the configuration is
 * provided by the configureShaftPositionEmulatorShape method
 *
 * @date Dec 9, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "dist_emulator.h"
#include "rficonsole.h"
#include "main_loop.h"
#include "datalogging.h"
#include "pinout.h"
#include "engine_configuration.h"

extern EngineConfiguration *engineConfiguration;
extern EngineConfiguration2 *engineConfiguration2;

static Logging logger;
static volatile int deRpm = 0; // distributor RPM is camshaft RPM

#if defined __GNUC__
static PwmConfig configuration __attribute__((section(".ccm")));
#else
static PwmConfig configuration;
#endif

void setRevolutionPeriod(int value) {
	deRpm = (int)(value * engineConfiguration2->rpmMultiplier);
	myfloat gRpm = deRpm / 60.0; // per minute converted to per second
	if (gRpm == 0) {
		configuration.period = 0;
	} else {
		configuration.period = frequency2period(gRpm);
	}
	scheduleSimpleMsg(&logger, "Emulating position sensor(s). RPM=", value);
}

void triggerShapeInit(trigger_shape_s *trigger) {
	trigger->size = 0;
}

void triggerAddEvent(trigger_shape_s *trigger, float angle, trigger_wheel_e waveIndex, int state) {
	angle /= 720;
	if (trigger->size == 0) {
		trigger->size = 1;
		for (int i = 0; i < PWM_PHASE_MAX_WAVE_PER_PWM; i++)
			trigger->wave.waves[i].pinStates[0] = 0;

		trigger->wave.switchTimes[0] = angle;
		trigger->wave.waves[waveIndex].pinStates[0] = state;
		return;
	}

//	if(angle!=trigger->wave.switchTimes[trigger->currentIndex])

	int index = trigger->size++;

	for (int i = 0; i < PWM_PHASE_MAX_WAVE_PER_PWM; i++)
		trigger->wave.waves[i].pinStates[index] = trigger->wave.waves[i].pinStates[index - 1];
	trigger->wave.switchTimes[index] = angle;
	trigger->wave.waves[waveIndex].pinStates[index] = state;
}

void initShaftPositionEmulator(void) {
#if EFI_EMULATE_POSITION_SENSORS
	print("Emulating %s\r\n", getConfigurationName(engineConfiguration));

	initLogging(&logger, "position sensor(s) emulator");

	initOutputPin("distributor ch1", &configuration.outputPins[0],
	PRIMARY_SHAFT_POSITION_EMULATION_PORT, PRIMARY_SHAFT_POSITION_EMULATION_PIN);

	initOutputPin("distributor ch2", &configuration.outputPins[1],
	SECONDARY_SHAFT_POSITION_EMULATION_PORT, SECONDARY_SHAFT_POSITION_EMULATION_PIN);

	trigger_shape_s *s = &engineConfiguration2->triggerShape;

	int *pinStates[2] = {s->wave.waves[0].pinStates, s->wave.waves[1].pinStates};
	weComplexInit("position sensor", &configuration, 0, s->size, s->wave.switchTimes, 2, pinStates);


	setRevolutionPeriod(DEFAULT_EMULATION_RPM);

	addConsoleActionI("rpm", &setRevolutionPeriod);

#else
	print("No position sensor(s) emulation\r\n");
#endif /* EFI_EMULATE_POSITION_SENSORS */
}
