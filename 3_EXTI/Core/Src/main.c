/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

bool extiFlag;

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
  // EXTI configuration
  exti_PB_config();

  printf("\nProgram is starting...");
  while(1)
  {
    if(extiFlag)
    {
      extiFlag = false;
      LED_PC13 = !LED_PC13;
      printf("\n---LED Toggle!---");
      rcc_msDelay(100);
      // Unmask EXTI0
      EXTI->IMR |= EXTI_IMR_IM0;
    }
    printf("\nHello World!");
    rcc_msDelay(500);
  }
}

void EXTI0_IRQHandler()
{
  NVIC_ClearPendingIRQ(EXTI0_IRQn);
  EXTI->PR |= EXTI_PR_PR0;
  // Mask EXTI0 to avoid button debounce
  EXTI->IMR &= ~(EXTI_IMR_IM0);
  // Application
  extiFlag = true;
}
