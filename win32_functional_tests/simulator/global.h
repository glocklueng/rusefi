
#include <ch.h>
#include <hal.h>
#include <time.h>
#include <math.h>

#include "boards.h"
#include "eficonsole.h"
#include "efilib.h"
#include "datalogging.h"
#include "error_handling.h"


#ifndef GLOBAL_FT_H_
#define GLOBAL_FT_H_

#define EFI_SIMULATOR TRUE

#define EFI_SUPPORT_DODGE_NEON TRUE
#define EFI_SUPPORT_FORD_ASPIRE TRUE
#define EFI_SUPPORT_FORD_FIESTA TRUE
#define EFI_SUPPORT_NISSAN_PRIMERA TRUE
#define EFI_SUPPORT_1995_FORD_INLINE_6 TRUE

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

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

void printToWin32Console(char *p);
int systicks2ms(int systicks);

// todo: move somewhere else?
void lockAnyContext(void);
void unlockAnyContext(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */


/**
 * number of SysClock ticks in one ms
 */
#define TICKS_IN_MS  (CH_FREQUENCY / 1000)

#define hal_lld_get_counter_value() 0
