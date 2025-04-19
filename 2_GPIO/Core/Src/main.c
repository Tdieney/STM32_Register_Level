/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

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
  // Slide switchs configuration
  gpio_SW_config();
  LED_PC13 = 0;

//  printf("\nProgram is starting...");
  while(1)
  {
    LED_PC13 = !LED_PC13;
//    gpio_LED_write(gpio_PB_read());
//    gpio_LED_write(gpio_SW1_read());
//    gpio_LED_write(gpio_SW2_read());
    printf("\nHello World!");
    rcc_msDelay(1000);
  }
}
