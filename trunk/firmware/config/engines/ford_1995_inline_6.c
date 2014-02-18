/*
 * @file ford_1995_inline_6.c
 *
 * http://rusefi.com/forum/viewtopic.php?f=3&t=469
 *
 * @date Feb 12, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "ford_1995_inline_6.h"
#include "trigger_decoder.h"
#include "engine_math.h"

#if EFI_SUPPORT_1995_FORD_INLINE_6

extern engine_configuration_s *engineConfiguration;

void setFordInline6(engine_configuration_s *engineConfiguration) {
	engineConfiguration->cylindersCount = 6;

	/**
	 * we have a sensor on the camshaft, so rpmMultiplier == 2
	 */
	engineConfiguration->rpmMultiplier = 2;

	engineConfiguration->ignitionMode = IM_ONE_COIL;
	engineConfiguration->firingOrder = FO_1_THEN_5_THEN_3_THEN_6_THEN_2_THEN_4;

	setConstantDwell(engineConfiguration, 0.5);
}

void setFordInline6_2(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2) {
	initializeIgnitionActions(engineConfiguration, engineConfiguration2);

	skippedToothTriggerShapeExt(engineConfiguration2, 6, 0);
	engineConfiguration2->triggerShape.useRiseEdge = TRUE;
	engineConfiguration2->triggerShape.onlyOneTeeth = TRUE;
}

#endif /* EFI_SUPPORT_1995_FORD_INLINE_6 */
