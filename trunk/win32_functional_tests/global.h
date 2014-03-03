
#include <ch.h>
#include <hal.h>
#include <time.h>
#include <math.h>

#ifndef GLOBAL_FT_H_
#define GLOBAL_FT_H_


#define EFI_SUPPORT_FORD_ASPIRE TRUE
#define EFI_SIGNAL_EXECUTOR_SLEEP TRUE

#define EFI_WAVE_CHART TRUE

#include "eficonsole_logic.h"
#include "rusefi_enums.h"

#define EFI_CUSTOM_PANIC_METHOD 1

// project-wide default thread stack size
#define UTILITY_THREAD_STACK_SIZE 1384

/**
 * @brief   @p Win32TestStream virtual methods table.
 */
struct Win32TestStreamVMT {
  _base_sequential_stream_methods
};

typedef struct {
  const struct Win32TestStreamVMT *vmt;
} TestStream;

extern TestStream testStream;

//##define TRUE 1
//#define FALSE 0
#endif /* GLOBAL_FT_H_ */
