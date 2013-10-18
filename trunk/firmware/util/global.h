/*
 * global.h
 *
 *  Created on: May 27, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <ch.h>
#include <hal.h>

/**
 * To be honest, I have already forgotten why I use my own type name for float values. Probably two reasons:
 *  1) I can search all float usages in my code
 *  2) I am hoping that eventually some MCU would have an FPU to handle double-precision values
 */
typedef float myfloat;

/* definition to expand macro then apply to pragma message */
#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define VAR_NAME_VALUE(var) #var "="  VALUE(var)

#endif /* GLOBAL_H_ */
