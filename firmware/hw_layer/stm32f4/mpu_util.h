/**
 * @file	mpu_util.h
 *
 * @date Jul 27, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */
#ifndef MPU_UTIL_H_
#define MPU_UTIL_H_

#ifndef GPIO_AF_TIM1
#define GPIO_AF_TIM1 1
#endif

#ifndef GPIO_AF_TIM2
#define GPIO_AF_TIM2 1
#endif

#ifndef GPIO_AF_TIM3
#define GPIO_AF_TIM3 2
#endif

#ifndef GPIO_AF_TIM4
#define GPIO_AF_TIM4 2
#endif

#ifndef GPIO_AF_TIM5
#define GPIO_AF_TIM5 2
#endif

#ifndef GPIO_AF_TIM9
#define GPIO_AF_TIM9 3
#endif

#ifndef ADC_TwoSamplingDelay_5Cycles
#define ADC_TwoSamplingDelay_5Cycles ((uint32_t)0x00000000)
#endif

#ifndef ADC_TwoSamplingDelay_20Cycles
#define ADC_TwoSamplingDelay_20Cycles ((uint32_t)0x00000F00)
#endif

#ifndef ADC_CR2_SWSTART
#define ADC_CR2_SWSTART ((uint32_t)0x40000000)
#endif


void baseHardwareInit(void);

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

// these need to be declared C style for the linker magic to work

void DebugMonitorVector(void);
void UsageFaultVector(void);
void BusFaultVector(void);
void HardFaultVector(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MPU_UTIL_H_ */
