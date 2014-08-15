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

extern Engine engine;
extern engine_configuration_s *engineConfiguration;

#define LCD_WIDTH 20

char * appendStr(char *ptr, const char *suffix) {
	for (uint32_t i = 0; i < strlen(suffix); i++) {
		*ptr++ = suffix[i];
	}
	return ptr;
}

static void prepareVBattMapLine(char *buffer) {
	char *ptr = buffer;
	*ptr++ = 'V';
	ptr = ftoa(ptr, getVBatt(), 10.0f);

	ptr = appendStr(ptr, " M");
	ptr = ftoa(ptr, getRawMap(), 10.0f);

}

static void prepareCltIatTpsLine(char *buffer) {
	char *ptr = buffer;
	*ptr++ = 'C';
	ptr = ftoa(ptr, getCoolantTemperature(), 10.0f);

	ptr = appendStr(ptr, " C");
	ptr = ftoa(ptr, getIntakeAirTemperature(), 10.0f);

	ptr = appendStr(ptr, " TP");
	ptr = itoa10(ptr, (int) getTPS());
}

static const char* algorithmStr[] = { "MAF", "TPS", "MAP", "SD" };
static const char* ignitionModeStr[] = { "1C", "IND", "WS" };

static const char *getPinShortName(io_pin_e pin) {
	switch (pin) {
	case ALTERNATOR_SWITCH:
		return "AL";
	case FUEL_PUMP_RELAY:
		return "FP";
	case FAN_RELAY:
		return "FN";
	}
	firmwareError("No short name for %d", (int) pin);
	return "";
}

static void prepareInfoLine(char *buffer) {
	char *ptr = buffer;

	ptr = appendStr(ptr, algorithmStr[engineConfiguration->algorithm]);

	ptr = appendStr(ptr, " ");
	ptr = appendStr(ptr, ignitionModeStr[engineConfiguration->ignitionMode]);

	ptr = appendStr(ptr, " ");
}

static void prepareStatusLine(char *buffer) {
	char *ptr = buffer;

}

static char buffer[LCD_WIDTH + 4];
static char dateBuffer[30];

static void prepareCurrentSecondLine() {
	switch (getTimeNowSeconds() % 3) {
	case 0:
		prepareCltIatTpsLine(buffer);
		break;
	case 1:
		prepareInfoLine(buffer);
		break;
	case 2:
		prepareVBattMapLine(buffer);
		break;
	}
}

void updateHD44780lcd(void) {

	lcd_HD44780_set_position(0, 9);
	lcd_HD44780_print_char('R');
	lcd_HD44780_set_position(0, 10);

	char * ptr = itoa10(buffer, getRpm());
	ptr[0] = 0;
	int len = ptr - buffer;
	for (int i = 0; i < 6 - len; i++) {
		lcd_HD44780_print_char(' ');
	}
	lcd_HD44780_print_string(buffer);

	lcd_HD44780_set_position(1, 0);
	memset(buffer, ' ', LCD_WIDTH);
	memcpy(buffer, getWarninig(), LCD_WIDTH);
	buffer[LCD_WIDTH] = 0;
	lcd_HD44780_print_string(buffer);

	if (engineConfiguration->HD44780height < 3) {
		return;
	}

	memset(buffer, ' ', LCD_WIDTH);
	prepareCurrentSecondLine();
	buffer[LCD_WIDTH] = 0;

	lcd_HD44780_set_position(2, 0);
	lcd_HD44780_print_string(buffer);

#if EFI_PROD_CODE
	dateToString(dateBuffer);
	lcd_HD44780_set_position(1, 0);
	lcd_HD44780_print_string(dateBuffer);
#endif /* EFI_PROD_CODE */
}
