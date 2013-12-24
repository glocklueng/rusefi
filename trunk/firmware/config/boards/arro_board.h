/*
 * arro_board.h
 *
 * @date Nov 14, 2013
 * @author frig
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

#define STM32_CAN_USE_CAN1                  TRUE
#define STM32_CAN_USE_CAN2                  TRUE

#define EFI_INTERNAL_SLOW_ADC_PWM	&PWMD5
#define EFI_INTERNAL_FAST_ADC_PWM	&PWMD4

#define EFI_CAN_DEVICE CAND2
#define EFI_CAN_RX_PORT GPIOB
#define EFI_CAN_RX_PIN 12
#define EFI_CAN_RX_AF 9
#define EFI_CAN_TX_PORT GPIOB
#define EFI_CAN_TX_PIN 6
#define EFI_CAN_TX_AF 9

//#define EFI_CAN_DEVICE CAND1
//#define EFI_CAN_RX_PORT GPIOB
//#define EFI_CAN_RX_PIN 8
//#define EFI_CAN_RX_AF 9
//#define EFI_CAN_TX_PORT GPIOB
//#define EFI_CAN_TX_PIN 9
//#define EFI_CAN_TX_AF 9

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
 * ADC 14	PC4		MAP
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
#define ADC_LOGIC_TPS_2 ADC_CHANNEL_IN0

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
#define INJECTOR_1_PIN 9
#define INJECTOR_1_XOR 0

#define INJECTOR_2_PORT GPIOE
#define INJECTOR_2_PIN 1
#define INJECTOR_2_XOR 0

#define INJECTOR_3_PORT GPIOE
#define INJECTOR_3_PIN 3
#define INJECTOR_3_XOR 0

#define INJECTOR_4_PORT GPIOE
#define INJECTOR_4_PIN 5
#define INJECTOR_4_XOR 0

#define INJECTOR_5_PORT GPIOE
#define INJECTOR_5_PIN 6
#define INJECTOR_5_XOR 0

#define IDLE_VALVE_PORT GPIOE
#define IDLE_VALVE_PIN 2

/* Check Engine light */
#define LED_CHECK_ENGINE_PORT GPIOC
#define LED_CHECK_ENGINE_PIN 7

/* Fuel pump */
#define FUEL_PUMP_PORT GPIOC
#define FUEL_PUMP_PIN 13

/* Logic analyzer */
#define LOGIC_ANALYZER_1_DRIVER ICUD1
#define LOGIC_ANALYZER_1_PORT GPIOA
#define LOGIC_ANALYZER_1_PIN 8

#define LOGIC_ANALYZER_2_DRIVER ICUD9
#define LOGIC_ANALYZER_2_PORT GPIOE
#define LOGIC_ANALYZER_2_PIN 7

/* Spark ports */
#define SPARK_1_PORT GPIOC
#define SPARK_1_PIN 15
#define SPARK_1_XOR 1

#define SPARK_2_PORT GPIOE
#define SPARK_2_PIN 4
#define SPARK_2_XOR 1

/* Additional PINs on top of the standard discovery pins */
#define EXTRA_LED_1_PORT GPIOC
#define EXTRA_LED_1_PIN 14

#define PRIMARY_SHAFT_POSITION_EMULATION_PIN 1
#define PRIMARY_SHAFT_POSITION_EMULATION_PORT GPIOD

#define SECONDARY_SHAFT_POSITION_EMULATION_PORT GPIOD
#define SECONDARY_SHAFT_POSITION_EMULATION_PIN 2

#define IDLE_SWITCH_PORT GPIOC
#define IDLE_SWITCH_PIN 8

#define ETB_CONTROL_LINE_1_PORT GPIOE
#define ETB_CONTROL_LINE_1_PIN 0

#define ETB_CONTROL_LINE_2_PORT GPIOB
#define ETB_CONTROL_LINE_2_PIN 8

#define ETB_CONTROL_LINE_3_PORT GPIOD
#define ETB_CONTROL_LINE_3_PIN 3

//#define CONSOLE_PORT GPIOB
//#define CONSOLE_TX_PIN 10
//#define CONSOLE_RX_PIN 11

#define EFI_CONSOLE_PORT GPIOD
#define EFI_CONSOLE_TX_PIN 8
#define EFI_CONSOLE_RX_PIN 9
#define EFI_CONSOLE_AF 7

#define STATUS_LED_1_PORT GPIOD
#define STATUS_LED_1_PIN GPIOD_LED3

#define STATUS_LED_2_PORT GPIOD
#define STATUS_LED_2_PIN GPIOD_LED4

#define STATUS_LED_3_PORT GPIOD
#define STATUS_LED_3_PIN GPIOD_LED5

#define STATUS_LED_4_PORT GPIOD
#define STATUS_LED_4_PIN GPIOD_LED6

#define EFI_SIGNAL_EXECUTOR_SLEEP TRUE
//#define EFI_SIGNAL_EXECUTOR_SINGLE_TIMER TRUE
//#define EFI_SIGNAL_EXECUTOR_HW_TIMER TRUE

#endif /*ARRO_BOARD_H_*/
