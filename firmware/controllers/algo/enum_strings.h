/**
 * @file enum_strings.h
 *
 * @date Sep 4, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef ENUM_STRINGS_H_
#define ENUM_STRINGS_H_

#include "rusefi_enums.h"

const char* getConfigurationName(engine_type_e engineType);
const char * ignitionModeToString(ignition_mode_e mode);

#endif /* ENUM_STRINGS_H_ */
