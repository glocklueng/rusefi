/**
 * @file	engine_test_helper.cpp
 *
 * @date Jun 26, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "engine_test_helper.h"
#include "stddef.h"

EngineTestHelper::EngineTestHelper(engine_type_e engineType) {
	ec = &persistentConfig.engineConfiguration;

	resetConfigurationExt(NULL, FORD_INLINE_6_1995, ec, &ec2, &persistentConfig.boardConfiguration);

}

