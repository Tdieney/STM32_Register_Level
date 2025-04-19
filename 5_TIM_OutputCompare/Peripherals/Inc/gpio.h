/*
 * gpio.h
 *
 *  Created on: Aug 22, 2021
 *      Author: THINH
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"

// Bit - banding
#define BIT_BAND(ADDR, BIT_NUMB)      *(uint32_t *)((ADDR & 0xF0000000UL) + 0x02000000 + \
                                                    (ADDR - (ADDR & 0xF0000000UL)) * 32 + BIT_NUMB * 4)
#define LED_PC13                      BIT_BAND((uint32_t)&(GPIOC->ODR), 13)
#define BTN_PA0                       BIT_BAND((uint32_t)&(GPIOA->IDR), 0)
#define SW1_PA8                       BIT_BAND((uint32_t)&(GPIOA->IDR), 8)
#define SW2_PA15                      BIT_BAND((uint32_t)&(GPIOA->IDR), 15)

/**
 * @brief LED GPIO configuration (PC13)
 */
void gpio_LED_config();

/**
 * @brief Write/Toggle LED functions
 */
void gpio_LED_write(bool state);
void gpio_LED_toggle();

/**
 * @brief Button configuration (PA0)
 */
void gpio_PB_config();

/**
 * @brief Read push-button function
 */
bool gpio_PB_read();

/**
 * @brief Slide switchs configuration (PA8, PA15)
 */
void gpio_SW_config();

/**
 * @brief Read Slide switchs function (PA8, PA15)
 */
bool gpio_SW1_read();
bool gpio_SW2_read();

/**
 * @brief TIM1_CH1N GPIO configuration
 */
void gpio_TIM1_CH1N_config();

#endif /* INC_GPIO_H_ */
