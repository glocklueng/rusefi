
#include "global.h"
#include "boards.h"
#include "eficonsole.h"

#include "datalogging.h"
#include "error_handling.h"

void printToWin32Console(int *p);
int systicks2ms(int systicks);

// todo: move somewhere else?
void lockAnyContext(void);
void unlockAnyContext(void);

/**
 * number of SysClock ticks in one ms
 */
#define TICKS_IN_MS  (CH_FREQUENCY / 1000)

#define hal_lld_get_counter_value() 0
