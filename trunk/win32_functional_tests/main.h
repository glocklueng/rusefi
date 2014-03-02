
#include "global.h"
#include "boards.h"

#include "datalogging.h"

void fatal(x);
void printToWin32Console(int *p);

/**
 * number of SysClock ticks in one ms
 */
#define TICKS_IN_MS  (CH_FREQUENCY / 1000)

#define hal_lld_get_counter_value() 0
