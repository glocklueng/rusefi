/**
 * @file fsio_impl.cpp
 * @brief FSIO as it's used for GPIO
 *
 * @date Oct 5, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"

#if EFI_FSIO || defined(__DOXYGEN__)

#include "fsio_impl.h"
#include "allsensors.h"
#include "rpm_calculator.h"
#include "efiGpio.h"

/**
 * Here we define all rusEfi-specific methods
 */
static LENameOrdinalPair leRpm(LE_METHOD_RPM, "rpm");
static LENameOrdinalPair leTps(LE_METHOD_TPS, "tps");
static LENameOrdinalPair leMaf(LE_METHOD_MAF, "maf");
static LENameOrdinalPair leVBatt(LE_METHOD_VBATT, "vbatt");
static LENameOrdinalPair leFan(LE_METHOD_FAN, "fan");
static LENameOrdinalPair leCoolant(LE_METHOD_COOLANT, "coolant");
static LENameOrdinalPair leAcToggle(LE_METHOD_AC_TOGGLE, "ac_on_switch");
static LENameOrdinalPair leFanOnSetting(LE_METHOD_FAN_ON_SETTING, "fan_on_setting");
static LENameOrdinalPair leFanOffSetting(LE_METHOD_FAN_OFF_SETTING, "fan_off_setting");
static LENameOrdinalPair leTimeSinceBoot(LE_METHOD_TIME_SINCE_BOOT, "time_since_boot");
static LENameOrdinalPair leFsioSsetting(LE_METHOD_FSIO_SETTING, "fsio_setting");

#define LE_EVAL_POOL_SIZE 32

#if EFI_PROD_CODE || EFI_SIMULATOR
static Logging logger;
#endif

static LECalculator evalCalc;
static LEElement evalPoolElements[LE_EVAL_POOL_SIZE];
static LEElementPool evalPool(evalPoolElements, LE_EVAL_POOL_SIZE);

#define SYS_ELEMENT_POOL_SIZE 128
#define UD_ELEMENT_POOL_SIZE 128

static LEElement sysElements[SYS_ELEMENT_POOL_SIZE];
LEElementPool sysPool(sysElements, SYS_ELEMENT_POOL_SIZE);

static LEElement userElements[UD_ELEMENT_POOL_SIZE];
LEElementPool userPool(userElements, UD_ELEMENT_POOL_SIZE);
LEElement * fsioLogics[LE_COMMAND_COUNT] CCM_OPTIONAL;

void setFsioExt(engine_configuration_s *engineConfiguration, int index, brain_pin_e pin, const char * exp, int freq) {
	board_configuration_s *boardConfiguration = &engineConfiguration->bc;

	boardConfiguration->fsioPins[index] = pin;
	strcpy(boardConfiguration->le_formulas[index], exp);
	boardConfiguration->fsioFrequency[index] = freq;
}

void setFsio(engine_configuration_s *engineConfiguration, int index, brain_pin_e pin, const char * exp) {
	setFsioExt(engineConfiguration, index, pin, exp, 0);
}

EXTERN_ENGINE;

void applyFsioConfiguration(DECLARE_ENGINE_PARAMETER_F) {
	board_configuration_s * boardConfiguration = &engineConfiguration->bc;
	for (int i = 0; i < LE_COMMAND_COUNT; i++) {
		brain_pin_e brainPin = boardConfiguration->fsioPins[i];

		if (brainPin != GPIO_UNASSIGNED) {
			const char *formula = boardConfiguration->le_formulas[i];
			LEElement *logic = userPool.parseExpression(formula);
			if (logic == NULL) {
				warning(OBD_PCM_Processor_Fault, "parsing [%s]", formula);
			}

			fsioLogics[i] = logic;
		}
	}
}

#if (EFI_PROD_CODE || EFI_SIMULATOR) || defined(__DOXYGEN__)

static void eval(char *line, Engine *engine) {
	line = unquote(line);
	scheduleMsg(&logger, "Parsing [%s]", line);
	evalPool.reset();
	LEElement * e = evalPool.parseExpression(line);
	if (e == NULL) {
		scheduleMsg(&logger, "parsing failed");
	} else {
		float result = evalCalc.getValue2(e, engine);
		scheduleMsg(&logger, "Eval result: %f", result);
	}
}

float getLEValue(Engine *engine, calc_stack_t *s, le_action_e action) {
	efiAssert(engine!=NULL, "getLEValue", NAN);
	switch (action) {
	case LE_METHOD_FAN:
		return getOutputPinValue(FAN_RELAY);
	case LE_METHOD_AC_TOGGLE:
		return getAcToggle(engine);
	case LE_METHOD_COOLANT:
		return getCoolantTemperature(engine);
	case LE_METHOD_INTAKE_AIR:
		return getIntakeAirTemperature(engine);
	case LE_METHOD_RPM:
		return engine->rpmCalculator.rpm();
	case LE_METHOD_TIME_SINCE_BOOT:
		return getTimeNowSeconds();
	case LE_METHOD_FAN_OFF_SETTING:
		return engine->engineConfiguration->fanOffTemperature;
	case LE_METHOD_FAN_ON_SETTING:
		return engine->engineConfiguration->fanOnTemperature;
	case LE_METHOD_VBATT:
		return getVBatt(engine->engineConfiguration);
	default:
		firmwareError("FSIO unexpected %d", action);
		return NAN;
	}
}

void initFsioImpl(Engine *engine) {
	initLogging(&logger, "le");
	addConsoleActionSP("eval", (VoidCharPtrVoidPtr) eval, engine);
}

#endif

#endif /* EFI_FSIO */
