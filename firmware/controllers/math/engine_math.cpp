/**
 * @file	engine_math.cpp
 * @brief
 *
 * @date Jul 13, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
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

#include "main.h"
#include "engine_math.h"
#include "engine_configuration.h"
#include "interpolation.h"
#include "allsensors.h"
#include "io_pins.h"
#include "trigger_decoder.h"
#include "event_registry.h"
#include "efiGpio.h"

EXTERN_ENGINE
;

extern OutputPin outputs[IO_PIN_COUNT];

/**
 * this cache allows us to find a close-enough (with one degree precision) trigger wheel index by
 * given angle with fast constant speed
 */
static int triggerIndexByAngle[720];

/*
 * default Volumetric Efficiency
 */
//float getDefaultVE(int rpm) {
//	if (rpm > 5000)
//		return interpolate(5000, 1.1, 8000, 1, rpm);
//	return interpolate(500, 0.5, 5000, 1.1, rpm);
//}
/**
 * @return number of milliseconds in one crankshaft revolution
 */
float getCrankshaftRevolutionTimeMs(int rpm) {
	return 360 * getOneDegreeTimeMs(rpm);
}

/**
 * @brief Returns engine load according to selected engine_load_mode
 *
 */
float getEngineLoadT(DECLARE_ENGINE_PARAMETER_F) {
	efiAssert(engine!=NULL, "engine 2NULL", NAN);
	efiAssert(engineConfiguration!=NULL, "engineConfiguration 2NULL", NAN);
	switch (engineConfiguration->algorithm) {
	case LM_MAF:
		return getMafT(engineConfiguration);
	case LM_SPEED_DENSITY:
		// SD engine load is used for timing lookup but not for fuel calculation
	case LM_MAP:
		return getMap();
	case LM_ALPHA_N:
		return getTPS(PASS_ENGINE_PARAMETER_F);
	default:
		firmwareError("Unexpected engine load parameter: %d", engineConfiguration->algorithm);
		return -1;
	}
}

void setSingleCoilDwell(engine_configuration_s *engineConfiguration) {
	for (int i = 0; i < DWELL_CURVE_SIZE; i++) {
		engineConfiguration->sparkDwellBins[i] = 0;
		engineConfiguration->sparkDwell[i] = -1;
	}

	engineConfiguration->sparkDwellBins[5] = 1;
	engineConfiguration->sparkDwell[5] = 4;

	engineConfiguration->sparkDwellBins[6] = 4500;
	engineConfiguration->sparkDwell[6] = 4;

	engineConfiguration->sparkDwellBins[7] = 12500;
	engineConfiguration->sparkDwell[7] = 0;
}

#if EFI_ENGINE_CONTROL || defined(__DOXYGEN__)
OutputSignalList injectonSignals CCM_OPTIONAL;

void initializeIgnitionActions(angle_t advance, angle_t dwellAngle, IgnitionEventList *list DECLARE_ENGINE_PARAMETER_S) {
	efiAssertVoid(engineConfiguration->cylindersCount > 0, "cylindersCount");

	list->reset();

	for (int i = 0; i < CONFIG(cylindersCount); i++) {
		float localAdvance = advance + ENGINE(angleExtra[i]);
		io_pin_e pin = ENGINE(ignitionPin[i]);

		IgnitionEvent *event = list->add();

		if (!isPinAssigned(&outputs[(pin)])) {
			// todo: extact method for this index math
			warning(OBD_PCM_Processor_Fault, "no_pin_cl #%d", (int) pin - (int) SPARKOUT_1_OUTPUT + 1);
		}
		event->io_pin = pin;
		event->advance = localAdvance;

		findTriggerPosition(&event->dwellPosition, localAdvance - dwellAngle PASS_ENGINE_PARAMETER);
	}
}

void FuelSchedule::registerInjectionEvent(io_pin_e pin, float angle, bool_t isSimultanious DECLARE_ENGINE_PARAMETER_S) {
	if (!isSimultanious && !isPinAssigned(&outputs[(pin)])) {
		// todo: extact method for this index math
		warning(OBD_PCM_Processor_Fault, "no_pin_inj #%d", (int) pin - (int) INJECTOR_1_OUTPUT + 1);
	}

	InjectionEvent *ev = events.add();
	if (ev == NULL) {
		// error already reported
		return;
	}

	OutputSignal *actuator = injectonSignals.add();
	initOutputSignal(actuator, pin);

	ev->isSimultanious = isSimultanious;

	efiAssertVoid(TRIGGER_SHAPE(getSize()) > 0, "uninitialized TriggerShape");

	ev->actuator = actuator;

	findTriggerPosition(&ev->position, angle PASS_ENGINE_PARAMETER);
	hasEvents[ev->position.eventIndex] = true;
}

