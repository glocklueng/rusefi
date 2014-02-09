/*
 * @file lcd_2x16.h
 * @date 13.12.2013
 */

#ifndef LCD_2X16_H_
#define LCD_2X16_H_

extern void lcd_2x16_init(void);
extern void lcd_2x16_set_position(uint8_t row, uint8_t colum);
extern void lcd_2x16_print_char(uint8_t data);
extern void lcd_2x16_print_string(uint8_t * string);
extern const uint8_t lcd_2x16_decode[];

void lcdShowFatalMessage(char *message);
void lcdTest(void);

#endif /* LCD_2X16_H_ */
