/**
 * @file	engine.cpp
 *
 *
 * This might be a http://en.wikipedia.org/wiki/God_object but that's best way I can
 * express myself in C/C++. I am open for suggestions :)
 *
 * @date May 21, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "main.h"
#include "engine.h"
#include "engine_state.h"
#include "efiGpio.h"
#include "trigger_central.h"

#if EFI_PROD_CODE
#include "injector_central.h"
#else
#define isRunningBenchTest() true
#endif

static Logging logger;

extern NamedOutputPin outputs[IO_PIN_COUNT];

EXTERN_ENGINE
;

/**
 * We are executing these heavy (logarithm) methods from outside the trigger callbacks for performance reasons.
 */
void Engine::updateSlowSensors() {
	engineState.iat = getIntakeAirTemperature(this);
	engineState.clt = getCoolantTemperature(this);
}

void Engine::onTriggerEvent(uint64_t nowNt) {
	isSpinning = true;
	lastTriggerEventTimeNt = nowNt;
}

Engine::Engine() {
	lastTriggerEventTimeNt = 0;
	isCylinderCleanupMode = false;
	engineCycleEventCount = 0;
	stopEngineRequestTimeNt = 0;
}

void Engine::precalc(engine_configuration_s *engineConfiguration) {
	sparkTable.init(DWELL_CURVE_SIZE, sparkAtable, sparkBtable);
	sparkTable.preCalc(engineConfiguration->sparkDwellBins, engineConfiguration->sparkDwell);
}

void Engine::init() {
	initLogging(&logger, "engine");
}

static bool stopPin(io_pin_e pin) {
	NamedOutputPin *output = &outputs[(int)pin];
	if (output->getLogicValue()) {
		doSetOutputPinValue2(output, false);
		scheduleMsg(&logger, "turning off %s", output->name);
		return true;
	}
	return false;
}

bool Engine::stopPins() {
	bool result = false;
	for (int i = 0; i < engineConfiguration->cylindersCount; i++) {
		io_pin_e pin = (io_pin_e) ((int) INJECTOR_1_OUTPUT + i);
		result |= stopPin(pin);
		pin = (io_pin_e) ((int) SPARKOUT_1_OUTPUT + i);
		result |= stopPin(pin);
	}
	return result;
}

void Engine::watchdog() {
	if (!isSpinning) {
		if (!isRunningBenchTest() && stopPins()) {
			firmwareError("Some pins were turned off by 2nd pass watchdog");
		}
		return;
	}
	uint64_t nowNt = getTimeNowNt();
	/**
	 * Lowest possible cranking is about 240 RPM, that's 4 revolutions per second.
	 * 0.25 second is 250000 uS
	 *
	 * todo: better watch dog implementation should be implemented - see
	 * http://sourceforge.net/p/rusefi/tickets/96/
	 */
	if (nowNt - lastTriggerEventTimeNt < US2NT(250000LL)) {
		return;
	}
	isSpinning = false;
#if EFI_PROD_CODE || EFI_SIMULATOR
	scheduleMsg(&logger, "engine has STOPPED");
	triggerInfo(engine);
#endif

	stopPins();
}

StartupFuelPumping::StartupFuelPumping() {
	isTpsAbove50 = false;
	pumpsCounter = 0;
}

void StartupFuelPumping::setPumpsCounter(engine_configuration_s *engineConfiguration, int newValue) {
	if (pumpsCounter != newValue) {
		pumpsCounter = newValue;

		if (pumpsCounter == PUMPS_TO_PRIME) {
			scheduleMsg(&logger, "let's squirt prime pulse %f", pumpsCounter);
			pumpsCounter = 0;
		} else {
			scheduleMsg(&logger, "setPumpsCounter %d", pumpsCounter);
		}
	}
}

void StartupFuelPumping::update(DECLARE_ENGINE_PARAMETER_F) {
	if (engine->rpmCalculator.rpm(PASS_ENGINE_PARAMETER_F) == 0) {
		bool isTpsAbove50 = getTPS(PASS_ENGINE_PARAMETER_F) >= 50;

		if (this->isTpsAbove50 != isTpsAbove50) {
			setPumpsCounter(engineConfiguration, pumpsCounter + 1);
		}

	} else {
		/**
		 * Engine is not stopped - not priming pumping mode
		 */
		setPumpsCounter(engineConfiguration, 0);
		isTpsAbove50 = false;
	}
}

