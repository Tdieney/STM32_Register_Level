/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

int main(void)
{
  rcc_HSE_config();
  rcc_SysTick_config();
  // UART configuration
  uart_UART1_GPIO_config();
  uart_UART1_config();

  printf("\nProgram is starting...");
  while(1)
  {
    printf("\nHello World!");
    rcc_msDelay(1000);
  }
}
