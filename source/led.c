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
 * @file    led.c
 * @brief	This file contains definition of various functions developed for various LED flashing sequences.
 *
 *
 * @author  Krishna Suhagiya
 * @date    1st October 2023
 *
 */

#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "led.h"

void led_init(void) {
	// Enable clock to Port B and Port D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	// Make 3 pins GPIO
	PORTB->PCR[RED_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_SHIFT] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_SHIFT] |= PORT_PCR_MUX(1);
	PORTD->PCR[BLUE_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_SHIFT] |= PORT_PCR_MUX(1);

	// Init GPIO registers
	PTB->PDDR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
	PTD->PDDR |= MASK(BLUE_LED_SHIFT);

	PTB->PDOR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
	PTD->PDOR |= MASK(BLUE_LED_SHIFT);
}

// Since LED anode is connected to the MCU, clearing output bit to zero will light the LED and
// setting the output bit to one will turn off the LED.
void led_turn_on(led_color color)
{
	switch(color) {
		case blue:
			PTD->PCOR |= MASK(BLUE_LED_SHIFT);
			break;

		case white:
			PTB->PCOR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
			PTD->PCOR |= MASK(BLUE_LED_SHIFT);
			break;

		case red:
			PTB->PCOR |= MASK(RED_LED_SHIFT);
			break;

		case green:
			PTB->PCOR |= MASK(GREEN_LED_SHIFT);
			break;

		case yellow:
			PTB->PCOR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
			break;

		default:
			PRINTF("Invalid color option.\r\n");
	}
}

void led_turn_off(led_color color)
{
	switch(color) {
		case blue:
			PTD->PSOR |= MASK(BLUE_LED_SHIFT);
			break;

		case white:
			PTB->PSOR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
			PTD->PSOR |= MASK(BLUE_LED_SHIFT);
			break;

		case red:
			PTB->PSOR |= MASK(RED_LED_SHIFT);
			break;

		case green:
			PTB->PSOR |= MASK(GREEN_LED_SHIFT);
			break;

		case yellow:
			PTB->PSOR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
			break;

		default:
			PRINTF("Invalid color option.\r\n");
	}
}
