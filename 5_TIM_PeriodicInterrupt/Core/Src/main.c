/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

bool periodicINTFlag = false;

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
  // TIM2 periodic interrupt configuration
  tim_TIM2_periodicINTConfig();

  printf("\nProgram is starting...");

  while(1)
  {
    if(periodicINTFlag)
    {
      periodicINTFlag = false;
      printf("\nLED Toggle!");
      LED_PC13 = ~LED_PC13;
    }
  }
}

void TIM2_IRQHandler()
{
  if(TIM2->SR & TIM_SR_UIF)
  {
    TIM2->SR &= ~(TIM_SR_UIF);
    periodicINTFlag = true;
  }
  NVIC_ClearPendingIRQ(TIM2_IRQn);
}
