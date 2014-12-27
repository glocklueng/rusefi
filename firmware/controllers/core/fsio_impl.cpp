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

static LECalculator evalCalc;
static LEElement evalPoolElements[LE_EVAL_POOL_SIZE];
static LEElementPool evalPool(evalPoolElements, LE_EVAL_POOL_SIZE);

#define SYS_ELEMENT_POOL_SIZE 128
#define UD_ELEMENT_POOL_SIZE 128

static LEElement sysElements[SYS_ELEMENT_POOL_SIZE];
LEElementPool sysPool(sysElements, SYS_ELEMENT_POOL_SIZE);

static LEElement userElements[UD_ELEMENT_POOL_SIZE];
LEElementPool userPool(userElements, UD_ELEMENT_POOL_SIZE);
static LEElement * fsioLogics[LE_COMMAND_COUNT] CCM_OPTIONAL;

static LEElement * acRelayLogic;
static LEElement * fuelPumpLogic;
static LEElement * radiatorFanLogic;
static LEElement * alternatorLogic;

EXTERN_ENGINE;



#if EFI_PROD_CODE || EFI_SIMULATOR
static Logging logger;

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

#endif

#if EFI_PROD_CODE || defined(__DOXYGEN__)

#include "pin_repository.h"
#include "pwm_generator.h"
// todo: that's about bench test mode, wrong header for sure!
#include "injector_central.h"

static void setFsioPin(const char *indexStr, const char *pinName) {
	int index = atoi(indexStr) - 1;
	if (index < 0 || index >= LE_COMMAND_COUNT) {
		scheduleMsg(&logger, "invalid index %d", index);
		return;
	}
	brain_pin_e pin = parseBrainPin(pinName);
	// todo: extract method - code duplication with other 'set_xxx_pin' methods?
	if (pin == GPIO_INVALID) {
		scheduleMsg(&logger, "invalid pin name [%s]", pinName);
		return;
	}
	boardConfiguration->fsioPins[index] = pin;
	scheduleMsg(&logger, "FSIO pin #%d [%s]", (index + 1), hwPortname(pin));
}
#endif


void setFsioExt(engine_configuration_s *engineConfiguration, int index, brain_pin_e pin, const char * exp, int freq) {
	board_configuration_s *boardConfiguration = &engineConfiguration->bc;

	boardConfiguration->fsioPins[index] = pin;
	strcpy(boardConfiguration->le_formulas[index], exp);
	boardConfiguration->fsioFrequency[index] = freq;
}

void setFsio(engine_configuration_s *engineConfiguration, int index, brain_pin_e pin, const char * exp) {
	setFsioExt(engineConfiguration, index, pin, exp, 0);
}

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

#if EFI_PROD_CODE || defined(__DOXYGEN__)

static SimplePwm fsioPwm[LE_COMMAND_COUNT] CCM_OPTIONAL;

static LECalculator calc;
extern LEElement * fsioLogics[LE_COMMAND_COUNT];

static void handleFsio(Engine *engine, int index) {
	if (boardConfiguration->fsioPins[index] == GPIO_UNASSIGNED)
		return;

	bool_t isPwmMode = boardConfiguration->fsioFrequency[index] != 0;

	io_pin_e pin = (io_pin_e) ((int) GPIO_0 + index);

	float fvalue = calc.getValue2(fsioLogics[index], engine);
	engine->engineConfiguration2->fsioLastValue[index] = fvalue;

	if (isPwmMode) {
		fsioPwm[index].setSimplePwmDutyCycle(fvalue);
	} else {
		int value = (int) fvalue;
		if (value != getOutputPinValue(pin)) {
			//		scheduleMsg(&logger, "setting %s %s", getIo_pin_e(pin), boolToString(value));
			setOutputPinValue(pin, value);
		}
	}
}

static void setPinState(io_pin_e ioPin, LEElement *element, Engine *engine) {
	if (element == NULL) {
		warning(OBD_PCM_Processor_Fault, "invalid expression for %s", getIo_pin_e(ioPin));
	} else {
		int value = calc.getValue2(element, engine);
		if (value != getOutputPinValue(ioPin)) {
			if (isRunningBenchTest())
				return; // let's not mess with bench testing
			scheduleMsg(&logger, "setting %s %s", getIo_pin_e(ioPin), boolToString(value));
			setOutputPinValue(ioPin, value);
		}
	}
}

static void showFsio(const char *msg, LEElement *element) {
	if (msg != NULL)
		scheduleMsg(&logger, "%s:", msg);
	while (element != NULL) {
		scheduleMsg(&logger, "action %d: fValue=%f iValue=%d", element->action, element->fValue, element->iValue);
		element = element->next;
	}
	scheduleMsg(&logger, "<end>");
}