FuelSchedule::FuelSchedule() {
	clear();
}

void FuelSchedule::clear() {
	memset(hasEvents, 0, sizeof(hasEvents));
}

void FuelSchedule::addFuelEvents(injection_mode_e mode DECLARE_ENGINE_PARAMETER_S) {
	ActuatorEventList *list = &events;
	;
	list->reset();

	float baseAngle = engineConfiguration->globalTriggerAngleOffset + engineConfiguration->injectionAngle;

	switch (mode) {
	case IM_SEQUENTIAL:
		for (int i = 0; i < engineConfiguration->cylindersCount; i++) {
			io_pin_e pin = INJECTOR_PIN_BY_INDEX(getCylinderId(engineConfiguration->firingOrder, i) - 1);
			float angle = baseAngle
					+ (float) engineConfiguration->engineCycle * i / engineConfiguration->cylindersCount;
			registerInjectionEvent(pin, angle, false PASS_ENGINE_PARAMETER);
		}
		break;
	case IM_SIMULTANEOUS:
		for (int i = 0; i < engineConfiguration->cylindersCount; i++) {
			float angle = baseAngle
					+ (float) engineConfiguration->engineCycle * i / engineConfiguration->cylindersCount;

			/**
			 * We do not need injector pin here because we will control all injectors
			 * simultaniously
			 */
			registerInjectionEvent(IO_INVALID, angle, true PASS_ENGINE_PARAMETER);
		}
		break;
	case IM_BATCH:
		for (int i = 0; i < engineConfiguration->cylindersCount; i++) {
			int index = i % (engineConfiguration->cylindersCount / 2);
			io_pin_e pin = INJECTOR_PIN_BY_INDEX(index);
			float angle = baseAngle
					+ i * (float) engineConfiguration->engineCycle / engineConfiguration->cylindersCount;
			registerInjectionEvent(pin, angle, false PASS_ENGINE_PARAMETER);

			/**
			 * also fire the 2nd half of the injectors so that we can implement a batch mode on individual wires
			 */
			pin = INJECTOR_PIN_BY_INDEX(index + (engineConfiguration->cylindersCount / 2));
			registerInjectionEvent(pin, angle, false PASS_ENGINE_PARAMETER);
		}
		break;
	default:
		firmwareError("Unexpected injection mode %d", mode);
	}
}

#endif

/**
 * @return Spark dwell time, in milliseconds.
 */
float getSparkDwellMsT(int rpm DECLARE_ENGINE_PARAMETER_S) {
	if (isCrankingR(rpm)) {
		if (engineConfiguration->useConstantDwellDuringCranking) {
			return engineConfiguration->ignitionDwellForCrankingMs;
		} else {
			// technically this could be implemented via interpolate2d
			float angle = engineConfiguration->crankingChargeAngle;
			return getOneDegreeTimeMs(rpm) * angle;
		}
	}
	efiAssert(!cisnan(rpm), "invalid rpm", NAN);

	return interpolate2d(rpm, engineConfiguration->sparkDwellBins, engineConfiguration->sparkDwell, DWELL_CURVE_SIZE);
}

static int findAngleIndex(float angleOffset DECLARE_ENGINE_PARAMETER_S) {
	/**
	 * Here we rely on this to be pre-calculated, that's a performance optimization
	 */
	int engineCycleEventCount = engine->engineCycleEventCount;

	efiAssert(engineCycleEventCount > 0, "engineCycleEventCount", 0);

	uint32_t middle;
	uint32_t left = 0;
	uint32_t right = engineCycleEventCount - 1;

	/**
	 * Let's find the last trigger angle which is less or equal to the desired angle
	 * todo: extract binary search as template method?
	 */
	while (true) {
		middle = (left + right) / 2;
		float eventAngle = TRIGGER_SHAPE(eventAngles[middle]);

		if (middle == left) {
			return middle;
		}
		if (angleOffset < eventAngle) {
			right = middle;
		} else if (angleOffset > eventAngle) {
			left = middle;
		} else {
			return middle;
		}
	}
}

void findTriggerPosition(event_trigger_position_s *position, angle_t angleOffset DECLARE_ENGINE_PARAMETER_S) {
	angleOffset += CONFIG(globalTriggerAngleOffset);
	fixAngle(angleOffset);

	int index = triggerIndexByAngle[(int)angleOffset];
	angle_t eventAngle = TRIGGER_SHAPE(eventAngles[index]);
	if (angleOffset < eventAngle) {
		firmwareError("angle constraint violation in registerActuatorEventExt(): %f/%f", angleOffset, eventAngle);
		return;
	}

	position->eventIndex = index;
	position->eventAngle = eventAngle;
	position->angleOffset = angleOffset - eventAngle;
}

