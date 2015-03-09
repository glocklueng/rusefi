/**
 * @file	loggingcentral.cpp
 *
 * @date Mar 8, 2015
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "main.h"
#include "efilib.h"

#if ! EFI_UNIT_TEST || defined(__DOXYGEN__)

typedef char log_buf_t[DL_OUTPUT_BUFFER];

/**
 * we need to leave a byte for zero terminator, also two bytes for the \r\n in
 * printWithLength, also couple of bytes just in case
 */
#define MAX_DL_CAPACITY (DL_OUTPUT_BUFFER - 5)

/**
 * This is the buffer into which all the data providers write
 */
static char *accumulationBuffer;

static log_buf_t pendingBuffers0 CCM_OPTIONAL;
static log_buf_t pendingBuffers1;

/**
 * amount of data accumulated so far
 */
static uint32_t accumulatedSize;

/**
 * We copy all the pending data into this buffer once we are ready to push it out
 */
static char * outputBuffer;

/**
 * This method appends the content of this thread-local logger into the global buffer
 * of logging content
 */
void scheduleLogging(Logging *logging) {
	// this could be done without locking
	int newLength = efiStrlen(logging->buffer);

	bool alreadyLocked = lockOutputBuffer();
	if (accumulatedSize + newLength >= MAX_DL_CAPACITY) {
		/**
		 * if no one is consuming the data we have to drop it
		 * this happens in case of serial-over-USB, todo: find a better solution?
		 */
		if (!alreadyLocked) {
			unlockOutputBuffer();
		}
		resetLogging(logging);
		return;
	}
	// memcpy is faster then strcpy because it is not looking for line terminator
	memcpy(accumulationBuffer + accumulatedSize, logging->buffer, newLength + 1);
	accumulatedSize += newLength;
	if (!alreadyLocked) {
		unlockOutputBuffer();
	}
	resetLogging(logging);
}

/**
 * this method should always be invoked from the same thread!
 */
char * swapOutputBuffers(int *actualOutputBufferSize) {
	int expectedOutputSize;
	{ // start of critical section
		lockOutputBuffer();
		/**
		 * we cannot output under syslock, we simply rotate which buffer is which
		 */
		char *temp = outputBuffer;

		expectedOutputSize = accumulatedSize;
		outputBuffer = accumulationBuffer;

		accumulationBuffer = temp;
		accumulatedSize = 0;
		accumulationBuffer[0] = 0;

		unlockOutputBuffer();
	} // end of critical section

	*actualOutputBufferSize = efiStrlen(outputBuffer);
	efiAssert(*actualOutputBufferSize == expectedOutputSize, "out constr", NULL);
	return outputBuffer;
}

extern bool_t consoleInBinaryMode;

/**
 * This method actually sends all the pending data to the communication layer.
 * This method is invoked by the main thread - that's the only thread which should be sending
 * actual data to console in order to avoid concurrent access to serial hardware.
 */
void printPending(void) {
	if (consoleInBinaryMode)
		return;
	int actualOutputBufferSize;
	char *output = swapOutputBuffers(&actualOutputBufferSize);

	if (actualOutputBufferSize > 0) {
		printWithLength(output);
	}
}

void initLoggingCentral(void) {
	pendingBuffers0[0] = 0;
	pendingBuffers1[0] = 0;
	accumulationBuffer = pendingBuffers0;
	outputBuffer = pendingBuffers1;
	accumulatedSize = 0;
}

#endif /* EFI_UNIT_TEST */
