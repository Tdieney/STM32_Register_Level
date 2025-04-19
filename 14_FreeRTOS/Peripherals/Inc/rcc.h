/*
 * rcc.h
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "main.h"

/**
 * @brief HSE configuration
 */
//void rcc_HSE_config();

/**
 * @brief Systick configuration
 */
void rcc_SysTick_config();

/**
 * @brief Increment milliseconds
 */
void rcc_msIncTick();

/**
 * @brief Get milliseconds
 */
uint32_t rcc_msGetTick();

/**
 * @brief Milliseconds delay function
 */
void rcc_msDelay(uint32_t milliseconds);

#endif /* INC_RCC_H_ */
