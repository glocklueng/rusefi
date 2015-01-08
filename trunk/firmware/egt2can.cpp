
#include "main.h"
#include "engine_configuration.h"
#include "max31855.h"

egt_cs_array_t max31855_cs;

int main_loop_started;

int maxNesting = 0;

void firmwareError(const char *fmt, ...) {

}

/*
 * Blue LED blinker thread, times are in milliseconds.
 */
static WORKING_AREA(waThread1, 128);
static msg_t Thread1(void *arg) {

  (void)arg;
  chRegSetThreadName("blinker1");
  while (TRUE) {
    palClearPad(GPIOC, 13);
    chThdSleepMilliseconds(500);
    palSetPad(GPIOC, 13);
    chThdSleepMilliseconds(500);
  }
  return 0;
}


void initSpiCs(SPIConfig *spiConfig, brain_pin_e csPin) {
	spiConfig->end_cb = NULL;
//	ioportid_t port = getHwPort(csPin);
//	ioportmask_t pin = getHwPin(csPin);
//	spiConfig->ssport = port;
//	spiConfig->sspad = pin;
//	mySetPadMode("chip select", port, pin, PAL_STM32_MODE_OUTPUT);
}



void runRusEfi(void) {

#if EFI_USE_UART_FOR_CONSOLE
  /*
   * Activates the serial driver 1 using the driver default configuration.
   * PA9 and PA10 are routed to USART1.
   */
  sdStart(&SD1, NULL);
  palSetPadMode(GPIOA, 9, PAL_MODE_ALTERNATE(1));       /* USART1 TX.       */
  palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(1));      /* USART1 RX.       */
#endif

  /*
   * Creates the blinker threads.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  initMax31855(NULL, max31855_cs);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state, when the button is
   * pressed the test procedure is launched with output on the serial
   * driver 1.
   */
  while (true) {
//    if (palReadPad(GPIOA, GPIOA_BUTTON))
//      TestThread(&SD1);
    chThdSleepMilliseconds(50);

    printPending();
  }


}
