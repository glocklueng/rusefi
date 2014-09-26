/**
 * @file    trigger_emulator.cpp
 * @brief   Position sensor(s) emulation code
 *
 * This file is mostly about initialization, the configuration is
 * provided by the configureShaftPositionEmulatorShape method
 *
 * @date Dec 9, 2012
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "trigger_emulator.h"
#include "eficonsole.h"
#include "main_trigger_callback.h"
#include "datalogging.h"
#include "engine_configuration.h"
#if EFI_PROD_CODE
#include "pwm_generator.h"
#include "pin_repository.h"
#endif
#include "io_pins.h"
#include "trigger_emulator_algo.h"
#include "trigger_central.h"

extern engine_configuration_s *engineConfiguration;
extern board_configuration_s *boardConfiguration;

extern PwmConfig triggerSignal;

void initTriggerEmulator(void) {
#if EFI_EMULATE_POSITION_SENSORS || defined(__DOXYGEN__)
	print("Emulating %s\r\n", getConfigurationName(engineConfiguration->engineType));

	triggerSignal.outputPins[0] = TRIGGER_EMULATOR_PRIMARY;
	triggerSignal.outputPins[1] = TRIGGER_EMULATOR_SECONDARY;
	triggerSignal.outputPins[2] = TRIGGER_EMULATOR_3RD;

#if EFI_PROD_CODE
	// todo: refactor, make this a loop
	outputPinRegisterExt2("distributor ch1", triggerSignal.outputPins[0], boardConfiguration->triggerSimulatorPins[0],
			&boardConfiguration->triggerSimulatorPinModes[0]);

	outputPinRegisterExt2("distributor ch2", triggerSignal.outputPins[1], boardConfiguration->triggerSimulatorPins[1],
			&boardConfiguration->triggerSimulatorPinModes[1]);

	outputPinRegisterExt2("distributor ch3", triggerSignal.outputPins[2], boardConfiguration->triggerSimulatorPins[2],
			&boardConfiguration->triggerSimulatorPinModes[2]);
#endif /* EFI_PROD_CODE */

	initTriggerEmulatorLogic();
#else
	print("No position sensor(s) emulation\r\n");
#endif /* EFI_EMULATE_POSITION_SENSORS */
}
