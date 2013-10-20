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

#define EFI_INTERNAL_SLOW_ADC_PWM	&PWMD5
#define EFI_INTERNAL_FAST_ADC_PWM	&PWMD4


#endif /* FORD_ASPIRE_MCU_H_ */
