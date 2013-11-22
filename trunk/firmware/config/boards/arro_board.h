/*
 * arro_board.h
 *
 *  Created on: Nov 14, 2013
 *      Author: frig
 *
 *      This file contents a configuration of arro239 ecu board. Pinout and other.
 */
#ifndef ARRO_BOARD_H_
#define ARRO_BOARD_H_


#define STM32_ICU_USE_TIM1                  TRUE // wave input
#define STM32_ICU_USE_TIM2                  TRUE // primary position sensor
#define STM32_ICU_USE_TIM3                  TRUE // secondary position sensor
#define STM32_ICU_USE_TIM4                  FALSE
#define STM32_ICU_USE_TIM5                  FALSE
#define STM32_ICU_USE_TIM8                  FALSE
#define STM32_ICU_USE_TIM9                  TRUE // wave input

#define STM32_PWM_USE_TIM1                  FALSE
#define STM32_PWM_USE_TIM2                  FALSE
#define STM32_PWM_USE_TIM3                  FALSE
#define STM32_PWM_USE_TIM4                  TRUE // fast adc
#define STM32_PWM_USE_TIM5                  TRUE // slow adc
#define STM32_PWM_USE_TIM8                  FALSE
#define STM32_PWM_USE_TIM9                  FALSE

#define STM32_SPI_USE_SPI1                  FALSE
#define STM32_SPI_USE_SPI2                  TRUE // external ADC
#define STM32_SPI_USE_SPI3                  TRUE // potentiometer

#define EFI_INTERNAL_SLOW_ADC_PWM	&PWMD5
#define EFI_INTERNAL_FAST_ADC_PWM	&PWMD4

#define EFI_SPI2_SCK_PORT GPIOB
#define EFI_SPI2_SCK_PIN 13
#define EFI_SPI2_MISO_PORT GPIOB
#define EFI_SPI2_MISO_PIN 14
#define EFI_SPI2_MOSI_PORT GPIOB
#define EFI_SPI2_MOSI_PIN 15
#define EFI_SPI2_AF 5

#define EFI_ADC_SLOW_CHANNELS_COUNT 	8

#define EFI_USE_ADC_CHANNEL_IN0 TRUE
#define EFI_USE_ADC_CHANNEL_IN1 TRUE
#define EFI_USE_ADC_CHANNEL_IN2 TRUE
#define EFI_USE_ADC_CHANNEL_IN3 TRUE
#define EFI_USE_ADC_CHANNEL_IN6 TRUE
#define EFI_USE_ADC_CHANNEL_IN7 TRUE
#define EFI_USE_ADC_CHANNEL_IN14 TRUE
#define EFI_USE_ADC_CHANNEL_IN15 TRUE

/**
 * Patched version of ChibiOS/RT support extra details in the system error messages
 */
#define EFI_CUSTOM_PANIC_METHOD TRUE

/*
 * 10 channel board is (from left to right):
 * ADC 15	PC5		TPS
 * ADC 14	PC4
 * ADC 7 	PA7
 * ADC 6	PA6		CLT
 * ADC 5	PA5		TIM2_CH1
 * ADC 4	PA4
 * ADC 3	PA3
 * ADC 2	PA2
 * ADC 1	PA1		MAF
 * ADC 0	PA0
 */

#define ADC_LOGIC_TPS ADC_CHANNEL_IN15
#define ADC_LOGIC_COOLANT ADC_CHANNEL_IN6
#define ADC_LOGIC_MAF ADC_CHANNEL_IN1


#define ADC_LOGIC_MAP ADC_CHANNEL_IN14
#define ADC_LOGIC_AFR ADC_CHANNEL_IN14

#define ADC_CHANNEL_VREF ADC_CHANNEL_IN14
#define ADC_LOGIC_AIR ADC_CHANNEL_IN14

/* Primary shaft position input */

#define PRIMARY_SHAFT_POSITION_INPUT_DRIVER ICUD3
#define PRIMARY_SHAFT_POSITION_INPUT_PORT GPIOC
#define PRIMARY_SHAFT_POSITION_INPUT_PIN 6
#define PRIMARY_SHAFT_POSITION_INPUT_CHANNEL ICU_CHANNEL_1

/* Secondary shaft position input */
#define SECONDARY_SHAFT_POSITION_INPUT_DRIVER ICUD2
#define SECONDARY_SHAFT_POSITION_INPUT_PORT GPIOA
#define SECONDARY_SHAFT_POSITION_INPUT_PIN 5
#define SECONDARY_SHAFT_POSITION_INPUT_CHANNEL ICU_CHANNEL_1

/* Injector ports */
#define INJECTOR_1_PORT GPIOB
#define INJECTOR_1_PIN 8

#define INJECTOR_2_PORT GPIOB
#define INJECTOR_2_PIN 9

#define INJECTOR_3_PORT GPIOE
#define INJECTOR_3_PIN 1

#define INJECTOR_4_PORT GPIOE
#define INJECTOR_4_PIN 0

#define IDLE_VALVE_PORT GPIOE
#define IDLE_VALVE_PIN 3

/* Fuel pump */
#define FUEL_PUMP_PORT GPIOE
#define FUEL_PUMP_PIN 4

/* Logic analyzer */
#define LOGIC_ANALYZER_ONE_DRIVER ICUD1
#define LOGIC_ANALYZER_PORT GPIOA
#define LOGIC_ANALYZER_PIN 8

/* Spark ports */
#define SPARK_1_PORT GPIOD
#define SPARK_1_PIN 3

#define PRIMARY_SHAFT_POSITION_EMULATION_PIN 1
#define PRIMARY_SHAFT_POSITION_EMULATION_PORT GPIOD

#define SECONDARY_SHAFT_POSITION_EMULATION_PORT GPIOD
#define SECONDARY_SHAFT_POSITION_EMULATION_PIN 2

#define IDLE_SWITCH_PORT GPIOC
#define IDLE_SWITCH_PIN 8

#endif /*ARRO_BOARD_H_*/
