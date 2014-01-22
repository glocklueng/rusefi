/**
 * @file features.h
 * @brief In this header we can configure which firmware modules are used.
 *
 * @date Aug 29, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef FEATURES_H_
#define FEATURES_H_

/**
 * Build-in logic analyzer support. Logic analyzer viewer is one of the java console panes.
 */
#define EFI_WAVE_ANALYZER TRUE

#define EFI_SERIAL_OVER_USB TRUE

//#define SERIAL_SPEED (8 * 115200)
//#define SERIAL_SPEED (2 * 115200)
#define SERIAL_SPEED 115200

/**
 * TunerStudio support.
 */
#define EFI_TUNER_STUDIO TRUE
//#define EFI_TUNER_STUDIO_OVER_USB TRUE

/**
 * TunerStudio debug output
 */
#define EFI_TUNER_STUDIO_VERBOSE TRUE

#define EFI_DEFAILED_LOGGING FALSE

/**
 * Dev console support.
 */
#define EFI_CLI_SUPPORT TRUE


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

#define EFI_CAN_SUPPORT FALSE

#define EFI_IDLE_CONTROL FALSE

#define EFI_ENGINE_EMULATOR TRUE
#define EFI_EMULATE_POSITION_SENSORS TRUE

#if EFI_TUNER_STUDIO
#if EFI_SERIAL_OVER_USB
#if EFI_TUNER_STUDIO_OVER_USB
  #pragma "Cannot be EFI_SERIAL_OVER_USB and EFI_TUNER_STUDIO_OVER_USB at the same time"
#endif
#else
#if EFI_TUNER_STUDIO_OVER_USB
#else
  #pragma "Cannot be serial over USART and TUNER_STUDIO over USART at the same time"
#endif
#endif /* EFI_TUNER_STUDIO */
#endif /* EFI_SERIAL_OVER_USB */

/**
 * This macros is used to hide pieces of the code from unit tests, so it only makes sense in folders exposed to the tests project.
 * This macros is NOT about taking out logging in general.
 */
#define EFI_PROD_CODE TRUE

/**
 * Do we need Malfunction Indicator blinking logic?
 */
#define EFI_MALFUNCTIONAL_INDICATOR TRUE
/**
 * Do we need file logging (like SD card) logic?
 */
#define EFI_FILE_LOGGING TRUE

/**
 * Do we need GPS logic?
 */
#define EFI_GPS TRUE

/**
 * While we embed multiple PnP configurations into the same firmware binary, these marcoses give us control
 * over which configurations go into the binary
 */
#define EFI_SUPPORT_DODGE_NEON TRUE
#define EFI_SUPPORT_FORD_ASPIRE TRUE
#define EFI_SUPPORT_FORD_FIESTA TRUE
#define EFI_SUPPORT_NISSAN_PRIMERA TRUE

#endif /* FEATURES_H_ */
