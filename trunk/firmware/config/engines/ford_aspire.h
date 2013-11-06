/*
 * ford_aspire.h
 *
 *  Created on: Aug 30, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 *
 *
 *	Injectors: Denso 195500-2110, 120cc, purple, 13.9 ohms
 *	camshaft position sensor(s): two Hall sensors
 *	single ignition coil(s), low-side driven with 5v pull-up resistor
 */

#ifndef FORD_ASPIRE_H_
#define FORD_ASPIRE_H_

#if EFI_ENGINE_FORD_ASPIRE

#include "global.h"
#include "adc_inputs.h"
#include "thermistors.h"
#include "pwm_generator.h"

#define SHAFT_POSITION_EVENT_COUNT 10

#define EFI_SIGNAL_EXECUTOR_SLEEP TRUE
//#define EFI_SIGNAL_EXECUTOR_HW_TIMER TRUE

#include "main_loop.h"

#define EFI_USE_MULTI_SENSOR_SHAFT_SENSOR TRUE

#define EFI_ENGINE_ID "Ford Aspire"

#define ASPIRE_MAGIC_DUTY_CYCLE 0.3877

#define NUMBER_OF_CYLINDERS 4


#define ENGINE_CRANKING_RPM 400

#define ENGINE_HAS_COOLANT_SENSOR TRUE
#define ENGINE_HAS_MAP_SENSOR TRUE

#define CLT_HI_RESISTOR 1500

// be careful not to put brackets around the value, otherwise integer math would trigger
// and you would get zero multiplier
#define RPM_MULT 0.5

// todo: this value is way off! I am pretty sure temp coeffs are off also
#define IAT_HI_RESISTOR 2700

/**
 * @brief Engine coolant temperature, C
 */
#define getCoolantTemperature() (getTemperatureC(adcToVolts(getAdcValue(ADC_LOGIC_COOLANT)), CLT_HI_RESISTOR))

#define getIntakeAirTemperature() (getTemperatureC(adcToVolts(getAdcValue(ADC_LOGIC_AIR)), IAT_HI_RESISTOR))


/*
 * 10 channel board is (from left to right):
 * ADC 15	PC5		TPS
 * ADC 14	PC4
 * ADC 7 	PA7
 * ADC 6	PA6		CLT
 * ADC 5	PA5		TIM2_CH1
 * ADC 4	PA4
 * ADC 3
 * ADC 2
 * ADC 1			MAF
 * ADC 0
 */

#define ADC_LOGIC_TPS ADC_CHANNEL_IN15
#define ADC_LOGIC_COOLANT ADC_CHANNEL_IN6
#define ADC_LOGIC_MAF ADC_CHANNEL_IN1


#define ADC_LOGIC_MAP ADC_CHANNEL_IN14
#define ADC_LOGIC_AFR ADC_CHANNEL_IN14

#define ADC_CHANNEL_VREF ADC_CHANNEL_IN14
#define ADC_LOGIC_AIR ADC_CHANNEL_IN14

myfloat getMaf(void);
myfloat getAfr(void);
myfloat getTPS(void);
myfloat getMap(void);

void confgiureShaftPositionEmulatorShape(PwmConfig *state);
void configureInjection(InjectionConfiguration *config);

#define PRIMARY_SHAFT_POSITION_INPUT_DRIVER ICUD2
#define PRIMARY_SHAFT_POSITION_INPUT_PORT GPIOA
#define PRIMARY_SHAFT_POSITION_INPUT_PIN 5
#define PRIMARY_SHAFT_POSITION_INPUT_CHANNEL ICU_CHANNEL_1

#define EFI_SHAFT_POSTION_NEEDS_SECONDARY TRUE

#define SECONDARY_SHAFT_POSITION_INPUT_DRIVER ICUD3
#define SECONDARY_SHAFT_POSITION_INPUT_PORT GPIOC
#define SECONDARY_SHAFT_POSITION_INPUT_PIN 6
#define SECONDARY_SHAFT_POSITION_INPUT_CHANNEL ICU_CHANNEL_1

#define INJECTOR_1_PORT GPIOB
#define INJECTOR_1_PIN 8

#define INJECTOR_2_PORT GPIOB
#define INJECTOR_2_PIN 9

#define INJECTOR_3_PORT GPIOE
#define INJECTOR_3_PIN 1

#define INJECTOR_4_PORT GPIOE
#define INJECTOR_4_PIN 0

#define FUEL_PUMP_PORT GPIOE
#define FUEL_PUMP_PIN 4

#if EFI_EMULATE_POSITION_SENSORS
// One signal per cam shaft revolution
#define PRIMARY_SHAFT_POSITION_EMULATION_PIN 4
#define PRIMARY_SHAFT_POSITION_EMULATION_PORT GPIOD
// Four signals per cam shaft revolution
#define SECONDARY_SHAFT_POSITION_EMULATION_PORT GPIOD
#define SECONDARY_SHAFT_POSITION_EMULATION_PIN 1
#endif /* EFI_EMULATE_POSITION_SENSORS */

#define LOGIC_ANALYZER_ONE_DRIVER ICUD1
#define LOGIC_ANALYZER_PORT GPIOA
#define LOGIC_ANALYZER_PIN 8
//#define SECONDARY_SHAFT_POSITION_INPUT_CHANNEL ICU_CHANNEL_1

#define SPARK_1_PORT GPIOD
#define SPARK_1_PIN 3

#endif /* EFI_ENGINE_FORD_ASPIRE */


#endif /* FORD_ASPIRE_H_ */
