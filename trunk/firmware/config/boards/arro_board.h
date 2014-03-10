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
#define STM32_SPI_USE_SPI2                  FALSE // external ADC
#define STM32_SPI_USE_SPI3                  TRUE // potentiometer

#define STM32_CAN_USE_CAN1                  TRUE
#define STM32_CAN_USE_CAN2                  TRUE

#define STM32_I2C_I2C1_RX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 5)
#define STM32_I2C_I2C1_TX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 6)

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

/**
 * This section is for bottom-left corner SPI
 */
//#define SPI_CS1_PORT GPIOE
//#define SPI_CS1_PIN 13
//#define SPI_CS2_PORT GPIOE
//#define SPI_CS2_PIN 14
//#define SPI_CS3_PORT GPIOE
//#define SPI_CS3_PIN 15
//#define SPI_CS4_PORT GPIOD
//#define SPI_CS4_PIN 10
//#define SPI_SD_MODULE_PORT GPIOD
//#define SPI_SD_MODULE_PIN 11
#define EFI_SPI2_SCK_PORT GPIOB
#define EFI_SPI2_SCK_PIN 13
#define EFI_SPI2_MISO_PORT GPIOB
#define EFI_SPI2_MISO_PIN 14
#define EFI_SPI2_MOSI_PORT GPIOB
#define EFI_SPI2_MOSI_PIN 15
#define EFI_SPI2_AF 5

/**
 * This section is for right-side center SPI
 */
#define SPI_CS1_PORT GPIOD
#define SPI_CS1_PIN 7
// this is pointing into the sky for now - conflict with I2C
#define SPI_CS2_PORT GPIOH
// this is pointing into the sky for now - conflict with I2C
#define SPI_CS2_PIN 0
#define SPI_CS3_PORT GPIOD
#define SPI_CS3_PIN 5
#define SPI_CS4_PORT GPIOD
#define SPI_CS4_PIN 3
#define SPI_SD_MODULE_PORT GPIOD
#define SPI_SD_MODULE_PIN 4
#define EFI_SPI3_SCK_PORT GPIOB
#define EFI_SPI3_SCK_PIN 3
#define EFI_SPI3_MISO_PORT GPIOB
#define EFI_SPI3_MISO_PIN 4
#define EFI_SPI3_MOSI_PORT GPIOB
#define EFI_SPI3_MOSI_PIN 5
#define EFI_SPI3_AF 6
#define MMC_CARD_SPI SPID3

#define EFI_I2C_SCL_PORT GPIOB
#define EFI_I2C_SCL_PIN 6
#define EFI_I2C_SDA_PORT GPIOB
#define EFI_I2C_SDA_PIN 7
#define EFI_I2C_AF 4

#define EFI_ADC_SLOW_CHANNELS_COUNT 	10

#define EFI_USE_ADC_CHANNEL_IN0 TRUE
#define EFI_USE_ADC_CHANNEL_IN1 TRUE
#define EFI_USE_ADC_CHANNEL_IN2 TRUE
#define EFI_USE_ADC_CHANNEL_IN3 TRUE
#define EFI_USE_ADC_CHANNEL_IN6 TRUE
#define EFI_USE_ADC_CHANNEL_IN7 TRUE
#define EFI_USE_ADC_CHANNEL_IN11 TRUE
#define EFI_USE_ADC_CHANNEL_IN13 TRUE
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
 * ADC 7 	PA7		IAT
 * ADC 6	PA6		CLT
 * ADC 5	PA5		TIM2_CH1
 * ADC 4	PA4
 * ADC 3	PA3
 * ADC 2	PA2
 * ADC 1	PA1		vBatt
 * ADC 0	PA0		MAF
 */

#define ADC_LOGIC_TPS_2 ADC_CHANNEL_IN0
#define ADC_CHANNEL_VBATT ADC_CHANNEL_IN1

#define ADC_LOGIC_AFR ADC_CHANNEL_IN14

#define ADC_CHANNEL_VREF ADC_CHANNEL_IN14


/**
 * currently ChibiOS uses only first and second channels of each timer for input capture
 *
 * So, our options are:
 *
 * TIM2_CH1
 *  PA5
 *
 * TIM4_CH1
 *  PB6
 * 	PD12
 *
 * TIM9_CH1
 *  PE5
 */


/**
 * Primary shaft position input
 * TODO: ? rename to PRIMARY_TRIGGER?
 */

#define PRIMARY_SHAFT_POSITION_INPUT_DRIVER ICUD3
#define PRIMARY_SHAFT_POSITION_INPUT_PORT GPIOC
#define PRIMARY_SHAFT_POSITION_INPUT_PIN 6
#define PRIMARY_SHAFT_POSITION_INPUT_CHANNEL ICU_CHANNEL_1

/**
 * Secondary shaft position input
 * TODO: ? rename to SECONDARY_TRIGGER? *
 */
#define SECONDARY_SHAFT_POSITION_INPUT_DRIVER ICUD2
#define SECONDARY_SHAFT_POSITION_INPUT_PORT GPIOA
#define SECONDARY_SHAFT_POSITION_INPUT_PIN 5
#define SECONDARY_SHAFT_POSITION_INPUT_CHANNEL ICU_CHANNEL_1


