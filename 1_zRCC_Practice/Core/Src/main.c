/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

int main(void)
{
  // Configure 64MHz clock
  RCC_HSI_PLL_config();
  RCC_SysTick_config();
  // UART configuration
  uart_UART1_GPIO_config();
  uart_UART1_config();

//  printf("\nProgram is starting...");
  while(1)
  {
    printf("\nHello World!");
    delay_ms(1000);
  }
}
