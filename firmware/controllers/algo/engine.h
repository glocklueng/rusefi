/**
 * @file	engine.h
 *
 * @date May 21, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */
#ifndef ENGINE_H_
#define ENGINE_H_

#include "main.h"
#include "engine_configuration.h"
#include "rpm_calculator.h"

#include "global.h"
#include "engine_configuration.h"
#include "event_registry.h"
#include "trigger_structure.h"
#include "table_helper.h"
#include "listener_array.h"
#include "accel_enrichment.h"

/**
 * This class knows about when to inject fuel
 */
class FuelSchedule {
public:
	FuelSchedule();
	ActuatorEventList events;

	/**
	 * this method schedules all fuel events for an engine cycle
	 */
	void addFuelEvents(injection_mode_e mode DECLARE_ENGINE_PARAMETER_S);

	/**
	 * This is a performance optimization for https://sourceforge.net/p/rusefi/tickets/64/
	 * TODO: better data structure? better algorithm?
	 */
	uint8_t hasEvents[PWM_PHASE_MAX_COUNT];
	/**
	 * How many trigger events have injection? This depends on fuel strategy & trigger shape
	 */
	int eventsCount;
private:
	void clear();
	void registerInjectionEvent(NamedOutputPin *output, float angle, bool_t isSimultanious DECLARE_ENGINE_PARAMETER_S);
};

/**
 * this part of the structure is separate just because so far
 * these fields are not integrated with Tuner Studio. Step by step :)
 */
class engine_configuration2_s {
	// todo: move these fields into Engine class, eliminate this class
public:
	engine_configuration2_s();

#if EFI_ENGINE_CONTROL || defined(__DOXYGEN__)
	FuelSchedule crankingInjectionEvents;
	FuelSchedule injectionEvents;
#endif

	float fsioLastValue[LE_COMMAND_COUNT];

	/**
	 * We are alternating two event lists in order to avoid a potential issue around revolution boundary
	 * when an event is scheduled within the next revolution.
	 */
	IgnitionEventList ignitionEvents[2];
};


class EngineState {
public:
	/**
	 * WIP: accessing these values here would be a performance optimization since log() function needed for
	 * thermistor logic is relatively heavy
	 * Access to these two fields is not synchronized in any way - that should work since float read/write are atomic.
	 */
	float iat;
	float clt;

	angle_t mapAveragingStart;
	angle_t mapAveragingDuration;

	// spark-related
	float sparkDwell;
	float timingAdvance;

	// fuel-related;
	float iatFuelCorrection;
	float cltFuelCorrection;
	float injectorLag;

	// speed density
	float tChargeK;
	float currentVE;
	float targerAFR;

	angle_t injectionAngle;
};

class RpmCalculator;

typedef struct {
	ThermistorConf *config;
	adc_channel_e channel;
} Thermistor;

#define MAF_DECODING_CACHE_SIZE 256

#define MAF_DECODING_CACHE_MULT (MAF_DECODING_CACHE_SIZE / 5.0)

typedef struct {
	uint32_t beforeIgnitionMath;
	uint32_t ignitionMathTime;

	uint32_t beforeIgnitionSch;
	uint32_t ignitionSchTime;

	uint32_t beforeInjectonSch;
	uint32_t injectonSchTime;

	uint32_t beforeZeroTest;
	uint32_t zeroTestTime;

	uint32_t beforeAdvance;
	uint32_t advanceTime;

	uint32_t beforeFuelCalc;
	uint32_t fuelCalcTime;

	uint32_t beforeMapAveragingCb;
	uint32_t mapAveragingCbTime;

	uint32_t beforeHipCb;
	uint32_t hipCbTime;

	uint32_t beforeRpmCb;
	uint32_t rpmCbTime;
} monitoring_timestamps_s;

class Engine;

typedef void (*configuration_callback_t)(Engine*);

class Engine {
public:
	Engine(persistent_config_s *config);
	void init();
	RpmCalculator rpmCalculator;
	persistent_config_s *config;
	engine_configuration_s *engineConfiguration;
	engine_configuration2_s *engineConfiguration2;

