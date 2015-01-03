/**
 * @file lcd_controller.cpp
 *
 * @date Aug 14, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "lcd_controller.h"
#include "lcd_HD44780.h"
#include "efilib.h"
#include "rpm_calculator.h"
#include "allsensors.h"
#include "engine.h"
#include "rtc_helper.h"
#include "io_pins.h"
#include "efiGpio.h"
#include "svnversion.h"
#include "joystick.h"

EXTERN_ENGINE
;

#define DISP_LINES (engineConfiguration->HD44780height - 1)

static int infoIndex = 0;
static int cursorY = 0;

void onJoystick(joystick_button_e button) {
	if (cursorY == TOTAL_OPTIONS - 1) {
		cursorY = infoIndex = 0;
	} else {
		cursorY++;
		if (cursorY - DISP_LINES >= infoIndex)
			infoIndex++;
	}
}

char * appendStr(char *ptr, const char *suffix) {
	for (uint32_t i = 0; i < efiStrlen(suffix); i++) {
		*ptr++ = suffix[i];
	}
	return ptr;
}

static char * prepareVBattMapLine(engine_configuration_s *engineConfiguration, char *buffer) {
	char *ptr = buffer;
	*ptr++ = 'V';
	ptr = ftoa(ptr, getVBatt(engineConfiguration), 10.0f);

	ptr = appendStr(ptr, " M");
	ptr = ftoa(ptr, getRawMap(), 10.0f);
	return ptr;
}

static char * prepareCltIatTpsLine(Engine *engine, char *buffer) {
	char *ptr = buffer;
	*ptr++ = 'C';

	ptr = appendStr(ptr, " TP");
	ptr = itoa10(ptr, (int) getTPS(PASS_ENGINE_PARAMETER_F));
	return ptr;
}

static const char* algorithmStr[] = { "MAF", "TPS", "MAP", "SD" };
static const char* ignitionModeStr[] = { "1C", "IND", "WS" };
static const char* injectionModeStr[] = { "Sim", "Seq", "Bch" };
static const char* idleModeStr[] = { "I:A", "I:M" };

static const char *getPinShortName(io_pin_e pin) {
	switch (pin) {
	case ALTERNATOR_SWITCH:
		return "AL";
	case FUEL_PUMP_RELAY:
		return "FP";
	case FAN_RELAY:
		return "FN";
	case O2_HEATER:
		return "O2H";
	default:
		firmwareError("No short name for %d", (int) pin);
		return "";
	}
}

char * appendPinStatus(char *buffer, io_pin_e pin) {
	char *ptr = appendStr(buffer, getPinShortName(pin));
	int state = getOutputPinValue(pin);
	// todo: should we handle INITIAL_PIN_STATE?
	if (state) {
		return appendStr(ptr, ":Y ");
	} else {
		return appendStr(ptr, ":n ");
	}
}

static char * prepareInfoLine(engine_configuration_s *engineConfiguration, char *buffer) {
	char *ptr = buffer;

	ptr = appendStr(ptr, " ");
	ptr = appendStr(ptr, ignitionModeStr[engineConfiguration->ignitionMode]);

	ptr = appendStr(ptr, " ");
	ptr = appendStr(ptr, injectionModeStr[engineConfiguration->injectionMode]);

	ptr = appendStr(ptr, " ");
	ptr = appendStr(ptr, idleModeStr[engineConfiguration->idleMode]);

	ptr = appendStr(ptr, " ");
	return ptr;
}

static char * prepareStatusLine(char *buffer) {
	char *ptr = buffer;

	ptr = appendPinStatus(ptr, FUEL_PUMP_RELAY);
	ptr = appendPinStatus(ptr, FAN_RELAY);
	ptr = appendPinStatus(ptr, O2_HEATER);
	return ptr;
}

static char buffer[MAX_LCD_WIDTH + 4];
static char dateBuffer[30];

static void showLine(lcd_line_e line) {
	switch (line) {
	case LL_VERSION:
		lcd_HD44780_print_string("version ");
		lcd_HD44780_print_string(VCS_VERSION);
		return;
	case LL_CONFIG:
		lcd_HD44780_print_string("config ");
		lcd_HD44780_print_string(getConfigurationName(engine->engineConfiguration->engineType));
		return;
	case LL_RPM:
		lcd_HD44780_print_string("RPM ");
		itoa10(buffer, getRpmE(engine));
		lcd_HD44780_print_string(buffer);
		return;
	case LL_CLT_TEMPERATURE:
		lcd_HD44780_print_string("Coolant ");
		ftoa(buffer, getCoolantTemperature(engine), 10.0f);
		lcd_HD44780_print_string(buffer);
		return;
	case LL_IAT_TEMPERATURE:
		lcd_HD44780_print_string("Intake Air ");
		ftoa(buffer, getIntakeAirTemperature(engine), 10.0f);
		lcd_HD44780_print_string(buffer);
		return;
	case LL_ALGORITHM:
		lcd_HD44780_print_string(getEngine_load_mode_e(engineConfiguration->algorithm));
		return;
	}
}

void updateHD44780lcd(Engine *engine) {
	for (int i = infoIndex; i < infoIndex + DISP_LINES; i++) {
		lcd_HD44780_set_position(i - infoIndex, 0);

		lcd_HD44780_print_char(cursorY == i ? '*' : ' ');

		showLine((lcd_line_e) i);

		int column = getCurrentHD44780column();

		for (int r = column; r < 20; r++) {
			lcd_HD44780_print_char(' ');
		}
	}

//	lcd_HD44780_set_position(0, 0);
//	bool_t isEven = getTimeNowSeconds() % 2 == 0;
//
//	if (isEven) {
//
//	} else {
//
//	}
//
//	lcd_HD44780_set_position(0, 9);
//	/**
//	 * this would blink so that we know the LCD is alive
//	 */
//	if (isEven) {
//		lcd_HD44780_print_char('R');
//	} else {
//		lcd_HD44780_print_char(' ');
//	}
//	lcd_HD44780_set_position(0, 10);
//
//	char * ptr = itoa10(buffer, getRpmE(engine));
//	ptr[0] = 0;
//	int len = ptr - buffer;
//	for (int i = 0; i < 6 - len; i++) {
//		lcd_HD44780_print_char(' ');
//	}
//	lcd_HD44780_print_string(buffer);
//
//	if (hasFirmwareError()) {
//		memcpy(buffer, getFirmwareError(), LCD_WIDTH);
//		buffer[LCD_WIDTH] = 0;
//		lcd_HD44780_set_position(1, 0);
//		lcd_HD44780_print_string(buffer);
//		return;
//	}
//
//	lcd_HD44780_set_position(1, 0);
//	memset(buffer, ' ', LCD_WIDTH);
//	memcpy(buffer, getWarninig(), LCD_WIDTH);
//	buffer[LCD_WIDTH] = 0;
//	lcd_HD44780_print_string(buffer);
//
//	if (engineConfiguration->HD44780height < 3) {
//		return;
//	}
//
//	int index = (getTimeNowSeconds() / 2) % (NUMBER_OF_DIFFERENT_LINES / 2);
//
//	prepareCurrentSecondLine(engine, index);
//	buffer[LCD_WIDTH] = 0;
//	lcd_HD44780_set_position(2, 0);
//	lcd_HD44780_print_string(buffer);
//
//	prepareCurrentSecondLine(engine, index + NUMBER_OF_DIFFERENT_LINES / 2);
//	buffer[LCD_WIDTH] = 0;
//	lcd_HD44780_set_position(3, 0);
//	lcd_HD44780_print_string(buffer);
//
//#if EFI_PROD_CODE
//	dateToString(dateBuffer);
//	lcd_HD44780_set_position(1, 0);
//	lcd_HD44780_print_string(dateBuffer);
//#endif /* EFI_PROD_CODE */
}
