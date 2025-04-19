/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

bool cc1InterruptFlag;
uint32_t temp;
float distance;

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
  // TIM2 HC-SR04 configuration
  tim_TIM2_HCSR04_GPIO_config();
  tim_TIM2_HCSR04_config();

  while(1)
  {
    if(cc1InterruptFlag)
    {
      cc1InterruptFlag = false;
      // PSC = 71 -> 1000000 xung = 1s
      distance = (float)temp/(10000.0f)*(170.0f);
    }
    printf("TIM2->CCR1 = %lu", TIM2->CCR1);
    printf("TIM2->CCR2 = %lu", TIM2->CCR2);
    printf("\nDistance: %.4f cm", distance);
    rcc_msDelay(1000);
  }
}

void TIM2_IRQHandler()
{
  if(TIM2->SR & TIM_SR_CC2IF)
  {
    TIM2->SR &= ~(TIM_SR_CC2IF);
    cc1InterruptFlag = true;
    temp = (TIM2->CCR2) - (TIM2->CCR1);
  }
  NVIC_ClearPendingIRQ(TIM2_IRQn);
}
