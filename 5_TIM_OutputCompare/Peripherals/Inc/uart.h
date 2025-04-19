/*
 * uart.h
 *
 *  Created on: Aug 21, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

/**
 * @brief UART1 GPIO configuration
 */
void uart_UART1_GPIO_config();

/**
 * @brief UART1 Peripherals configuration
 */
void uart_UART1_config();

/**
 * @brief UART transmit function
 */
bool uart_UART1_transmit(uint8_t *data, uint8_t len, uint32_t timeout);

#endif /* INC_UART_H_ */
