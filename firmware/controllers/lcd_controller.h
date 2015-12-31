/**
 * @file lcd_controller.h
 *
 * @date Aug 14, 2014
 * @author Andrey Belomutskiy, (c) 2012-2016
 */

#ifndef LCD_CONTROLLER_H_
#define LCD_CONTROLLER_H_

#include "engine.h"

#define MAX_LCD_WIDTH 20

#define TOTAL_OPTIONS 6

void initLcdController(void);
void updateHD44780lcd(Engine *engine);

#endif /* LCD_CONTROLLER_H_ */
