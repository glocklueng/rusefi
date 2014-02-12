/*
 * @file ford_1995_inline_6.c
 *
 * http://rusefi.com/forum/viewtopic.php?f=3&t=469
 *
 * @date Feb 12, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "ford_1995_inline_6.h"
#include "toothed_wheel_emulator.h"

void setFordInline6(engine_configuration_s *engineConfiguration) {

}

void setFordInline6_2(engine_configuration2_s *engineConfiguration2) {
	skippedToothTriggerShapeExt(engineConfiguration2, 3, 0);
}