static int order_1_THEN_3_THEN_4_THEN2[] = { 1, 3, 4, 2 };

static int order_1_THEN_5_THEN_3_THEN_6_THEN_2_THEN_4[] = { 1, 5, 3, 6, 2, 4 };

static int order_1_8_4_3_6_5_7_2[] = { 1, 8, 4, 3, 6, 5, 7, 2 };

/**
 * @param index from zero to cylindersCount - 1
 * @return cylinderId from one to cylindersCount
 */
int getCylinderId(firing_order_e firingOrder, int index) {

	switch (firingOrder) {
	case FO_ONE_CYLINDER:
		return 1;
	case FO_1_THEN_3_THEN_4_THEN2:
		return order_1_THEN_3_THEN_4_THEN2[index];
	case FO_1_THEN_5_THEN_3_THEN_6_THEN_2_THEN_4:
		return order_1_THEN_5_THEN_3_THEN_6_THEN_2_THEN_4[index];
	case FO_1_8_4_3_6_5_7_2:
		return order_1_8_4_3_6_5_7_2[index];

	default:
		firmwareError("getCylinderId not supported for %d", firingOrder);
	}
	return -1;
}

io_pin_e getIgnitionPinForIndex(int i DECLARE_ENGINE_PARAMETER_S) {
	switch (CONFIG(ignitionMode)) {
	case IM_ONE_COIL:
		return SPARKOUT_1_OUTPUT;
		break;
	case IM_WASTED_SPARK: {
		int wastedIndex = i % (CONFIG(cylindersCount) / 2);
		int id = getCylinderId(CONFIG(firingOrder), wastedIndex) - 1;
		return (io_pin_e) (SPARKOUT_1_OUTPUT + id);
	}
		break;
	case IM_INDIVIDUAL_COILS:
		return (io_pin_e) ((int) SPARKOUT_1_OUTPUT + getCylinderId(CONFIG(firingOrder), i) - 1);
		break;

	default:
		firmwareError("unsupported ignitionMode %d in initializeIgnitionActions()", engineConfiguration->ignitionMode);
		return SPARKOUT_1_OUTPUT;
	}

}

#if EFI_ENGINE_CONTROL || defined(__DOXYGEN__)

void prepareOutputSignals(DECLARE_ENGINE_PARAMETER_F) {

	engine_configuration2_s *engineConfiguration2 = engine->engineConfiguration2;

	// todo: move this reset into decoder
	engine->triggerShape.calculateTriggerSynchPoint(engineConfiguration, engine);

	for (int i = 0; i < CONFIG(cylindersCount); i++) {
		ENGINE(angleExtra[i])= (float) CONFIG(engineCycle) * i / CONFIG(cylindersCount);

		ENGINE(ignitionPin[i]) = getIgnitionPinForIndex(i PASS_ENGINE_PARAMETER);

	}

	for (int angle = 0; angle < CONFIG(engineCycle); angle++) {
		triggerIndexByAngle[angle] = findAngleIndex(angle PASS_ENGINE_PARAMETER);
	}

	injectonSignals.reset();
	engineConfiguration2->crankingInjectionEvents.addFuelEvents(
			engineConfiguration->crankingInjectionMode PASS_ENGINE_PARAMETER);
	engineConfiguration2->injectionEvents.addFuelEvents(engineConfiguration->injectionMode PASS_ENGINE_PARAMETER);
}

#endif

void setFuelRpmBin(engine_configuration_s *engineConfiguration, float l, float r) {
	setTableBin(engineConfiguration->fuelRpmBins, FUEL_RPM_COUNT, l, r);
}

void setFuelLoadBin(engine_configuration_s *engineConfiguration, float l, float r) {
	setTableBin(engineConfiguration->fuelLoadBins, FUEL_LOAD_COUNT, l, r);
}

void setTimingRpmBin(engine_configuration_s *engineConfiguration, float l, float r) {
	setTableBin(engineConfiguration->ignitionRpmBins, IGN_RPM_COUNT, l, r);
}

void setTimingLoadBin(engine_configuration_s *engineConfiguration, float l, float r) {
	setTableBin(engineConfiguration->ignitionLoadBins, IGN_LOAD_COUNT, l, r);
}

int isInjectionEnabled(engine_configuration_s *engineConfiguration) {
	// todo: is this worth a method? should this be inlined?
	return engineConfiguration->isInjectionEnabled;
}
