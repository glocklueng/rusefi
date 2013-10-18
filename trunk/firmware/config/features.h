/*
 * features.h
 *
 *  Created on: Aug 29, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef FEATURES_H_
#define FEATURES_H_

#define MAF_MODE 1

/**
 * Patched version of ChibiOS/RT support extra details in the system error messages
 */
#define EFI_CUSTOM_PANIC_METHOD TRUE

/**
 * Build-in logic analyzer support. Logic analyzer viewer is one of the java console panes.
 */
#define EFI_WAVE_ANALYZER TRUE

/**
 * TunerStudio support.
 */
#define EFI_TUNER_STUDIO TRUE
/**
 * TunerStudio debug output
 */
#define EFI_TUNER_STUDIO_VERBOSE TRUE

#define EFI_DEFAILED_LOGGING FALSE

/**
 * Usually you need shaft position input, but maybe you do not need it?
 */
#define EFI_SHAFT_POSITION_INPUT TRUE

/**
 * MCP42010 digital potentiometer supporrt. This could be useful if you are stimulating some
 * stock ECU
 */
#define EFI_POTENTIOMETER TRUE

#define EFI_INTERNAL_ADC TRUE

#define EFI_DENSO_ADC FALSE

#define RFI_IDLE_CONTROL FALSE

#define EFI_ENGINE_EMULATOR TRUE
#define EFI_EMULATE_POSITION_SENSORS TRUE

#define EFI_SERIAL_OVER_USB TRUE

/**
 * 1996 1.3 Ford Aspire
 */
//#define EFI_ENGINE_FORD_ASPIRE TRUE

//#define EFI_ENGINE_SNOW_BLOWER TRUE

/**
 * 60-2 toothed wheel
 */
#define EFI_ENGINE_DENISVAK TRUE

#endif /* FEATURES_H_ */
