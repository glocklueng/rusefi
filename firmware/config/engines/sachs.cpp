/**
 * @file	sachs.cpp
 *
 * set_engine_type 29
 * http://rusefi.com/forum/viewtopic.php?f=3&t=396
 *
 * @date Jan 26, 2015
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "sachs.h"

void setSachs(engine_configuration_s *engineConfiguration) {
	engineConfiguration->displacement = 0.1; // 100cc
}

