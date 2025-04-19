/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

bool eocFlag = false;
bool jeocFlag = false;
bool awdFlag = false;
uint16_t adcValue[3];
uint16_t jadcValue;
uint16_t temp;

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
  adc_AWD_config(ADC_CHANNEL2, 100, 4000);
//  adc_start();
  // TIM3 configuration
  tim_TIM3_config();
  adc_INJ_config(ADC_CHANNEL1);

  printf("\nProgram is starting...");

  while(1)
  {
    if(eocFlag)
    {
      eocFlag = false;
      temp = (uint16_t)adcValue[1]/12.41;
      printf("\nChannel1 = %u     Temp = %u     Channel3 = %u", adcValue[0], temp, adcValue[2]);
      gpio_LED_toggle();
      if(awdFlag)
      {
        awdFlag = false;
        printf("\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
      }
      else
      {
        printf("\n-----------------------------------");
      }
    }
    if(!BTN_PA0)
    {
      adc_INJ_start();
    }
    if(jeocFlag)
    {
      jeocFlag = false;
      jadcValue = ADC1->JDR1;
      printf("\nInjChannel = %u", jadcValue);
      rcc_msDelay(500);
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
    eocFlag = true;
  }
}

// ADC AWD interrupt
void ADC1_2_IRQHandler()
{
  // AWD
  if(ADC1->SR & ADC_SR_AWD)
  {
    ADC1->SR &= ~ADC_SR_AWD;
    // Signal to application
    awdFlag = true;
  }
  // JEOC
  if(ADC1->SR & ADC_SR_JEOC)
  {
    ADC1->SR &= ~ADC_SR_JEOC;
    // Signal to application
    jeocFlag = true;
  }
  NVIC_ClearPendingIRQ(ADC1_2_IRQn);
}
