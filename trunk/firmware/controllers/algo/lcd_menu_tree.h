/**
 * @file	lcd_menu_tree.h
 *
 * @date Jan 6, 2015
 * @author Andrey Belomutskiy, (c) 2012-2014
 */
#ifndef CONTROLLERS_ALGO_LCD_MENU_TREE_H_
#define CONTROLLERS_ALGO_LCD_MENU_TREE_H_

typedef enum {
	LL_STRING,
	LL_VERSION,
	LL_CONFIG,
	LL_ALGORITHM,

	LL_RPM,
	LL_TRIGGER_ERRORS,
	LL_TRIGGER_DUTY,

	LL_CLT_TEMPERATURE,
	LL_IAT_TEMPERATURE,
	LL_TPS,
	LL_VBATT,
	LL_MAF,
	LL_MAP,
	LL_EGO,
	LL_BARO,

	LL_BASE_FUEL,
	LL_TOTAL_FUEL,
	LL_CLT_FUEL_CORR,
	LL_IAT_FUEL_CORR,
} lcd_line_e;

typedef void (*VoidCallback)(void);

class MenuItem {
public:
	MenuItem(MenuItem * parent, const char *text, VoidCallback callback);
	MenuItem(MenuItem * parent, const char *text);
	MenuItem(MenuItem * parent, lcd_line_e lcdLine);
	const char *text;
	lcd_line_e lcdLine;
	int index;
	// that's upper level menu item
	MenuItem *parent;
	MenuItem *topOfTheList;
	MenuItem *firstChild;
	MenuItem *lastChild;
	MenuItem *next;
	VoidCallback callback;
private:
	void init(MenuItem * parent, VoidCallback callback);
};

class MenuTree {
public:
	MenuTree(MenuItem *root);
	void nextItem(void);
	void back(void);
	void enterSubMenu(void);
	void init(MenuItem *first, int linesCount);
	MenuItem *root;

	int linesCount;
	MenuItem *current;
	MenuItem *topVisible;
};



#endif /* CONTROLLERS_ALGO_LCD_MENU_TREE_H_ */
