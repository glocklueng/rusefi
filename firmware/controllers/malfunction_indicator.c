/*
 * @file malfunction_indicator.c
 * @brief We can blink out OBD-II error codes using Malfunction Indicator Light (MIL)
 *
 *
 * @date Dec 20, 2013
 * @author Konstantin Nikonenko
 * @author Andrey Belomutskiy, (c) 2012-2013
 * we show 4 digit error code - 1,5sec * (4xxx+1) digit + 0,4sec * (x3xxx+1) + ....
 * ATTENTION!!! 0 = 1 blink, 1 = 2 blinks, ...., 9 = 10 blinks
 * sequence is the constant!!!
 */

#include "main.h"
#include "output_pins.h"
#include "malfunction_indicator.h"

#define MFI_LONG_BLINK	1500
#define MFI_SHORT_BLINK	400
#define MFI_BLINK_SEPARATOR 400
#define MFI_CHECKENGINE_LIGHT 10000

int iMFIerror = 32;			// in future this error code will be check from main status engine structure

static WORKING_AREA(mfiThreadStack, UTILITY_THREAD_STACK_SIZE);	// declare thread

static void blink_digits(int digit, int duration) {
	for (int iter = 0; iter < digit; iter++) {
		turnOutputPinOn(LED_CHECK_ENGINE);
		chThdSleepMilliseconds(duration);
		turnOutputPinOff(LED_CHECK_ENGINE);
		chThdSleepMilliseconds(MFI_BLINK_SEPARATOR);
	}
}

// calculate how many digits our code have
static int DigitLength(int digit) {
	int i = 0;
	while (digit > 0) {
		digit = digit / 10;
		++i;
	}
	return i;
}

// display code
static void DisplayErrorCode(int length, int code) {
	for (int iter = length - 1; iter >= 0; iter--) {
		int ourDigit = pow(10, iter);		// 10^0 = 1, 10^1 = 10, 10^2=100, 10^3 = 1000, ....
		int digit = 1;						// as we remember "0" we show as one blink
		while (code >= ourDigit) {
			code = code - ourDigit;
			digit++;
		}
		if (iter % 2 == 0)
			blink_digits(digit, MFI_SHORT_BLINK);		// even 2,0 - long blink
		else
			blink_digits(digit, MFI_LONG_BLINK); 		// odd  3,1 - short blink
	}
}

//  our main thread for show check engine error
static msg_t mfiThread(void) {
	chRegSetThreadName("MFIndicator");

	while (TRUE) {
		// todo: extract this as 'blinkOneCode' method
		if (iMFIerror > 0) {
			// switch on check engine light on 10sec (one long blink)
			// todo: this needs to be a SLEEP, this has nothing to do with digits!
			// todo: if the problem is with LED invertion, it should be solved properly
			// todo: using 'blink_digits' to sleep is a hack :( we do not like hacks
			blink_digits(1, MFI_CHECKENGINE_LIGHT);
			// First at all calculate how many digits in this integer
			// and display error code
			DisplayErrorCode(DigitLength(iMFIerror), iMFIerror);
		}
	}
	return 0;
}

void initMalfunctionIndicator(void) {
	// create static thread
	chThdCreateStatic(mfiThreadStack, sizeof(mfiThreadStack), LOWPRIO, (tfunc_t) mfiThread, NULL );
}

