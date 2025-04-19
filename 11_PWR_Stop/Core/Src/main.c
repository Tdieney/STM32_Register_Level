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
    printf("Enter stop mode in %u.\n", i);
    LED_PC13 = !LED_PC13;
    rcc_msDelay(1000);
  }
  // Enter stop mode
  pwr_enterStop();

  // Reconfigure system clock
  rcc_HSE_config();
  rcc_SysTick_config();

  printf("MCU exited from stop mode.\n");
  rcc_msDelay(1000);
  /*
   * Note:
   * Stop mode operate in a similar way as sleep mode
   * But in stop mode, HSI and HSE are halted and peripheral clocks all disabled apart from EXTI to generate interrupt
   * In stop mode any EXTI Line can wakeup the processor
   * Stop mode exit on HSI clock, thus needs to reconfigure for HSE on exit from stop mode
   */

  while(1)
  {
    LED_PC13 = !LED_PC13;
    rcc_msDelay(1000);
  }
}

void EXTI0_IRQHandler()
{
  NVIC_ClearPendingIRQ(EXTI0_IRQn);
  EXTI->PR |= EXTI_PR_PR0;
}
