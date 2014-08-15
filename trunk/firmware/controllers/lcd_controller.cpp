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

extern Engine engine;
extern engine_configuration_s *engineConfiguration;

char * appendStr(char *ptr, const char *suffix) {
	for (uint32_t i = 0; i < strlen(suffix); i++) {
		*ptr++ = suffix[i];
	}
	return ptr;
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

static const char* algorithmStr[] = {"MAF", "TPS", "MAP", "SD"};

static void prepareInfoLine(char *buffer) {
	char *ptr = buffer;

	ptr = appendStr(ptr, " ");
	ptr = appendStr(ptr, algorithmStr[engineConfiguration->algorithm]);

	ptr = appendStr(ptr, " ");

	ptr = appendStr(ptr, " ");

}

static char buffer[24];
static char dateBuffer[30];

static void prepareCurrentSecondLine() {
	switch (getTimeNowSeconds() % 2) {
	case 0:
		prepareCltIatTpsLine(buffer);
		break;
	case 1:
		prepareInfoLine(buffer);
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

	memset(buffer, ' ', 20);

	prepareCurrentSecondLine();
	buffer[20] = 0;

	lcd_HD44780_set_position(2, 0);
	lcd_HD44780_print_string(buffer);

#if EFI_PROD_CODE
	dateToString(dateBuffer);
	lcd_HD44780_set_position(1, 0);
	lcd_HD44780_print_string(dateBuffer);
#endif /* EFI_PROD_CODE */
}
