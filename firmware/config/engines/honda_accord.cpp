/**
 * @file	honda_accord.cpp
 *
 * 1995 Honda Accord EX
 * http://rusefi.com/wiki/index.php?title=Vehicle:Honda_Accord_1995
 * http://rusefi.com/forum/viewtopic.php?f=3&t=621
 *
 * engine_type 6
 *
 * @date Jan 12, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "engine_configuration.h"
#include "trigger_decoder.h"
#include "thermistors.h"

void setHondaAccordConfiguration(engine_configuration_s *engineConfiguration, board_configuration_s *boardConfiguration) {
	engineConfiguration->engineType = HONDA_ACCORD_CD;
	engineConfiguration->triggerConfig.triggerType = TT_HONDA_ACCORD_CD;

	engineConfiguration->map.sensor.sensorType = MT_HONDA3BAR;

	engineConfiguration->cylindersCount = 4;
	engineConfiguration->displacement = 2.156;

	// Keihin 06164-P0A-A00
	engineConfiguration->injectorFlow = 248;


	engineConfiguration->algorithm = LM_SPEED_DENSITY;


	engineConfiguration->crankingSettings.coolantTempMaxC = 65; // 8ms at 65C
	engineConfiguration->crankingSettings.fuelAtMaxTempMs = 8;

	engineConfiguration->crankingSettings.coolantTempMinC = 0; // 20ms at 0C
	engineConfiguration->crankingSettings.fuelAtMinTempMs = 15;


	memset(boardConfiguration->adcHwChannelEnabled, 0, sizeof(boardConfiguration->adcHwChannelEnabled));
	boardConfiguration->adcHwChannelEnabled[0] = ADC_FAST; // ADC0 - PA0 - MAP
	boardConfiguration->adcHwChannelEnabled[1] = ADC_SLOW;
	boardConfiguration->adcHwChannelEnabled[2] = ADC_SLOW;
	boardConfiguration->adcHwChannelEnabled[3] = ADC_SLOW;
	boardConfiguration->adcHwChannelEnabled[4] = ADC_SLOW;

	boardConfiguration->adcHwChannelEnabled[6] = ADC_SLOW;
	boardConfiguration->adcHwChannelEnabled[7] = ADC_SLOW;
	boardConfiguration->adcHwChannelEnabled[11] = ADC_SLOW;
	boardConfiguration->adcHwChannelEnabled[12] = ADC_SLOW;
	boardConfiguration->adcHwChannelEnabled[13] = ADC_SLOW;


	engineConfiguration->map.sensor.sensorType = MT_MPX4250;
	engineConfiguration->map.sensor.hwChannel = 0;

	setThermistorConfiguration(&engineConfiguration->cltThermistorConf, -20.0, 18000.0, 23.8889, 2100.0, 120.0, 100.0);
	engineConfiguration->cltThermistorConf.bias_resistor = 1500; // same as OEM ECU

	setThermistorConfiguration(&engineConfiguration->iatThermistorConf, -20.0, 18000.0, 23.8889, 2100.0, 120.0, 100.0);
	engineConfiguration->iatThermistorConf.bias_resistor = 1500; // same as OEM ECU

	// set_cranking_charge_angle 35
	engineConfiguration->crankingChargeAngle = 35;
	// set_cranking_timing_angle 0
	engineConfiguration->crankingTimingAngle = 0;

	// set_global_trigger_offset_angle 34
	engineConfiguration->globalTriggerAngleOffset = 34;

	// set_rpm_hard_limit 4000
	engineConfiguration->rpmHardLimit = 4000; // yes, 4k. let's play it safe for now
	// set_cranking_rpm 2000
	engineConfiguration->crankingSettings.crankingRpm = 2000;


	// set_ignition_offset 350
//	engineConfiguration->ignitionOffset = 350;
	 // set_injection_offset 510
//	engineConfiguration->injectionOffset = 510;

}

