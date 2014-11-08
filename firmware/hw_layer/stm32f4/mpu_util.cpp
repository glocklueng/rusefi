/**
 * @file	mpu_util.cpp
 *
 * @date Jul 27, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "mpu_util.h"
#include "error_handling.h"

extern "C" {
int getRemainingStack(Thread *otp);
void prvGetRegistersFromStack(uint32_t *pulFaultStackAddress);
}

extern stkalign_t __main_stack_base__;

#define GET_CFSR() (*((volatile uint32_t *) (0xE000ED28)))

#if defined __GNUC__
// GCC version

int getRemainingStack(Thread *otp) {

#if CH_DBG_ENABLE_STACK_CHECK
	register struct intctx *r13 asm ("r13");
	otp->activeStack = r13;

	int rs;
	if (dbg_isr_cnt > 0) {
		// ISR context
		rs = (stkalign_t *) (r13 - 1) - &__main_stack_base__;
	} else {

		rs = (stkalign_t *) (r13 - 1) - otp->p_stklimit;
	}
	otp->remainingStack = rs;
	return rs;
#else
	return 99999;
#endif /* CH_DBG_ENABLE_STACK_CHECK */
}

#else /* __GNUC__ */

extern uint32_t CSTACK$$Base; /* symbol created by the IAR linker */
extern uint32_t IRQSTACK$$Base; /* symbol created by the IAR linker */

int getRemainingStack(Thread *otp) {
#if CH_DBG_ENABLE_STACK_CHECK || defined(__DOXYGEN__)
	int remainingStack;
	if (dbg_isr_cnt > 0) {
		remainingStack = (__get_SP() - sizeof(struct intctx)) - (int)&IRQSTACK$$Base;
	} else {
		remainingStack = (stkalign_t *)(__get_SP() - sizeof(struct intctx)) - otp->p_stklimit;
	}
	otp->remainingStack = remainingStack;
	return remainingStack;
#else
	return 999999;
#endif  
}

// IAR version

#endif

void baseHardwareInit(void) {
	// looks like this holds a random value on start? Let's set a nice clean zero
	DWT_CYCCNT = 0;
}

void DebugMonitorVector(void) {

	chDbgPanic3("DebugMonitorVector", __FILE__, __LINE__);

	while (TRUE)
		;
}

void UsageFaultVector(void) {

	chDbgPanic3("UsageFaultVector", __FILE__, __LINE__);

	while (TRUE)
		;
}

void BusFaultVector(void) {

	chDbgPanic3("BusFaultVector", __FILE__, __LINE__);

	while (TRUE) {
	}
}

/**
 + * @brief   Register values for postmortem debugging.
 + */
volatile uint32_t postmortem_r0;
volatile uint32_t postmortem_r1;
volatile uint32_t postmortem_r2;
volatile uint32_t postmortem_r3;
volatile uint32_t postmortem_r12;
volatile uint32_t postmortem_lr; /* Link register. */
volatile uint32_t postmortem_pc; /* Program counter. */
volatile uint32_t postmortem_psr;/* Program status register. */
volatile uint32_t postmortem_CFSR;
volatile uint32_t postmortem_HFSR;
volatile uint32_t postmortem_DFSR;
volatile uint32_t postmortem_AFSR;
volatile uint32_t postmortem_BFAR;
volatile uint32_t postmortem_MMAR;
volatile uint32_t postmortem_SCB_SHCSR;

/**
 * @brief   Evaluates to TRUE if system runs under debugger control.
 * @note    This bit resets only by power reset.
 */
#define is_under_debugger() (((CoreDebug)->DHCSR) & \
                            CoreDebug_DHCSR_C_DEBUGEN_Msk)

/**
 *
 */
void prvGetRegistersFromStack(uint32_t *pulFaultStackAddress) {

	postmortem_r0 = pulFaultStackAddress[0];
	postmortem_r1 = pulFaultStackAddress[1];
	postmortem_r2 = pulFaultStackAddress[2];
	postmortem_r3 = pulFaultStackAddress[3];
	postmortem_r12 = pulFaultStackAddress[4];
	postmortem_lr = pulFaultStackAddress[5];
	postmortem_pc = pulFaultStackAddress[6];
	postmortem_psr = pulFaultStackAddress[7];

	/* Configurable Fault Status Register. Consists of MMSR, BFSR and UFSR */
	postmortem_CFSR = GET_CFSR();

	/* Hard Fault Status Register */
	postmortem_HFSR = (*((volatile uint32_t *) (0xE000ED2C)));

	/* Debug Fault Status Register */
	postmortem_DFSR = (*((volatile uint32_t *) (0xE000ED30)));

	/* Auxiliary Fault Status Register */
	postmortem_AFSR = (*((volatile uint32_t *) (0xE000ED3C)));

	/* Read the Fault Address Registers. These may not contain valid values.
	 Check BFARVALID/MMARVALID to see if they are valid values
	 MemManage Fault Address Register */
	postmortem_MMAR = (*((volatile uint32_t *) (0xE000ED34)));
	/* Bus Fault Address Register */
	postmortem_BFAR = (*((volatile uint32_t *) (0xE000ED38)));

	postmortem_SCB_SHCSR = SCB->SHCSR;

	if (is_under_debugger()) {
		__asm("BKPT #0\n");
		// Break into the debugger
	}

	/* harmless infinite loop */
	while (1) {
		;
	}
}

void HardFaultVector(void) {
#if 0 && defined __GNUC__
	__asm volatile (
			" tst lr, #4                                                \n"
			" ite eq                                                    \n"
			" mrseq r0, msp                                             \n"
			" mrsne r0, psp                                             \n"
			" ldr r1, [r0, #24]                                         \n"
			" ldr r2, handler2_address_const                            \n"
			" bx r2                                                     \n"
			" handler2_address_const: .word prvGetRegistersFromStack    \n"
	);

#else
#endif        

	int cfsr = GET_CFSR();
	if (cfsr & 0x1) {
		chDbgPanic3("H IACCVIOL", __FILE__, __LINE__);
        } else if (cfsr & 0x100) {
		chDbgPanic3("H IBUSERR", __FILE__, __LINE__);
	} else if (cfsr & 0x20000) {
		chDbgPanic3("H INVSTATE", __FILE__, __LINE__);
	} else {
		chDbgPanic3("HardFaultVector", __FILE__, __LINE__);
	}

	while (TRUE) {
	}
}

