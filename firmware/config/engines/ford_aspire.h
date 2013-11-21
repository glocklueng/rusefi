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

void confgiureShaftPositionEmulatorShape(PwmConfig *state);
void configureEngineEventHandler(EventHandlerConfiguration *config);

#define EFI_SHAFT_POSTION_NEEDS_SECONDARY TRUE


#if EFI_EMULATE_POSITION_SENSORS
// One signal per cam shaft revolution
#define PRIMARY_SHAFT_POSITION_EMULATION_PIN 4
#define PRIMARY_SHAFT_POSITION_EMULATION_PORT GPIOD
// Four signals per cam shaft revolution
#define SECONDARY_SHAFT_POSITION_EMULATION_PORT GPIOD
#define SECONDARY_SHAFT_POSITION_EMULATION_PIN 1
#endif /* EFI_EMULATE_POSITION_SENSORS */

#endif /* EFI_ENGINE_FORD_ASPIRE */


#endif /* FORD_ASPIRE_H_ */
