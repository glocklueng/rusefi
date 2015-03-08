/**
 * @file	tunerstudio_io.h
 *
 * @date Mar 8, 2015
 * @author Andrey Belomutskiy, (c) 2012-2014
 */
#ifndef CONSOLE_TUNERSTUDIO_TUNERSTUDIO_IO_H_
#define CONSOLE_TUNERSTUDIO_TUNERSTUDIO_IO_H_

#define TS_SIGNATURE "MShift v0.01"

#define TS_RESPONSE_OK 0x00
#define TS_RESPONSE_BURN_OK 0x04
#define TS_RESPONSE_CRC_FAILURE 0x82

typedef enum {
	TS_PLAIN = 0,
	TS_CRC = 1
} ts_response_format_e;



#endif /* CONSOLE_TUNERSTUDIO_TUNERSTUDIO_IO_H_ */
