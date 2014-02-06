/*
 *	File:	lcd_2x16.h
 *	Date:	13.12.2013
 */

#ifndef LCD_2X16_H_
#define LCD_2X16_H_

#define LCD_PORT	GPIOB
#define LCD_PIN_RS	10
#define LCD_PIN_E	11
#define LCD_PIN_DB4	12
#define LCD_PIN_DB5	13
#define LCD_PIN_DB6	14
#define LCD_PIN_DB7	15
#define LCD_PINS	((1<<LCD_PIN_RS) | (1<<LCD_PIN_E) | (1<<LCD_PIN_DB4) | (1<<LCD_PIN_DB5) | (1<<LCD_PIN_DB6) | (1<<LCD_PIN_DB7))
#define LCD_PINS_CTRL	((1<<LCD_PIN_RS) | (1<<LCD_PIN_E))
#define LCD_PINS_DATA	((1<<LCD_PIN_DB4) | (1<<LCD_PIN_DB5) | (1<<LCD_PIN_DB6) | (1<<LCD_PIN_DB7))
#define LCD_PORT_MODE	PAL_MODE_OUTPUT_PUSHPULL
#define LCD_PIN_OFFSET	8

extern void lcd_2x16_init(void);
extern void lcd_2x16_set_position(uint8_t row, uint8_t colum);
extern void lcd_2x16_print_char(uint8_t data);
extern void lcd_2x16_print_string(uint8_t * string);
extern const uint8_t lcd_2x16_decode[];

#endif /* LCD_2X16_H_ */
