/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

bool adcEOCFlag = false;
uint16_t adcValue;

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
  adc_enableEOC_IT();
  adc_start();

  printf("\nProgram is starting...");

  while(1)
  {
    if(adcEOCFlag)
    {
      adcEOCFlag = false;
      printf("\nADC = %d", adcValue);
      //rcc_msDelay(500);
      adc_start();
    }
  }
}

void ADC1_2_IRQHandler()
{
  // Read ADC value, this read function will clear EOC flag
  adcValue = adc_readValue();
  NVIC_ClearPendingIRQ(ADC1_2_IRQn);
  adcEOCFlag = true;
}
