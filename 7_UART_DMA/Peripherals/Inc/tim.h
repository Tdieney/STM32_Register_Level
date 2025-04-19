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
 * @brief TIM3 trigger output event configuration
 */
void tim_TIM3_config();

/**
 * @brief TIM2 milliseconds delay configuration
 */
void tim_TIM2_delayConfig();
void tim_TIM2_myDelayConfig();

/**
 * @brief TIM2 milliseconds delay function
 */
void tim_TIM2_msDelay(uint32_t milliseconds);
void delay_us(uint32_t microSeconds);
void delay_ms(uint32_t milliSeconds);

/**
 * @brief Periodic TIM2 interrupt configuration
 */
void tim_TIM2_periodicINTConfig();

/**
 * @brief TIM1_CH1N output compare (OC) configuration
 */
void tim_TIM1_CH1N_OC_config();

/**
 * @brief TIM3 PWM configuration
 */
void tim_TIM3_PWM_RGB_config();

/**
 * @brief Set PWM duty cycles for RGB (0 - 255)
 */
void tim_TIM3_PWM_setRGB(uint8_t R, uint8_t G, uint8_t B);

/**
 * @brief Encoder TIM4 Peripherals configuration
 */
void tim_TIM4_Encoder_config();

#endif /* INC_TIM_H_ */
