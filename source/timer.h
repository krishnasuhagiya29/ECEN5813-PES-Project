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
 * @file    timer.h
 * @brief	This file contains declaration of various functions developed for LED related operations.
 *
 *
 * @author  Krishna Suhagiya
 * @date    17th October 2023
 *
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

extern volatile uint32_t msticks;

/*!
 * @brief Function to initialize systick timer
 *
 * @param[in]  None
 *
 * @return     None
 */
void systick_init(void);

/*!
 * @brief Function to for handling systick interrupts
 *
 * @param[in]  None
 *
 * @return     None
 */
void SysTick_Handler(void);

/*!
 * @brief Function to get the current time in milliseconds
 *
 * @param[in]  None
 *
 * @return     Number of milliseconds elapsed since beginning
 */
uint32_t getCurrentTime(void);

/*!
 * @brief Function to delay for a the milliseconds value passed
 *
 * @param[in]  period        The milliseconds delay value to achieve
 *
 * @return     None
 */
void delay(uint32_t time_ms);

#endif /* TIMER_H_ */
