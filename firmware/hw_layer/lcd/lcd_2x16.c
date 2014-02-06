/**
 * @file lcd_2x16.c
 *
 *
 * http://forum.chibios.org/phpbb/viewtopic.php?f=16&t=1584
 *	Date:	13.12.2013
 */

#include "ch.h"
#include "hal.h"

#include "lcd_2x16.h"
#include "pin_repository.h"

const uint8_t lcd_2x16_decode[] =
{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

enum
{
	LCD_2X16_RESET = 0x30,
	LCD_2X16_4_BIT_BUS = 0x20,
	LCD_2X16_8_BIT_BUS = 0x30,
	LCD_2X16_LINE_ONE = 0x20,
	LCD_2X16_LINES_TWO = 0x28,
	LCD_2X16_FONT_5X8 = 0x20,
	LCD_2X16_FONT_5X10 = 0x24,
	LCD_2X16_DISPLAY_CLEAR = 0x01,
	LCD_2X16_DISPLAY_HOME = 0x02,
	LCD_2X16_DISPLAY_ON = 0x0C,
	LCD_2X16_DISPLAY_RIGHT = 0x1C,
	LCD_2X16_DISPLAY_LEFT = 0x18,
	LCD_2X16_DISPLAY_SHIFT = 0x05,
	LCD_2X16_CURSOR_ON = 0x0A,
	LCD_2X16_CURSOR_BLINK = 0x09, 
	LCD_2X16_CURSOR_RIGHT = 0x14,
	LCD_2X16_CURSOR_LEFT = 0x10, 
	LCD_2X16_SHIFT_RIGHT = 0x06,
	LCD_2X16_SHIFT_LEFT = 0x04,
	LCD_2X16_CGRAM_ADDR = 0x40,
	LCD_2X16_DDRAM_ADDR = 0x80,
	LCD_2X16_BUSY_FLAG = 0x80,
	LCD_2X16_NEXT_LINE = 0x40,
	LCD_2X16_COMMAND = 0x01,
	LCD_2X16_DATA = 0x00,
} lcd_2x16_command;

//-----------------------------------------------------------------------------
void lcd_2x16_write(uint8_t data)
{


	pal_lld_clearport(LCD_PORT, LCD_PINS_DATA);

	palSetPad(LCD_PORT, LCD_PIN_E);

#ifdef LCD_PIN_OFFSET
	pal_lld_setport(LCD_PORT, ((LCD_PINS_DATA | (data & 0xF0))<<LCD_PIN_OFFSET) );
#else
	if (data & 0x80)
		palSetPad(LCD_PORT, LCD_PIN_DB7);

	if (data & 0x40)
		palSetPad(LCD_PORT, LCD_PIN_DB6);

	if (data & 0x20)
		palSetPad(LCD_PORT, LCD_PIN_DB5);

	if (data & 0x10)
		palSetPad(LCD_PORT, LCD_PIN_DB4);
#endif

	chThdSleepMicroseconds(1);
	palClearPad(LCD_PORT, LCD_PIN_E);
}

//-----------------------------------------------------------------------------
void lcd_2x16_write_command(uint8_t data)
{
	palClearPad(LCD_PORT, LCD_PIN_RS);

	lcd_2x16_write(data);
	lcd_2x16_write(data << 4);
}

//-----------------------------------------------------------------------------
void lcd_2x16_write_data(uint8_t data)
{
	palSetPad(LCD_PORT, LCD_PIN_RS);

	lcd_2x16_write(data);
	lcd_2x16_write(data << 4);

	palClearPad(LCD_PORT, LCD_PIN_RS);
}

//-----------------------------------------------------------------------------
void lcd_2x16_set_position(uint8_t row, uint8_t colum)
{
	uint8_t position = LCD_2X16_DDRAM_ADDR;

	if (row > 0)
	{
		position |= LCD_2X16_NEXT_LINE;
	}

	lcd_2x16_write_command(position | colum);
}

//-----------------------------------------------------------------------------
void lcd_2x16_print_char(uint8_t data)
{
	if (data == '\n')
	{
		lcd_2x16_write_command(LCD_2X16_DDRAM_ADDR | LCD_2X16_NEXT_LINE);
	}
	else
	{
		lcd_2x16_write_data(data);
	}
}

//-----------------------------------------------------------------------------
void lcd_2x16_print_string(uint8_t * string)
{
	while (*string != 0x00)
	{
		lcd_2x16_print_char(*string++);
	}
}

//-----------------------------------------------------------------------------
void lcd_2x16_init(void)
{
	mySetPadMode("lcd", LCD_PORT, LCD_PIN_RS, PAL_MODE_OUTPUT_PUSHPULL);


	palSetGroupMode(LCD_PORT, LCD_PINS, 0, LCD_PORT_MODE);
	pal_lld_clearport(LCD_PORT, LCD_PINS);

	// LCD needs some time to wake up
	chThdSleepMilliseconds(50);

	lcd_2x16_write(0x30);
	chThdSleepMilliseconds(1);

	lcd_2x16_write(0x30);

	lcd_2x16_write(0x20);	// 4 bit, 2 line
	chThdSleepMicroseconds(40);

	lcd_2x16_write(0x20);	// 4 bit, 2 line
	lcd_2x16_write(0x80);
	chThdSleepMicroseconds(40);

	lcd_2x16_write(0x00);	// display and cursor control
	lcd_2x16_write(0xC0);
	chThdSleepMicroseconds(40);

	lcd_2x16_write(0x00);	// display clear
	lcd_2x16_write(0x01);
	chThdSleepMilliseconds(2);

	lcd_2x16_write(0x00);	// entry mode set
	lcd_2x16_write(0x60);
}
