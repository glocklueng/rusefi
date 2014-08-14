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
#include "thermistors.h"
#include "engine.h"
#include "rtc_helper.h"

extern Engine engine;

static char buffer[10];
static char dateBuffer[30];

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

	lcd_HD44780_set_position(2, 0);
	lcd_HD44780_print_char('C');

	ftoa(buffer, getCoolantTemperature(), 100.0f);
	lcd_HD44780_print_string(buffer);

#if EFI_PROD_CODE
	dateToString(dateBuffer);
	lcd_HD44780_set_position(1, 0);
	lcd_HD44780_print_string(dateBuffer);
#endif /* EFI_PROD_CODE */
}
