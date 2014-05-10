/**
 * @file ford_1995_inline_6.c
 * @brief Default engine configuration for a 1995 Ford inline 6 engine
 *
 * http://rusefi.com/forum/viewtopic.php?f=3&t=469
 *
 * FORD_INLINE_6_1995 = 7
 *
 * @date Feb 12, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "ford_1995_inline_6.h"
#include "engine_math.h"
#include "allsensors.h"

#if EFI_SUPPORT_1995_FORD_INLINE_6 || defined(__DOXYGEN__)

/**
 * @brief Default values for persistent properties
 */
void setFordInline6(engine_configuration_s *engineConfiguration, board_configuration_s *boardConfiguration) {
	engineConfiguration->cylindersCount = 6;

	/**
	 * 0.5 means primary position sensor is on a camshaft
	 */
	engineConfiguration->rpmMultiplier = 0.5;

	engineConfiguration->ignitionMode = IM_ONE_COIL;
	engineConfiguration->firingOrder = FO_1_THEN_5_THEN_3_THEN_6_THEN_2_THEN_4;
	engineConfiguration->crankingInjectionMode = IM_SIMULTANEOUS;
	engineConfiguration->injectionMode = IM_BATCH;

	/**
	 * 0.5ms dweel time just to be sure it would fit within camshaft revolution, dwell is not controlled by us anyway
	 */
	setConstantDwell(engineConfiguration, 0.5);

	/**
	 * We treat the trigger as 6/0 toothed wheel
	 */
	engineConfiguration->triggerConfig.totalToothCount = 6;
	engineConfiguration->triggerConfig.skippedToothCount = 0;
	engineConfiguration->triggerConfig.isSynchronizationNeeded = FALSE;
	engineConfiguration->triggerConfig.useRiseEdge = TRUE;
	engineConfiguration->needSecondTriggerInput = FALSE;

	engineConfiguration->globalTriggerAngleOffset = 0;
	engineConfiguration->ignitionOffset = 13;


	setThermistorConfiguration(&engineConfiguration->cltThermistorConf, -10, 160310, 60, 7700, 120.00, 1180);
	engineConfiguration->cltThermistorConf.bias_resistor = 2700;

	setThermistorConfiguration(&engineConfiguration->iatThermistorConf, -10, 160310, 60, 7700, 120.00, 1180);
	engineConfiguration->iatThermistorConf.bias_resistor = 2700;

	// 12ch analog board pinout:
	// input channel 3 is PA7, that's ADC7
	// input channel 5 is PA4, that's ADC4
	// input channel 6 is PA3, that's ADC3
	// input channel 7 is PA2, that's ADC2
	// input channel 8 is PA1, that's ADC1
	// input channel 9 is PA0, that's ADC0
	// input channel 10 is PC3, that's ADC13
	// input channel 12 is PC1, that's ADC11

	engineConfiguration->tpsAdcChannel = 4;
	engineConfiguration->iatAdcChannel = 2;
	engineConfiguration->cltAdcChannel = 1;
	engineConfiguration->afrSensor.afrAdcChannel = 11;

	// 6 channel output board
	// output 1 is PB9
	// output 3 is PE3
	// output 5 is PC13
	// output 6 is PC15

	boardConfiguration->fuelPumpPin = GPIOC_13;
	boardConfiguration->injectionPins[0] = GPIOB_9;
	boardConfiguration->injectionPins[1] = GPIOE_3;
	boardConfiguration->ignitionPins[0] = GPIOC_15;

	boardConfiguration->injectionPins[2] = GPIO_NONE;
	boardConfiguration->fanPin = GPIO_NONE;

	engineConfiguration->tpsMin = convertVoltageTo10bitADC(1.250);
	engineConfiguration->tpsMax = convertVoltageTo10bitADC(4.538);

	engineConfiguration->map.sensor.mapType = MT_MPX4250;
	engineConfiguration->map.sensor.hwChannel = 2; // input channel 8 is ADC2

	//	engineConfiguration->vBattAdcChannel = 0; //
//	engineConfiguration->mafAdcChannel = 1;

}

#endif /* EFI_SUPPORT_1995_FORD_INLINE_6 */