	/**
	 * this is about 'stopengine' command
	 */
	uint64_t stopEngineRequestTimeNt;

	Thermistor iat;
	Thermistor clt;

	AccelEnrichmemnt mapAccelEnrichment;
	AccelEnrichmemnt tpsAccelEnrichment;

	/**
	 * Fuel injection duration for current engine cycle
	 */
	floatms_t fuelMs;

	/**
	 * ignition dwell duration as crankshaft angle
	 */
	angle_t dwellAngle;
	angle_t advance;

	void periodicFastCallback(DECLARE_ENGINE_PARAMETER_F);

	bool_t clutchUpState;
	bool_t clutchDownState;

	bool_t isRunningPwmTest;

	bool_t knockNow;
	bool_t knockEver;

	/**
	 * are we running any kind of functional test? this affect
	 * some areas
	 */
	bool_t isTestMode;

	TriggerShape triggerShape;

	/**
	 * pre-calculated offset for given sequence index within engine cycle
	 * (not cylinder ID)
	 * todo: better name?
	 */
	angle_t angleExtra[IGNITION_PIN_COUNT];
	/**
	 * pre-calculated reference to which output pin should be used for
	 * given sequence index within engine cycle
	 */
	NamedOutputPin *ignitionPin[IGNITION_PIN_COUNT];

	void onTriggerEvent(uint64_t nowNt);
	EngineState engineState;
	uint64_t lastTriggerEventTimeNt;

	/**
	 * this value depends on a slow-changing VBatt value, so
	 * we update it once in a while
	 */
	float injectorLagMs;

	/**
	 * This coefficient translates ADC value directly into voltage adjusted according to
	 * voltage divider configuration. This is a future (?) performance optimization.
	 */
	float adcToVoltageInputDividerCoefficient;

	/**
	 * This field is true if we are in 'cylinder cleanup' state right now
	 * see isCylinderCleanupEnabled
	 */
	bool_t isCylinderCleanupMode;

	/**
	 * pre-calculating this value is a performance optimization
	 */
	int engineCycleEventCount;

	/**
	 * fast spark dwell time interpolation helper
	 * todo: finish the implementation and
	 */
	Table2D<DWELL_CURVE_SIZE> sparkTable;

	/**
	 * fast kg/hour MAF decoding lookup table with ~0.2 volt step
	 * This table is build based on MAF decoding curve
	 */
	float mafDecodingLookup[MAF_DECODING_CACHE_SIZE];

	void preCalculate();
	void addConfigurationListener(configuration_callback_t callback);

	void updateSlowSensors();
	void watchdog();

	/**
	 * here we have all the listeners which should be notified about a configuration
	 * change
	 */
	IntListenerArray configurationListeners;

	monitoring_timestamps_s m;

private:
	/**
	 * By the way:
	 * 'cranking' means engine is not stopped and the rpm are below crankingRpm
	 * 'running' means RPM are above crankingRpm
	 * 'spinning' means the engine is not stopped
	 */
	bool_t isSpinning;
	bool_t stopPins();
};

/**
 * 6 crossing over 50% TPS means pressing and releasing three times
 */
#define PUMPS_TO_PRIME 6

class StartupFuelPumping {
public:
	StartupFuelPumping();
	void update(DECLARE_ENGINE_PARAMETER_F);
	bool isTpsAbove50;
	int pumpsCounter;
private:
	void setPumpsCounter(engine_configuration_s *engineConfiguration, int newValue);
};

void prepareShapes(DECLARE_ENGINE_PARAMETER_F);
void resetConfigurationExt(Logging * logger, engine_type_e engineType DECLARE_ENGINE_PARAMETER_S);
void applyNonPersistentConfiguration(Logging * logger DECLARE_ENGINE_PARAMETER_S);
void prepareOutputSignals(DECLARE_ENGINE_PARAMETER_F);

#endif /* ENGINE_H_ */
