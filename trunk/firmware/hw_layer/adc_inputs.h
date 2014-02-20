/**
 * @file	adc_inputs.h
 * @brief	Low level ADC code
 *
 * @date Jan 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ADC_INPUTS_H_
#define ADC_INPUTS_H_

#include "main.h"

GPIO_TypeDef* getAdcChannelPort(int channel);
int getAdcChannelPin(int channel);
void initAdcInputs(void);
void pokeAdcInputs(void);
int getInternalAdcValue(int index);

// this structure contains one multi-channel ADC state snapshot
typedef struct {
	volatile adcsample_t adc_data[EFI_ADC_SLOW_CHANNELS_COUNT];
	time_t time;
} adc_state;


#define getAdcValue(channel) getInternalAdcValue(channel)

#define adcToVolts(adc) ((((float) 3.0) * (adc) / 4095))

#define adcToVoltsDivided(adc) (adcToVolts(adc) * engineConfiguration->analogInputDividerCoefficient)

#define getVoltage(channel) (adcToVolts(getAdcValue(channel)))

#define getVoltageDivided(channel) (getVoltage(channel) * engineConfiguration->analogInputDividerCoefficient)

#endif /* ADC_INPUTS_H_ */
