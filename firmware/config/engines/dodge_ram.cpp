/*
 * @file dodge_ram.cpp
 *
 * set_engine_type 31
 *
 * @date Apr 22, 2015
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "main.h"
#include "dodge_ram.h"
#include "custom_engine.h"

EXTERN_ENGINE
;

void setDodgeRam1996(DECLARE_ENGINE_PARAMETER_F) {
	setCustomEngineConfiguration(PASS_ENGINE_PARAMETER_F);
	board_configuration_s * boardConfiguration = &engineConfiguration->bc;

	setOperationMode(engineConfiguration, FOUR_STROKE_CAM_SENSOR);
	engineConfiguration->trigger.type = TT_DODGE_RAM;
	engineConfiguration->injector.flow = 243.6;
	engineConfiguration->map.sensor.type = MT_DODGE_NEON_2003;

	// set_cranking_charge_angle 30
	engineConfiguration->crankingChargeAngle = 30;

	//Base engine setting
	engineConfiguration->specs.cylindersCount = 8;
	engineConfiguration->specs.firingOrder = FO_1_8_4_3_6_5_7_2;

	boardConfiguration->triggerInputPins[0] = GPIOC_6;
	boardConfiguration->triggerInputPins[1] = GPIOA_5;

	boardConfiguration->injectionPins[0] = GPIOE_2;
	boardConfiguration->injectionPins[1] = GPIOB_9;
	boardConfiguration->injectionPins[2] = GPIOD_5;
	boardConfiguration->injectionPins[3] = GPIOB_8;

	boardConfiguration->injectionPins[4] = GPIOB_7;
	boardConfiguration->injectionPins[5] = GPIOE_3;
	boardConfiguration->injectionPins[6] = GPIOE_4;
	boardConfiguration->injectionPins[7] = GPIOD_3;

	boardConfiguration->ignitionPins[0] = GPIOC_9;
	boardConfiguration->ignitionPins[1] = GPIO_UNASSIGNED;
	boardConfiguration->ignitionPins[2] = GPIO_UNASSIGNED;
	boardConfiguration->ignitionPins[3] = GPIO_UNASSIGNED;

	boardConfiguration->mainRelayPin = GPIOE_5;
	boardConfiguration->fuelPumpPin = GPIOE_6;
	boardConfiguration->fanPin = GPIO_UNASSIGNED;

	engineConfiguration->engineChartSize = 450;

	// set_cranking_fuel 7
	engineConfiguration->cranking.baseFuel = 7;

	// set_global_trigger_offset_angle -50
	engineConfiguration->globalTriggerAngleOffset = -50;

	boardConfiguration->alternatorControlPin = GPIOD_7;
	engineConfiguration->alternatorControlPFactor = 22;

	boardConfiguration->idle.solenoidPin = GPIOC_13;
	boardConfiguration->idle.solenoidFrequency = 300;


	engineConfiguration->vbattAdcChannel = EFI_ADC_NONE; // todo: conflict with what?
}
