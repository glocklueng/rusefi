/**
 * @file	engine_test_helper.h
 *
 * @date Jun 26, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */
#ifndef ENGINE_TEST_HELPER_H_
#define ENGINE_TEST_HELPER_H_

#include "engine_configuration.h"
#include "ec2.h"

class EngineTestHelper {
public:
	EngineTestHelper(engine_type_e engineType);
	persistent_config_s persistentConfig;
	engine_configuration2_s ec2;

	engine_configuration_s *ec;
};

#endif /* ENGINE_TEST_HELPER_H_ */