static void showFsioInfo(void) {
	scheduleMsg(&logger, "sys used %d/user used %d", sysPool.getSize(), userPool.getSize());
	showFsio("a/c", acRelayLogic);
	showFsio("fuel", fuelPumpLogic);
	showFsio("fan", radiatorFanLogic);
	showFsio("alt", alternatorLogic);

	for (int i = 0; i < LE_COMMAND_COUNT; i++) {
		char * exp = boardConfiguration->le_formulas[i];
		if (exp[0] != 0) {
			/**
			 * in case of FSIO user interface indexes are starting with 0, the argument for that
			 * is the fact that the target audience is more software developers
			 */
			scheduleMsg(&logger, "FSIO #%d [%s] at %s@%dHz value=%f", i, exp,
					hwPortname(boardConfiguration->fsioPins[i]), boardConfiguration->fsioFrequency[i],
					engineConfiguration2->fsioLastValue[i]);
//			scheduleMsg(&logger, "user-defined #%d value=%f", i, engine->engineConfiguration2->fsioLastValue[i]);
			showFsio(NULL, fsioLogics[i]);
		}
	}
	for (int i = 0; i < LE_COMMAND_COUNT; i++) {
		float v = boardConfiguration->fsio_setting[i];
		if (!cisnan(v)) {
			scheduleMsg(&logger, "user property #%d: %f", i + 1, v);
		}
	}
}

/**
 * set_fsio_setting 0 0.11
 */
static void setFsioSetting(float indexF, float value) {
	int index = indexF;
	if (index < 0 || index >= LE_COMMAND_COUNT) {
		scheduleMsg(&logger, "invalid index %d", index);
		return;
	}
	engineConfiguration->bc.fsio_setting[index] = value;
	showFsioInfo();
}

static void setFsioFrequency(int index, int frequency) {
	index--;
	if (index < 0 || index >= LE_COMMAND_COUNT) {
		scheduleMsg(&logger, "invalid index %d", index);
		return;
	}
	boardConfiguration->fsioFrequency[index] = frequency;
	scheduleMsg(&logger, "Setting FSIO frequency %d on #%d", frequency, index + 1);
}

static void setUserOutput(const char *indexStr, const char *quotedLine, Engine *engine) {
	int index = atoi(indexStr) - 1;
	if (index < 0 || index >= LE_COMMAND_COUNT) {
		scheduleMsg(&logger, "invalid index %d", index);
		return;
	}
	char * l = unquote((char*) quotedLine);
	if (strlen(l) > LE_COMMAND_LENGTH - 1) {
		scheduleMsg(&logger, "Too long %d", strlen(l));
		return;
	}

	scheduleMsg(&logger, "setting user out #%d to [%s]", index + 1, l);
	strcpy(engine->engineConfiguration->bc.le_formulas[index], l);
	// this would apply the changes
	applyFsioConfiguration(PASS_ENGINE_PARAMETER_F);
	showFsioInfo();
}

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


void runFsio(void) {
	for (int i = 0; i < LE_COMMAND_COUNT; i++) {
		handleFsio(engine, i);
	}

#if EFI_FUEL_PUMP
	if (boardConfiguration->fuelPumpPin != GPIO_UNASSIGNED && engineConfiguration->isFuelPumpEnabled) {
		setPinState(FUEL_PUMP_RELAY, fuelPumpLogic, engine);
	}
#endif

	if (boardConfiguration->acRelayPin != GPIO_UNASSIGNED) {
		setPinState(AC_RELAY, acRelayLogic, engine);
	}

	if (boardConfiguration->alternatorControlPin != GPIO_UNASSIGNED) {
		setPinState(ALTERNATOR_SWITCH, alternatorLogic, engine);
	}

	if (boardConfiguration->fanPin != GPIO_UNASSIGNED) {
//		setPinState(FAN_RELAY, radiatorFanLogic, engine);
	}

}

static pin_output_mode_e defa = OM_DEFAULT;

void initFsioImpl(Engine *engine) {
	initLogging(&logger, "le");

#if EFI_FUEL_PUMP
	fuelPumpLogic = sysPool.parseExpression(FUEL_PUMP_LOGIC);
#endif

	acRelayLogic = sysPool.parseExpression(AC_RELAY_LOGIC);
	radiatorFanLogic = sysPool.parseExpression(FAN_CONTROL_LOGIC);

	alternatorLogic = sysPool.parseExpression(ALTERNATOR_LOGIC);

#if EFI_PROD_CODE || defined(__DOXYGEN__)
	for (int i = 0; i < LE_COMMAND_COUNT; i++) {
		brain_pin_e brainPin = boardConfiguration->fsioPins[i];

		if (brainPin != GPIO_UNASSIGNED) {
			//mySetPadMode2("user-defined", boardConfiguration->gpioPins[i], PAL_STM32_MODE_OUTPUT);

			io_pin_e pin = (io_pin_e) ((int) GPIO_0 + i);

			int frequency = boardConfiguration->fsioFrequency[i];
			if (frequency == 0) {
				outputPinRegisterExt2(getPinName(pin), pin, boardConfiguration->fsioPins[i], &defa);
			} else {
				startSimplePwmExt(&fsioPwm[i], "FSIO", brainPin, pin, frequency, 0.5f, applyPinState);
			}
		}
	}

#endif /* EFI_PROD_CODE */

	addConsoleActionSSP("set_fsio", (VoidCharPtrCharPtrVoidPtr) setUserOutput, engine);
	addConsoleActionSS("set_fsio_pin", (VoidCharPtrCharPtr) setFsioPin);
	addConsoleActionII("set_fsio_frequency", (VoidIntInt) setFsioFrequency);
	addConsoleActionFF("set_fsio_setting", setFsioSetting);
	addConsoleAction("fsioinfo", showFsioInfo);

	addConsoleActionSP("eval", (VoidCharPtrVoidPtr) eval, engine);
}

#endif

#endif /* EFI_FSIO */
