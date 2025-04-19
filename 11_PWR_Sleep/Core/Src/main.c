/*
 * main.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

void delay(uint32_t ms)
{
  while(ms--);
}

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
  // Enable button interrupt
  exti_PB_config();

  for(uint8_t i = 10; i > 0; i--)
  {
    printf("Enter sleep mode in %u.\n", i);
    LED_PC13 = !LED_PC13;
    rcc_msDelay(1000);
  }
  // Enter sleep mode
  pwr_enterSleep();

  printf("MCU exited from sleep mode.\n");
  rcc_msDelay(1000);
  // Notice: no need to config system again

  while(1)
  {
    LED_PC13 = !LED_PC13;
    rcc_msDelay(1000);
  }
}

void EXTI0_IRQHandler()
{
  printf("Back to sleep.\n");
  NVIC_ClearPendingIRQ(EXTI0_IRQn);
  EXTI->PR |= EXTI_PR_PR0;
}
