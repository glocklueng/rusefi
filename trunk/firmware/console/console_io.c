/**
 * @file	console_io.c
 *
 * @date Dec 29, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "console_io.h"
#include "ch.h"

#include "usbconsole.h"
#include "rfiutil.h"

/**
 * @brief   Reads a whole line from the input channel.
 *
 * @param[in] chp       pointer to a @p BaseChannel object
 * @param[in] line      pointer to the line buffer
 * @param[in] size      buffer maximum length
 * @return              The operation status.
 * @retval TRUE         the channel was reset or CTRL-D pressed.
 * @retval FALSE        operation successful.
 */
static bool_t getConsoleLine(BaseChannel *chp, char *line, unsigned size) {
	char *p = line;

	while (TRUE) {
		if (!is_serial_ready()) {
			// we better do not read from USB serial before it is ready
			chThdSleepMilliseconds(10);
			continue;
		}

		short c = (short) chSequentialStreamGet(chp);
		if (c < 0)
			return TRUE;
		if (c == 4) {
			return TRUE;
		}
		if (c == 8) {
			if (p != line) {
				// backspace
				consolePutChar((uint8_t) c);
				consolePutChar(0x20);
				consolePutChar((uint8_t) c);
				p--;
			}
			continue;
		}
		if (c == '\r') {
			consolePutChar('\r');
			consolePutChar('\n');
			*p = 0;
			return FALSE;
		}
		if (c < 0x20)
			continue;
		if (p < line + size - 1) {
			consolePutChar((uint8_t) c);
			*p++ = (char) c;
		}
	}
}

// todo: this is ugly as hell!
static char consoleInput[] = "                                                                              ";

void (*console_line_callback)(char *);

static WORKING_AREA(consoleThreadStack, UTILITY_THREAD_STACK_SIZE);
static msg_t consoleThreadThreadEntryPoint(void *arg) {
	(void) arg;
	chRegSetThreadName("console thread");

	while (TRUE) {
		bool_t end = getConsoleLine((BaseChannel *) CONSOLE_CHANNEL, consoleInput, sizeof(consoleInput));
		if (end)
			break;

		(console_line_callback)(consoleInput);
	}
	return FALSE;
}

#ifdef EFI_SERIAL_OVER_USB
#else
static SerialConfig serialConfig = { SERIAL_SPEED, 0, USART_CR2_STOP1_BITS | USART_CR2_LINEN, 0 };
#endif

#ifndef EFI_SERIAL_OVER_USB
int is_serial_ready(void) {
	return TRUE;
}
#endif

void startChibiosConsole(void (*console_line_callback_p)(char *)) {
	console_line_callback = console_line_callback_p;
#ifdef EFI_SERIAL_OVER_USB
	usb_serial_start();

#else
	/*
	 * Activates the serial using the driver default configuration (that's 38400)
	 * it is important to set 'NONE' as flow control! in terminal application on the PC
	 */
	sdStart(CONSOLE_CHANNEL, &serialConfig);

	// cannot use pin repository here because pin repository prints to console
	palSetPadMode(EFI_CONSOLE_PORT, EFI_CONSOLE_RX_PIN, PAL_MODE_ALTERNATE(EFI_CONSOLE_AF));
	palSetPadMode(EFI_CONSOLE_PORT, EFI_CONSOLE_TX_PIN, PAL_MODE_ALTERNATE(EFI_CONSOLE_AF));
#endif
	chThdCreateStatic(consoleThreadStack, sizeof(consoleThreadStack), NORMALPRIO, consoleThreadThreadEntryPoint, NULL);
}

extern cnt_t dbg_isr_cnt;

void lockAnyContext(void) {
	if (isIsrContext()) {
		chSysLockFromIsr()
		;
	} else {
		chSysLock()
		;
	}
}

void lockOutputBuffer(void) {
	lockAnyContext();
}

void unlockAnyContext(void) {
	if (isIsrContext()) {
		chSysUnlockFromIsr()
		;
	} else {
		chSysUnlock()
		;
	}
}

void unlockOutputBuffer(void) {
	unlockAnyContext();
}
