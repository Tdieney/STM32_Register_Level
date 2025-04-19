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
 * @brief HSI configuration
 */
void RCC_HSI_PLL_config();

/**
 * @brief Systick configuration
 */
void RCC_SysTick_config();

/**
 * @brief Increment milliseconds
 */
void RCC_msIncTick();

/**
 * @brief Get SysTick milliseconds
 */
uint32_t RCC_msGetTick();

/**
 * @brief Milliseconds delay by SysTick
 */
void delay_ms(uint32_t milliseconds);

#endif /* INC_RCC_H_ */
