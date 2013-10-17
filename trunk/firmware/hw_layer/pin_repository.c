/*
 * pin_repository.c
 *
 *  Created on: Jan 15, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    pin_repository.c
 * @brief   I/O pin registry code
 *
 * This job of this class is to make sure that we are not using same hardware pin for two
 * different purposes.
 */

#include "ch.h"
#include "hal.h"
#include "pin_repository.h"
#include "rficonsole.h"
#include "datalogging.h"

#define PIN_REPO_SIZE 7 * 16
int PIN_USED[PIN_REPO_SIZE];
static int initialized = FALSE;

static Logging log;
static int pinRegistrationComplete = FALSE;
static int totalPinsUsed = 0;

char *portname(GPIO_TypeDef* GPIOx) {
	if (GPIOx == GPIOA )
		return "PA";
	if (GPIOx == GPIOB )
		return "PB";
	if (GPIOx == GPIOC )
		return "PC";
	if (GPIOx == GPIOD )
		return "PD";
	if (GPIOx == GPIOE )
		return "PE";
	if (GPIOx == GPIOF )
		return "PF";
	if (GPIOx == GPIOH )
		return "PH";
	return "unknown";
}

static int getPortIndex(GPIO_TypeDef* port) {
	if (port == GPIOA )
		return 0;
	if (port == GPIOB )
		return 1;
	if (port == GPIOC )
		return 2;
	if (port == GPIOD )
		return 3;
	if (port == GPIOE )
		return 4;
	if (port == GPIOF )
		return 5;
	if (port == GPIOH )
		return 6;
	fatal("portindex");
}

static void reportPins(void) {
	pinRegistrationComplete = TRUE;
	print("Total pins count: %d\r\n", totalPinsUsed);
}

void initPinRepository(void) {
	initLogging(&log, "pin repos", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));

	for (int i = 0; i < PIN_REPO_SIZE; i++)
		PIN_USED[i] = 0;
	initialized = TRUE;
	print("Initializing pin repository\r\n");
	addConsoleAction("pins", reportPins);
}

void printpin(char *msg, ioportid_t port, int pin) {
	if (!initialized)
		fatal("repo not initialized");
	int portIndex = getPortIndex(port);
	int index = portIndex * 16 + pin;
	print("%s on %s:%d\r\n", msg, portname(port), pin);

	append(&log, "msg,");
	append(&log, msg);
	append(&log, " on ");
	msgInt(&log, portname(port), pin);
	printLine(&log);

	if (PIN_USED[index]) {
		print("!!!!!!!!!!!!! Already used [%s] %d\r\n", msg, pin);
		fatal("pin already used");
		//fatal(msg);
	}
	PIN_USED[index] = TRUE;
	totalPinsUsed++;
}

void mySetPadMode(char *msg, ioportid_t port, ioportmask_t pin, iomode_t mode) {
	printpin(msg, port, pin);
	palSetPadMode(port, pin, mode);
}
