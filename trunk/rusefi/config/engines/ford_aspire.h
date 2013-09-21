/*
 * ford_aspire.h
 *
 *  Created on: Aug 30, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef FORD_ASPIRE_H_
#define FORD_ASPIRE_H_

#define EPS_MESSAGE "Emulating Aspire distributor\r\n"

#define NUMBER_OF_CYLINDERS 4

#define ENGINE_CRANKING_RPM 400

#define ENGINE_HAS_COOLANT_SENSOR TRUE
#define ENGINE_HAS_MAP_SENSOR TRUE

#define CLT_HI_RESISTOR 1500

// be careful not to put brackets around the value, otherwise integer math would trigger
// and you would get zero multiplier
#define RPM_MULT 2 / 4

// todo: this value is way off! I am pretty sure temp coeffs are off also
#define IAT_HI_RESISTOR 2700

#include "adc_inputs.h"
#include "thermistors.h"

/**
 * @brief Engine coolant temperature, C
 */
#define getCoolantTemperature() (getTemperatureC(getAdcValue(ADC_LOGIC_COOLANT), CLT_HI_RESISTOR))

#define getIntakeAirTemperature() (getTemperatureC(getAdcValue(ADC_LOGIC_AIR), IAT_HI_RESISTOR))

myfloat getMaf(void);
myfloat getAfr(void);
myfloat getTPS(void);
myfloat getMap(void);

#endif /* FORD_ASPIRE_H_ */
