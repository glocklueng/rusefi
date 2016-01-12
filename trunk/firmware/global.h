/*
 * @file global.h
 *
 * @date May 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2016
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <ch.h>
#include <hal.h>
#include <string.h>

// this is about MISRA not liking 'time.h'. todo: figure out something
#if defined __GNUC__
// GCC
#include <sys/types.h>
#define ALWAYS_INLINE __attribute__((always_inline))
#else
// IAR
typedef unsigned int time_t;
// todo: what's the IAR option?
#define ALWAYS_INLINE INLINE
#endif

#include "efifeatures.h"
#include "rusefi_types.h"
#include "rusefi_enums.h"
#if EFI_PROD_CODE
#include "io_pins.h"
#include "auto_generated_enums.h"
#endif
#include "obd_error_codes.h"
#include "error_handling.h"

/* definition to expand macro then apply to pragma message */
#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define VAR_NAME_VALUE(var) #var "="  VALUE(var)

// project-wide default thread stack size
// see also PORT_INT_REQUIRED_STACK
#define UTILITY_THREAD_STACK_SIZE 400

#define EFI_ERROR_CODE 0xffffffff

#if EFI_USE_CCM && defined __GNUC__
#define CCM_OPTIONAL __attribute__((section(".ccm")))
#elif defined __GNUC__
#define CCM_OPTIONAL
#else
#define CCM_OPTIONAL @ ".ccm"
#endif

// this stuff is about ChibiOS 2.6 > Migration
typedef VirtualTimer virtual_timer_t;
typedef EventListener event_listener_t;
typedef Thread thread_t;

#define THD_WORKING_AREA WORKING_AREA
#define THD_FUNCTION(tname, arg) void tname(void *arg)


#if EFI_PROD_CODE

/**
 * The following obscurantism is a hack to reduce stack usage, maybe even a questionable performance
 * optimization.
 *
 * rusEfi main processing happends on IRQ so PORT_INT_REQUIRED_STACK has to be pretty large. Problem
 * is that PORT_INT_REQUIRED_STACK is included within each user thread stack, thus this large stack multiplies
 * and this consumes a lot of valueable RAM. While forcing the comiler to inline helps to some degree,
 * it would be even better not to waste stack on passing the parameter.
 *
 * In the firmware we are using 'extern *Engine' - in the firmware Engine is a signleton
 *
 * On the other hand, in order to have a meaningful unit test we are passing Engine * engine as a parameter
 */

#define EXTERN_ENGINE extern Engine *engine; \
		extern engine_configuration_s *engineConfiguration; \
		extern board_configuration_s *boardConfiguration; \
		extern persistent_config_container_s persistentState; \
		extern Engine _engine; \
		extern persistent_config_s *config; \
		extern engine_configuration2_s * engineConfiguration2

#define DECLARE_ENGINE_PARAMETER_F void
#define DECLARE_ENGINE_PARAMETER_S
#define PASS_ENGINE_PARAMETER_F
#define PASS_ENGINE_PARAMETER

/**
 * this macro allows the compiled to figure out the complete static address, that's a performance
 * optimization
 */
#define CONFIG(x) persistentState.persistentConfiguration.engineConfiguration.x
#define ENGINE(x) _engine.x
#define TRIGGER_SHAPE(x) _engine.triggerShape.x

#else
#define EXTERN_ENGINE
#endif


/**
 * low-level function is used here to reduce stack usage
 */
#define ON_FATAL_ERROR() \
		palWritePad(LED_ERROR_PORT, LED_ERROR_PIN, 1); \
		turnAllPinsOff();


#endif /* GLOBAL_H_ */
