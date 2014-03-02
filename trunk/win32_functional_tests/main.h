
#include "global.h"
#include "boards.h"

#include "datalogging.h"

// typedef int bool_t;

void fatal(x);
//void chDbgAssert(int c, char *msg, void *arg);

/**
 * number of SysClock ticks in one ms
 */
#define TICKS_IN_MS  (CH_FREQUENCY / 1000)

#define hal_lld_get_counter_value() 0
