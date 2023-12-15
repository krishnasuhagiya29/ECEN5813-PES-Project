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
 * @file    timer.c
 * @brief	This file contains definition of various functions developed for timer operations.
 *
 *
 * @author  Krishna Suhagiya
 * @date    17th October 2023
 *
 */

#include "MKL25Z4.h"
#include "timer.h"

volatile uint32_t msticks;	// Variable to count milliseconds
volatile uint32_t pollticks = 0; // Variable to count every 100ms

void systick_init(void) {
	// Load the timer for 1ms or 1000Hz timer
	SysTick->LOAD = (48000000 / 16) / 1000;
	NVIC_SetPriority(SysTick_IRQn, 2);
	// Load systock value
	SysTick->VAL = 0;
	// Use 3MHz clock
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void) {
	msticks++;

	pollticks += 1;
	if (pollticks == 100) {
		if (!(TSI0->GENCS & TSI_GENCS_SCNIP_MASK)) {
			// Software interrupt
			TSI0->DATA |= TSI_DATA_SWTS_MASK;
		}
		pollticks = 0;
	}
}

uint32_t getCurrentTime() {
	return msticks;
}

void delay(uint32_t time_ms) {
	uint32_t startticks = msticks;
	while ((msticks - startticks) < time_ms) {
		// Wait
	}
}
