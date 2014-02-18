/**
 * @file	trigger_decoder.h
 *
 * @date Dec 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef TRIGGER_DECODER_H_
#define TRIGGER_DECODER_H_

#include <time.h>
#include "trigger_structure.h"
#include "engine_configuration.h"

int isTriggerDecoderError(void);
void processTriggerEvent(trigger_state_s *shaftPositionState, trigger_shape_s *triggerShape, ShaftEvents signal, time_t now);
void initializeSkippedToothTriggerShapeExt(engine_configuration2_s *engineConfiguration2, int totalTeethCount, int skippedCount);
void initTriggerDecoder(void);

#endif /* TRIGGER_DECODER_H_ */
