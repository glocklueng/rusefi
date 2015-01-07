/**
 * @file	lcd_menu_tree.cpp
 *
 * @date Jan 6, 2015
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "stddef.h"
#include "lcd_menu_tree.h"
#include "error_handling.h"

static MenuItem ROOT(NULL, NULL);

static MenuTree tree(&ROOT);

static MenuItem miSensors(tree.root, "sensors");
static MenuItem miTrigger(tree.root, "trigger");
static MenuItem miBench(tree.root, "bench test");
static MenuItem miAbout(tree.root, "about");

MenuTree::MenuTree(MenuItem *root) {
	this->root = root;
	current = NULL;
}

void MenuTree::init(MenuItem *first, int linesCount) {
	this->linesCount = linesCount;
	current = first;
	topVisible = first;
}

void MenuTree::nextItem(void) {
	if (current->next == NULL) {
		// todo: go to first element
		return;
	}
	current = current->next;
	if (current->index - topVisible->index == linesCount)
		topVisible = topVisible->next;
}

MenuItem::MenuItem(MenuItem * parent, const char *text) {
	this->parent = parent;
	this->text = text;
	lcdLine = LL_STRING;

	// root element has NULL parent
	if (parent != NULL) {
		if (parent->firstChild == NULL) {
			parent->firstChild = this;
			index = 0;
		}
		if (parent->lastChild != NULL) {
			index = parent->lastChild->index + 1;
			parent->lastChild->next = this;
		}
		parent->lastChild = this;
	} else {
		firstChild = NULL;
		lastChild = NULL;
	}
}
