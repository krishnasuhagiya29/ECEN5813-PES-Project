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
 * @file    tsi.h
 * @brief	This file contains declaration of various functions developed for TSI operations.
 *
 *
 * @author  Krishna Suhagiya
 * @date    17th October 2023
 *
 */

#ifndef TSI_H_
#define TSI_H_

#include <stdint.h>

// Boolean indicating touch event
extern volatile bool touch_event;

/*!
 * @brief TSI0 handler
 *
 * @param[in]  None
 *
 * @return     None
 */
void TSI0_IRQHandler(void);

/*!
 * @brief Function to initialize TSI
 *
 * @param[in]  None
 *
 * @return     None
 */
void tsi_init(void);

#endif /* TSI_H_ */

