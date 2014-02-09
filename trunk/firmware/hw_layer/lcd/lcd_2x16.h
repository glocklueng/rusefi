/*
 * @file lcd_2x16.h
 * @date 13.12.2013
 */

#ifndef LCD_2X16_H_
#define LCD_2X16_H_

#define HD44780_PORT_RS	GPIOE
#define HD44780_PIN_RS	8

#define HD44780_PORT_E	GPIOE
#define HD44780_PIN_E	10

#define HD44780_PORT_DB4	GPIOE
#define HD44780_PIN_DB4	11

#define LCD_PORT_DB5	GPIOB
#define LCD_PIN_DB5	13

#define LCD_PORT_DB6	GPIOB
#define LCD_PIN_DB6	14

#define LCD_PORT_DB7	GPIOB
#define LCD_PIN_DB7	15

extern void lcd_2x16_init(void);
extern void lcd_2x16_set_position(uint8_t row, uint8_t colum);
extern void lcd_2x16_print_char(uint8_t data);
extern void lcd_2x16_print_string(uint8_t * string);
extern const uint8_t lcd_2x16_decode[];

void lcdShowFatalMessage(char *message);
void lcdTest(void);

#endif /* LCD_2X16_H_ */
