/*
 * features.h
 *
 *  Created on: Aug 29, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef FEATURES_H_
#define FEATURES_H_

#define MAF_MODE 1

#define EFI_CUSTOM_PANIC_METHOD TRUE

//#define EFI_WAVE_ANALYZER FALSE
//#define EFI_WAVE_ANALYZER TRUE

#define EFI_TUNER_STUDIO TRUE
#define EFI_TUNER_STUDIO_VERBOSE TRUE

#define EFI_DEFAILED_LOGGING FALSE

#define EFI_CRANK_INPUT TRUE

#define EFI_POTENTIOMETER TRUE

#define EFI_INTERNAL_ADC TRUE

#define EFI_DENSO_ADC FALSE

#define RFI_IDLE_CONTROL FALSE

//#define EFI_ENGINE_EMULATOR TRUE
#define EFI_EMULATE_POSITION_SENSORS TRUE

#define EFI_SERIAL_OVER_USB TRUE


/**
 * 1996 1.3 Ford Aspire
 */
#define EFI_ENGINE_FORD_ASPIRE TRUE

//#define EFI_ENGINE_SNOW_BLOWER TRUE



#include "engine.h"

#endif /* FEATURES_H_ */
