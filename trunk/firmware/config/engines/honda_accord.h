/**
 * @file	honda_accord.h
 *
 * @date Jan 12, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef HONDA_ACCORD_H_
#define HONDA_ACCORD_H_

#include "engine.h"

void setFrankenso_01_LCD(board_configuration_s *boardConfiguration);
void setHondaAccordConfigurationTwoWires(DECLARE_ENGINE_PARAMETER_F);
void setHondaAccordConfigurationThreeWires(DECLARE_ENGINE_PARAMETER_F);
void setHondaAccordConfigurationDip(DECLARE_ENGINE_PARAMETER_F);

#endif /* HONDA_ACCORD_H_ */
