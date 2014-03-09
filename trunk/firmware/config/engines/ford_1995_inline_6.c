/**
 * @file ford_1995_inline_6.c
 * @brief Default engine configuration for a 1995 Ford inline 6 engine
 *
 * http://rusefi.com/forum/viewtopic.php?f=3&t=469
 *
 * @date Feb 12, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "ford_1995_inline_6.h"
#include "engine_math.h"

#if EFI_SUPPORT_1995_FORD_INLINE_6 || defined(__DOXYGEN__)

/**
 * @brief Default values for persistent properties
 */
void setFordInline6(engine_configuration_s *engineConfiguration) {
	engineConfiguration->cylindersCount = 6;

	/**
	 * 0.5 means primary position sensor is on a camshaft
	 */
	engineConfiguration->rpmMultiplier = 0.5;

	engineConfiguration->ignitionMode = IM_ONE_COIL;
	engineConfiguration->firingOrder = FO_1_THEN_5_THEN_3_THEN_6_THEN_2_THEN_4;

	/**
	 * 0.5ms dweel time just to be sure it would fit within camshaft revolution, dwell is not controlled by us anyway
	 */
	setConstantDwell(engineConfiguration, 0.5);

	/**
	 * We treat the trigger as 3/0 toothed wheel
	 */
	engineConfiguration->triggerConfig.totalToothCount = 3;
	engineConfiguration->triggerConfig.skippedToothCount = 0;
	engineConfiguration->triggerConfig.isSynchronizationNeeded = FALSE;
	engineConfiguration->triggerConfig.useRiseEdge = TRUE;
	engineConfiguration->needSecondTriggerInput = FALSE;
}

/**
 * @brief These settings are not persistent yet
 */
void setFordInline6_2(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2) {
	initializeIgnitionActions(engineConfiguration, engineConfiguration2);
}

#endif /* EFI_SUPPORT_1995_FORD_INLINE_6 */
