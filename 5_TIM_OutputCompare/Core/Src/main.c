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
  // TIM1_CH1N output compare configuration
  gpio_TIM1_CH1N_config();
  tim_TIM1_CH1N_OC_config();

  while(1)
  {
    printf("\nTIM1->CNT = %d", (int)TIM1->CNT);
    rcc_msDelay(100);
  }
}
