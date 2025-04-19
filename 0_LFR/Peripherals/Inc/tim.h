/*
 * tim.h
 *
 *  Created on: Aug 25, 2021
 *      Author: THINH
 */

#ifndef INC_TIM_H_
#define INC_TIM_H_

#include "main.h"

/**
 * @brief TIM3 - Time Base ticks/delay
 */
void tim_TIM3_initTicks(void);

/**
 * @brief Increment milliseconds
 */
void tim_msIncTick();

/**
 * @brief Get milliseconds
 */
uint32_t tim_msGetTick();

/**
 * @brief Milliseconds delay function
 */
void tim_msDelay(uint32_t milliseconds);

/**
 * @brief TIM2 & TIM4 PWM configuration
 */
void tim_PWM_config();

/**
 * @brief TIM Configuration
 */
void tim_config();

#endif /* INC_TIM_H_ */
