/**
 * @file	ford_fiesta.cpp
 * @brief	European 1990 Ford Fiesta
 *
 * FORD_FIESTA = 4
 * set_engine_type 4
 *
 * @date Nov 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "main.h"

#if EFI_SUPPORT_FORD_FIESTA || defined(__DOXYGEN__)

#include "ford_fiesta.h"
#include "engine_math.h"

EXTERN_ENGINE;

void setFordFiestaDefaultEngineConfiguration(DECLARE_ENGINE_PARAMETER_F) {
	engineConfiguration->rpmHardLimit = 7000;
	setOperationMode(engineConfiguration, FOUR_STROKE_CRANK_SENSOR);

	engineConfiguration->trigger.type = TT_TOOTHED_WHEEL_36_1;

	engineConfiguration->ignitionMode = IM_WASTED_SPARK;
	engineConfiguration->specs.firingOrder = FO_1_THEN_3_THEN_4_THEN2;
	engineConfiguration->hasMafSensor = true;
	engineConfiguration->mafAdcChannel = EFI_ADC_NONE;


	// etb testing
//	boardConfiguration->clutchUpPin
	boardConfiguration->etbControlPin1 = GPIOD_3;
	engineConfiguration->pedalPositionChannel = EFI_ADC_1;

	engineConfiguration->tpsMin = 337;
	engineConfiguration->tpsMax = 896;
}

#endif /* EFI_SUPPORT_FORD_FIESTA */
