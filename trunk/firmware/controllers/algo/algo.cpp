/*
 * @file	algo.cpp
 *
 * @date Mar 2, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 *
 *
 * This file is part of rusEfi - see http://rusefi.com
 *
 * rusEfi is free software; you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * rusEfi is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "global.h"
#include "algo.h"
#include "advance_map.h"
#include "fuel_math.h"
#include "settings.h"
#include "signal_executor.h"
#include "speed_density.h"

EXTERN_ENGINE;

void initDataStructures(DECLARE_ENGINE_PARAMETER_F) {
	prepareFuelMap(engineConfiguration);
	prepareTimingMap(PASS_ENGINE_PARAMETER_F);
	initSpeedDensity(engineConfiguration);
}

void initAlgo(Logging *sharedLogger, engine_configuration_s *engineConfiguration) {
	initInterpolation(sharedLogger);
#if EFI_PROD_CODE || EFI_SIMULATOR
	initSettings(engineConfiguration);
	initSignalExecutor();
#endif
}
