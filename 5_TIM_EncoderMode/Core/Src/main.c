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
  // TIM4 Encoder configuration
  gpio_TIM4_Encoder_config();
  tim_TIM4_Encoder_config();

  while(1)
  {
    printf("\nEncoder counter: %u", (uint16_t)(TIM4->CNT));
    printf("\nDirection: %s", ((TIM4->CR1 & TIM_CR1_DIR) == 0) ? "CW" : "CCW");
    rcc_msDelay(500);
  }
}
