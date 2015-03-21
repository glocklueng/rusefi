/**
 * @file	sachs.cpp
 *
 * set_engine_type 29
 * http://rusefi.com/forum/viewtopic.php?f=3&t=396
 *
 * @date Jan 26, 2015
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "sachs.h"
#include "allsensors.h"

void setSachs(engine_configuration_s *engineConfiguration) {
	engineConfiguration->specs.displacement = 0.1; // 100cc
	engineConfiguration->specs.cylindersCount = 1;
	engineConfiguration->engineCycle = 360;

	engineConfiguration->specs.firingOrder = FO_ONE_CYLINDER;

	/**
	 * We treat the trigger as 1/0 toothed wheel
	 */
	engineConfiguration->trigger.type = TT_TOOTHED_WHEEL;
	engineConfiguration->trigger.customTotalToothCount = 1;
	engineConfiguration->trigger.customSkippedToothCount = 0;

	engineConfiguration->hasIatSensor = false;
	engineConfiguration->hasMapSensor = false;
	engineConfiguration->hasBaroSensor = false;
	engineConfiguration->hasAfrSensor = false;
	engineConfiguration->hasCltSensor = false;

	// Frankenstein analog input #1: PA1 adc1
	// Frankenstein analog input #2: PA3 adc3 TPS
	// Frankenstein analog input #3: PC3 adc13
	// Frankenstein analog input #4: PC1 adc11
	// Frankenstein analog input #5: PA0 adc0
	// Frankenstein analog input #6: PC2 adc12
	// Frankenstein analog input #7: PA4 adc4
	// Frankenstein analog input #8: PA2 adc2
	// Frankenstein analog input #9: PA6 adc6
	// Frankenstein analog input #10: PA7 adc7
	// Frankenstein analog input #11: PC4 adc14
	// Frankenstein analog input #12: PC5 adc15

	engineConfiguration->tpsAdcChannel = EFI_ADC_3;

	/**
	 * TPS 0% 0.9v
	 * TPS 100% 2.34v
	 */
	engineConfiguration->tpsMin = convertVoltageTo10bitADC(1.250);
	engineConfiguration->tpsMax = convertVoltageTo10bitADC(4.538);


	// Frankenstein: low side - out #1: PC14
	// Frankenstein: low side - out #2: PC15
	// Frankenstein: low side - out #3: PE6
	// Frankenstein: low side - out #4: PC13
	// Frankenstein: low side - out #5: PE4
	// Frankenstein: low side - out #6: PE5
	// Frankenstein: low side - out #7: PE2
	// Frankenstein: low side - out #8: PE3
	// Frankenstein: low side - out #9: PE0
	// Frankenstein: low side - out #10: PE1
	// Frankenstein: low side - out #11: PB8
	// Frankenstein: low side - out #12: PB9

	boardConfiguration->triggerInputPins[0] = GPIOA_5;
	boardConfiguration->triggerInputPins[1] = GPIOC_6;
}

