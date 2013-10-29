/*
 *  Created on: Oct 17, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    ford_aspire_mcu.h
 */


#ifndef FORD_ASPIRE_MCU_H_
#define FORD_ASPIRE_MCU_H_

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

#define EFI_ADC_SLOW_CHANNELS_COUNT		6

#define EFI_USE_ADC_CHANNEL_IN0 TRUE
#define EFI_USE_ADC_CHANNEL_IN1 TRUE
#define EFI_USE_ADC_CHANNEL_IN6 TRUE
#define EFI_USE_ADC_CHANNEL_IN7 TRUE
#define EFI_USE_ADC_CHANNEL_IN14 TRUE
#define EFI_USE_ADC_CHANNEL_IN15 TRUE

#endif /* FORD_ASPIRE_MCU_H_ */
