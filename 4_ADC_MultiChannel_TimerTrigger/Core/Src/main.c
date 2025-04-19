/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

bool tcFlag = false;
bool awdFlag = false;
uint16_t adcValue[3];

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
  adc_multiChannel_config();
  adc_multiChannel_DMA_config(adcValue);
//  adc_start();
  // TIM3 configuration
  tim_TIM3_config();

  printf("\nProgram is starting...");

  while(1)
  {
    if(tcFlag)
    {
      tcFlag = false;
      printf("\nChannel1 = %u     Channel2 = %u     Channel3 = %u", adcValue[0], adcValue[1], adcValue[2]);
      printf("\n-----------------------------------");
      gpio_LED_toggle();
    }
  }
}

// DMA transfer complete interrupt
void DMA1_Channel1_IRQHandler()
{
  if(DMA1->ISR & DMA_ISR_TCIF1)
  {
    // Clear flags
    NVIC_ClearPendingIRQ(DMA1_Channel1_IRQn);
    DMA1->IFCR |= DMA_IFCR_CTCIF1;
    tcFlag = true;
  }
}
