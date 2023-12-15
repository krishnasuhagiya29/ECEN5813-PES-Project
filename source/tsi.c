/*******************************************************************************
 * Copyright (C) 2023 by Krishna Suhagiya
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Krishna Suhagiya and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    tsi.c
 * @brief	This file contains definition of various functions developed for TSI operations.
 *
 *
 * @author  Krishna Suhagiya
 * @date    17th October 2023
 *
 */

#include <stdbool.h>

#include "MKL25Z4.h"
#include "tsi.h"

//variation of the capacitance >100
#define TOUCH_OFFSET 550  // offset value to be subtracted
#define TOUCH_DATA (TSI0->DATA & 0xFFFF)//macro for extracting the count from data register
#define ZERO (0uL)
#define NUM_OF_SCANS (31uL)
#define CHANNEL_NUM (10uL)
// TODO: Change the below values to align with your hardware
#define REF_SLIDER_VALUE  (100uL)	// Reference for slider value observed without touch event

volatile uint32_t touch_val = 0uL;	// calibrated touch value
volatile bool touch_event = false;		// touch event flag

void TSI0_IRQHandler(void) {
	touch_val = TOUCH_DATA - TOUCH_OFFSET;
	if (touch_val > REF_SLIDER_VALUE) {
		touch_event = true;
	} else {
		touch_event = false;
	}
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK; 	//writing one to clear the flag
}

void tsi_init(void) {
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; // Enabling the clock
	TSI0->GENCS = TSI_GENCS_MODE(ZERO) |
	TSI_GENCS_REFCHRG(ZERO) |
	TSI_GENCS_DVOLT(ZERO) |
	TSI_GENCS_EXTCHRG(ZERO) |
	TSI_GENCS_PS(ZERO) |
	TSI_GENCS_NSCN(NUM_OF_SCANS) |
	TSI_GENCS_TSIEN_MASK |
	TSI_GENCS_STPE_MASK |  // Enabling the TSI in low power modes
			TSI_GENCS_EOSF_MASK |
			TSI_GENCS_ESOR_MASK |//Enabling interrupt using end of scan
			TSI_GENCS_TSIIEN_MASK;//Enabling the TSI interrupt

	TSI0->DATA = TSI_DATA_TSICH(CHANNEL_NUM); // Selecting channel 10
	//enaling interrupt in NVIC
	NVIC_SetPriority(TSI0_IRQn, 3);
	NVIC_ClearPendingIRQ(TSI0_IRQn);
	NVIC_EnableIRQ(TSI0_IRQn);
	// Allow low leakage stop mode
	SMC->PMPROT = SMC_PMPROT_ALLS_MASK;
	// Enable low-leakage stop mode and regular run mode
	SMC->PMCTRL = SMC_PMCTRL_STOPM(3) | SMC_PMCTRL_RUNM(ZERO);
	SMC->STOPCTRL = SMC_STOPCTRL_PSTOPO(ZERO) | SMC_STOPCTRL_VLLSM(3);
	// Enable LLWU
	// allow TSI0 to wake LLWU
	LLWU->ME |= LLWU_ME_WUME4_MASK;
}
