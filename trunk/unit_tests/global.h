/*
 * @file	global.h
 *
 * @date Nov 28, 2013
 * @author pc
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "efitime.h"

#define US_TO_NT_MULTIPLIER 100

#define ALWAYS_INLINE INLINE

#define US2NT(x) (US_TO_NT_MULTIPLIER * (x))

#define NT2US(x) ((x) / US_TO_NT_MULTIPLIER)

#define INLINE inline

typedef int bool_t;

#define EFI_ERROR_CODE 0xffffffff
#define TRUE 1
#define FALSE 0

#define CCM_OPTIONAL

#define EXTERN_ENGINE

#ifdef __cplusplus
class Engine;
#endif

#define DECLARE_ENGINE_PARAMETER_F Engine *engine, engine_configuration_s *engineConfiguration, persistent_config_s *config, board_configuration_s *boardConfiguration
#define DECLARE_ENGINE_PARAMETER_S , Engine *engine, engine_configuration_s *engineConfiguration, persistent_config_s *config, board_configuration_s *boardConfiguration
#define PASS_ENGINE_PARAMETER_F engine, engineConfiguration, config, boardConfiguration
#define PASS_ENGINE_PARAMETER , engine, engineConfiguration, config, boardConfiguration

#define EXPAND_EngineTestHelper Engine *engine = &eth.engine; \
		engine_configuration_s *engineConfiguration = engine->engineConfiguration; \
		persistent_config_s *config = engine->config; \
		board_configuration_s *boardConfiguration = &engineConfiguration->bc;

#define CONFIG(x) engineConfiguration->x
#define ENGINE(x) engine->x
#define TRIGGER_SHAPE(x) engine->triggerShape.x

#endif /* GLOBAL_H_ */
