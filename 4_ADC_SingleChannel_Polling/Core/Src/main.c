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
  // ADC configuration
  adc_GPIO_config();
  adc_single_config(ADC_SINGLE_CHANNEL1);

  printf("\nProgram is starting...");

  uint16_t adcValue;

  while(1)
  {
    adc_start();
    if(adc_pollForEOC(5))
    {
      adcValue = adc_readValue();
      printf("\nADC = %d", adcValue);
    }
    else printf("\nADC read failed!");
    rcc_msDelay(500);
  }
}
