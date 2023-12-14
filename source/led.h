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
 * @file    led.h
 * @brief	This file contains declaration of various functions developed for various LED flashing sequences.
 *
 *
 * @author  Krishna Suhagiya
 * @date    1st October 2023
 *
 */

#ifndef LED_H_
#define LED_H_

#define RED_LED_SHIFT   (18uL)	// on port B
#define GREEN_LED_SHIFT (19uL)	// on port B
#define BLUE_LED_SHIFT  (1uL)		// on port D
#define MASK(x) (1UL << (x))

typedef enum {
    blue = 0,
    white,
    red,
	green,
	yellow
}led_color;

/*
 * This function initializes the LED setup.
 *
 * Parameters:
 *   None
 * Returns:
 *   None
 */
void init_led(void);

/*
 * This function turns the specified color LED on.
 *
 * Parameters:
 *   Enum value of LED color
 * Returns:
 *   None
 */
void turn_on_led(led_color color);

/*
 * This function turns the specified color LED off.
 *
 * Parameters:
 *   Enum value of LED color
 * Returns:
 *   None
 */
void turn_off_led(led_color color);

#endif /* LED_H_ */
