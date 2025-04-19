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

  if(PWR->CSR & PWR_CSR_SBF)
  {
    // Clear standby flag
    PWR->CR |= PWR_CR_CSBF;
  }

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
    printf("Enter standby mode in %u.\n", i);
    LED_PC13 = !LED_PC13;
    rcc_msDelay(1000);
  }
  // Enter standby mode
  pwr_enterStandby();

  printf("MCU exited from standby mode.\n");
  rcc_msDelay(1000);
  /*
   * Note:
   * In standby, the MCU is really turned off and wake up is reset. (the lowest power mode)
   * Standby mode can be exit by: reset button/pin, iwdg, rtc alarm or event, tamper event
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

