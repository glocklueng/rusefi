/**
 * @file	dodge_neon.c
 *
 * @date Dec 16, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

#if EFI_ENGINE_DODGE_NEON

#include "dodge_neon.h"
#include "engine_configuration.h"
#include "main_loop.h"

extern EngineConfiguration2 engineConfiguration2;

void configureShaftPositionEmulatorShape(PwmConfig *state) {

	float x = 90.0;

	float y1 = 110;
	float y2 = 110 + 360;
	float z = 5;

	myfloat switchTimes[] = { x / 720 ,

			y1 / 720, (y1  + 1 * z)/ 720, (y1  + 2 * z)/ 720, (y1  + 3 * z)/ 720, (y1  + 4 * z)/ 720, (y1  + 5 * z)/ 720, (y1  + 6 * z)/ 720, (y1  + 7 * z)/ 720,
			/* TDC 2 - 180 */


			(x + 210) / 720, (x + 360 ) / 720,

			y2 / 720, (y2  + 1 * z)/ 720, (y2  + 2 * z)/ 720, (y2  + 3 * z)/ 720, (y2  + 4 * z)/ 720, (y2  + 5 * z)/ 720, (y2  + 6 * z)/ 720, (y2  + 7 * z)/ 720,

			/* TDC 2 - 180 */


			(x + 510) / 720, 1 };

	int pinStates0[] = { 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			/* TDC 2 - 180 */
			0, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			/* TDC 2 - 180 */
			0, 0};


	int pinStates1[] = { 0,
			1, 0, 1, 0, 1, 0, 1, 0,
			/* TDC 2 - 180 */
			0, 0,
			1, 0, 1, 0, 1, 0, 1, 0,
			/* TDC 2 - 180 */
			0, 0

	} ;

	int *pinStates[2] = { pinStates0, pinStates1 };

	weComplexInit("distributor", state, 0, 21, switchTimes, 2, pinStates);
}

void setDefaultEngineConfiguration(EngineConfiguration *engineConfiguration) {
	engineConfiguration->rpmHardLimit = 7000;

	engineConfiguration2.shaftPositionEventCount = ((TOTAL_TEETH_COUNT - SKIPPED_TEETH_COUNT) * 2);
}

void configureEngineEventHandler(EventHandlerConfiguration *config) {
	resetEventList(&config->crankingInjectionEvents);

}

#endif /* EFI_ENGINE_DODGE_NEON */

