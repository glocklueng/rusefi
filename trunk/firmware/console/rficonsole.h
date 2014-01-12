/**
 * @file    rficonsole.h
 * @brief   Console package entry point header
 *
 * @date Nov 15, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#pragma once
#ifndef RFICONSOLE_H_
#define RFICONSOLE_H_

#include "rfiutil.h"
#include "rficonsole_logic.h"

void initializeConsole(void);
void sendOutConfirmation(char *value, int i);

#endif /* RFICONSOLE_H_ */
