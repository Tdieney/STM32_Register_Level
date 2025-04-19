/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

uint8_t rxBuf[10];

int main(void)
{
  // Configure 72MHz clock
  rcc_HSE_config();
  rcc_SysTick_config();
  // UART configuration
  uart_UART1_GPIO_config();
  uart_UART1_config();
  // LED configuration
  gpio_LED_config();
  // Button configuration
  gpio_PB_config();
  // Slide switch configuration
  gpio_SW_config();

  printf("Write 5 bytes to terminal:\n");

  while(1)
  {
    if(uart_UART1_receive(rxBuf, 5, 1000))
    {
      uart_UART1_transmit(rxBuf, 5, 1000);
    }
  }
}


