
#include <ch.h>
#include <hal.h>
#include <time.h>
#include <math.h>

#define EFI_SUPPORT_FORD_ASPIRE TRUE
#define EFI_SIGNAL_EXECUTOR_SLEEP TRUE

#include "eficonsole_logic.h"
#include "rusefi_enums.h"

#define EFI_CUSTOM_PANIC_METHOD 1

// project-wide default thread stack size
#define UTILITY_THREAD_STACK_SIZE 1384


//##define TRUE 1
//#define FALSE 0
