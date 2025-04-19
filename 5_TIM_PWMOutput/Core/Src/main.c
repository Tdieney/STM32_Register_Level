/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

uint8_t R_value, G_value, B_value;

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
  // TIM3 PWM configuration
  gpio_TIM3_PWM_RGB_config();
  tim_TIM3_PWM_RGB_config();

  while(1)
  {
    R_value = rand();
    G_value = rand();
    B_value = rand();
    tim_TIM3_PWM_setRGB(R_value, G_value, B_value);
    rcc_msDelay(100);
  }
}