#define IDLE_VALVE_PORT GPIOE
#define IDLE_VALVE_PIN 2

// todo: migrate to dynamic pin definition
/* Check Engine light */
#define LED_CHECK_ENGINE_PORT GPIOC
#define LED_CHECK_ENGINE_PIN 9

// todo: migrate to dynamic pin definition
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

/* Additional PINs on top of the standard discovery pins */
#define EXTRA_LED_1_PORT GPIOC
#define EXTRA_LED_1_PIN 14

#define EXTRA_LED_2_PORT GPIOE
#define EXTRA_LED_2_PIN 9

#define EXTRA_LED_3_PORT GPIOE
#define EXTRA_LED_3_PIN 11

#define PRIMARY_SHAFT_POSITION_EMULATION_PIN 1
#define PRIMARY_SHAFT_POSITION_EMULATION_PORT GPIOD

#define SECONDARY_SHAFT_POSITION_EMULATION_PORT GPIOD
#define SECONDARY_SHAFT_POSITION_EMULATION_PIN 2

// todo: migrate to dynamic pin definition
#define IDLE_SWITCH_PORT GPIOC
#define IDLE_SWITCH_PIN 8

//#define ETB_CONTROL_LINE_1_PORT GPIOE
//#define ETB_CONTROL_LINE_1_PIN 0
//
//#define ETB_CONTROL_LINE_2_PORT GPIOB
//#define ETB_CONTROL_LINE_2_PIN 8

#define ETB_CONTROL_LINE_3_PORT GPIOC
#define ETB_CONTROL_LINE_3_PIN 9

//#define CONSOLE_PORT GPIOB
//#define CONSOLE_TX_PIN 10
//#define CONSOLE_RX_PIN 11

/**
 * Here we define the pinout for the human-readable protocol via UART, TunerStudio pinout is defined separately
 */
#define EFI_CONSOLE_TX_PORT GPIOD
#define EFI_CONSOLE_TX_PIN 8
#define EFI_CONSOLE_RX_PORT GPIOD
#define EFI_CONSOLE_RX_PIN 9
#define EFI_CONSOLE_AF 7

#define EFI_CONSOLE_UART_DEVICE (&SD3)


//#define EFI_CONSOLE_TX_PORT GPIOC
//#define EFI_CONSOLE_TX_PIN 10
//#define EFI_CONSOLE_RX_PORT GPIOC
//#define EFI_CONSOLE_RX_PIN 11
//#define EFI_CONSOLE_AF 7

//#define TS_SERIAL_TX_PORT GPIOD
//#define TS_SERIAL_TX_PIN 8
//#define TS_SERIAL_RX_PORT GPIOD
//#define TS_SERIAL_RX_PIN 9
//#define TS_SERIAL_AF 7

#define TS_SERIAL_TX_PORT GPIOC
#define TS_SERIAL_TX_PIN 10
#define TS_SERIAL_RX_PORT GPIOC
#define TS_SERIAL_RX_PIN 11
#define TS_SERIAL_AF 7

#define LED_CRANKING_STATUS_PORT GPIOD
#define LED_CRANKING_STATUS_PIN GPIOD_LED3

#define LED_RUNNING_STATUS_PORT GPIOD
#define LED_RUNNING_STATUS_PIN GPIOD_LED4

#define LED_ERROR_PORT GPIOD
#define LED_ERROR_PIN GPIOD_LED5

#define LED_COMMUNICATION_PORT GPIOD
#define LED_COMMUNICATION_PIN GPIOD_LED6

#define EFI_SIGNAL_EXECUTOR_SLEEP TRUE
#define EFI_SIGNAL_EXECUTOR_SINGLE_TIMER FALSE
#define EFI_SIGNAL_EXECUTOR_HW_TIMER FALSE


//#define EFI_SIGNAL_EXECUTOR_SLEEP FALSE
//#define EFI_SIGNAL_EXECUTOR_SINGLE_TIMER TRUE


// USART1 -> check defined STM32_SERIAL_USE_USART1
// For GPS we have USART1. We can start with PB7 USART1_RX and PB6 USART1_TX
#define GPS_SERIAL_DEVICE &SD1
#define GPS_SERIAL_SPEED 38400
#define GPS_PORT GPIOB
#define GPS_SERIAL_TX_PIN 6
#define GPS_SERIAL_RX_PIN 7

#define HD44780_PORT_RS	GPIOE
#define HD44780_PIN_RS	9
#define HD44780_PORT_E	GPIOE
#define HD44780_PIN_E	11
#define HD44780_PORT_DB4	GPIOE
#define HD44780_PIN_DB4	13
#define HD44780_PORT_DB5	GPIOE
#define HD44780_PIN_DB5	15
#define HD44780_PORT_DB6	GPIOB
#define HD44780_PIN_DB6	11
#define HD44780_PORT_DB7	GPIOB
#define HD44780_PIN_DB7	13

// todo: migrate to dynamic pin definition
#define FAN_RELAY_PORT GPIOC
#define FAN_RELAY_PIN 15

#endif /*ARRO_BOARD_H_*/
