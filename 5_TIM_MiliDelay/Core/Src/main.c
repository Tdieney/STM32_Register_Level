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
  // TIM2 - delay configuration
//  tim_TIM2_delayConfig();
  tim_TIM2_myDelayConfig();

  printf("\nProgram is starting...");

  while(1)
  {
    printf("\nLED Toggle!");
    LED_PC13 = !LED_PC13;
    delay_ms(1000);
  }
}
