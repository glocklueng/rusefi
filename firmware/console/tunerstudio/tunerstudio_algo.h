/**
 * @file	tunerstudio_algo.h
 *
 * @date Oct 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef TUNERSTUDIO_ALGO_H_
#define TUNERSTUDIO_ALGO_H_

#define TS_SIGNATURE "MShift v0.01"

#include <stdint.h>

// http://en.wikipedia.org/wiki/Endianness

#define SWAP_UINT16(x) ((x) << 8) | ((x) >> 8)

#define SWAP_UINT32(x) (((x) >> 24) & 0xff) | (((x) << 8) & 0xff0000) | (((x) >> 8) & 0xff00) | (((x) << 24) & 0xff000000)

// response codes

#define TS_RESPONSE_OK 0x00

typedef struct {
	int queryCommandCounter;
	int outputChannelsCommandCounter;
	int readPageCommandsCounter;
	int burnCommandCounter;
	int pageCommandCounter;
	int writeValueCommandCounter;
	int writeChunkCommandCounter;
	int errorCounter;
	// this field is in the end to simply aligning situation
	short currentPageId;
} TunerStudioState;

int tunerStudioHandleCommand(char *data, int incomingPacketSize);

void handleTestCommand(void);
void handleQueryCommand(int needCrc);
void handleOutputChannelsCommand(void);

char *getWorkingPageAddr(int pageIndex);
int getTunerStudioPageSize(int pageIndex);
void handleWriteValueCommand(void);
void handleWriteChunkCommand(void);
void handlePageSelectCommand(short *pageId);
void handlePageReadCommand(short *pageId);
void handleBurnCommand(void);

void tunerStudioWriteData(const uint8_t * buffer, int size);
void tunerStudioDebug(char *msg);

#endif /* TUNERSTUDIO_ALGO_H_ */
