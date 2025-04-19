/*
 * adc.c
 *
 *  Created on: Aug 23, 2021
 *      Author: THINH
 */

#include "adc.h"

/**
 * @brief ADC GPIO pins: PA1-POT, PA2-X, PA3-Y
 */
void adc_GPIO_config()
{
  // Enable portA clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  // PA1, PA2, PA3 as analog input mode
  GPIOA->CRL &= ~(0xFFFUL << 4U);
}

/**
 * @brief ADC single channel configuration
 */
void adc_single_config(ADC_SINGLE_CHANNEL channel)
{
  // Enable ADC1 clock
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  // Right alignment
  ADC1->CR2 &= ~(ADC_CR2_ALIGN);
  // Single conversion
  ADC1->CR2 &= ~(ADC_CR2_CONT);
  // Software trigger
  ADC1->CR2 |= ADC_CR2_EXTSEL;
  // 28 cycles -> Sample time = (12 + 28)/12MHz = 3.3us
  // PA1, PA2, PA3
  ADC1->SMPR2 &= ~(ADC_SMPR2_SMP1 | ADC_SMPR2_SMP2 | ADC_SMPR2_SMP3);
  ADC1->SMPR2 |= (ADC_SMPR2_SMP1_0 | ADC_SMPR2_SMP1_1 | ADC_SMPR2_SMP2_0 | \
                  ADC_SMPR2_SMP2_1 | ADC_SMPR2_SMP3_0 | ADC_SMPR2_SMP3_1);
  // Number of conversion = 1
  ADC1->SQR1 &= ~(ADC_SQR1_L);
  // Rank 1 Channel 1, 2, 3
  ADC1->SQR3 = (uint32_t)channel;
  // Power up ADC
  ADC1->CR2 |= ADC_CR2_ADON;
  // Wait for ADC to stabilize by calibrate it
  ADC1->CR2 |= ADC_CR2_RSTCAL;
  while(ADC1->CR2 & ADC_CR2_RSTCAL);
  ADC1->CR2 |= ADC_CR2_CAL;
  while(ADC1->CR2 & ADC_CR2_CAL);
}

/**
 * @brief ADC start - SWSTART
 */
void adc_start()
{
  // Clear SR
  ADC1->SR = 0;
  // Generate software start
  ADC1->CR2 |= ADC_CR2_SWSTART;     // thieu van chay????????????????
  ADC1->CR2 |= ADC_CR2_ADON;
}

/**
 * @brief ADC stop
 */
void adc_stop()
{
  // Clear SR
  ADC1->SR = 0;
  // Clear SWSTART bit
  ADC1->CR2 &= ~(ADC_CR2_SWSTART);
}

/**
 * @brief ADC poll for End of Conversion
 *        This function should be used immediately after adc_start()
 */
bool adc_pollForEOC(uint32_t msTimeout)
{
  uint32_t startTick = rcc_msGetTick();
  while((ADC1->SR & ADC_SR_EOC) == 0)
  {
    if(rcc_msGetTick() - startTick > msTimeout)
    {
      return false;
    }
  }
  return true;
}

/**
 * @brief Read ADC value
 */
uint16_t adc_readValue()
{
  return (ADC1->DR & 0xFFFUL);
}
