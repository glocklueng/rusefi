/**
 * @file	tunerstudio.h
 *
 * @date Aug 26, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef TUNERSTUDIO_H_
#define TUNERSTUDIO_H_

#include "main.h"
#include "tunerstudio_io.h"

#if EFI_TUNER_STUDIO
#include "tunerstudio_configuration.h"
#include "engine.h"

#include <stdint.h>

typedef struct {
	int queryCommandCounter;
	int outputChannelsCommandCounter;
	int readPageCommandsCounter;
	int burnCommandCounter;
	int pageCommandCounter;
	int writeValueCommandCounter;
	int writeChunkCommandCounter;
	int errorCounter;
	int tsCounter;
} tunerstudio_counters_s;

bool handlePlainCommand(uint8_t command);
int tunerStudioHandleCrcCommand(uint8_t *data, int incomingPacketSize);

void handleTestCommand(void);
void handleQueryCommand(ts_response_format_e mode);
void handleOutputChannelsCommand(ts_response_format_e mode);

char *getWorkingPageAddr(int pageIndex);
int getTunerStudioPageSize(int pageIndex);
void handleWriteValueCommand(ts_response_format_e mode, uint16_t page, uint16_t offset, uint8_t value);
void handleWriteChunkCommand(ts_response_format_e mode, short offset, short count, void *content);
void handlePageSelectCommand(ts_response_format_e mode, uint16_t pageId);
void handlePageReadCommand(ts_response_format_e mode, uint16_t pageId, uint16_t offset, uint16_t count);
void handleBurnCommand(ts_response_format_e mode, uint16_t page);

void tunerStudioDebug(const char *msg);
void tunerStudioError(const char *msg);

void updateTunerStudioState(TunerStudioOutputChannels *tsOutputChannels DECLARE_ENGINE_PARAMETER_S);
void printTsStats(void);
void requestBurn(void);

void startTunerStudioConnectivity(Logging *sharedLogger);
void syncTunerStudioCopy(void);

#if defined __GNUC__
// GCC
#define pre_packed
#define post_packed __attribute__((packed))
#else
// IAR
#define pre_packed __packed
#define post_packed
#endif

typedef pre_packed struct
	post_packed {
		short int page;
		short int offset;
		short int count;
	} TunerStudioWriteChunkRequest;

	typedef pre_packed struct
		post_packed {
			short int page;
			short int offset;
			short int count;
		} TunerStudioReadRequest;

		typedef pre_packed struct
			post_packed {
				short int offset;
				unsigned char value;
			} TunerStudioWriteValueRequest;

#endif /* EFI_TUNER_STUDIO */

#endif /* TUNERSTUDIO_H_ */
