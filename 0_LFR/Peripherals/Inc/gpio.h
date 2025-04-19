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

/**
 * @brief GPIO configuration
 */
void gpio_config();

#endif /* INC_GPIO_H_ */
