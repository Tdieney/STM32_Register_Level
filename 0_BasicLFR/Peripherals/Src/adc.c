/*
 * adc.c
 *
 *  Created on: Aug 23, 2021
 *      Author: THINH
 */

#include "adc.h"

/**
 * @brief ADC1 and ADC2 configuration
 */
void adc_config()
{
  // Enable clocks
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_ADC2EN;
  // Right alignment
  ADC1->CR2 &= ~(ADC_CR2_ALIGN);
  ADC2->CR2 &= ~(ADC_CR2_ALIGN);
  // Continuous conversion mode
  ADC1->CR2 |= ADC_CR2_CONT;
  ADC2->CR2 |= ADC_CR2_CONT;
  // Software trigger
  ADC1->CR2 |= ADC_CR2_EXTSEL;
  ADC2->CR2 |= ADC_CR2_EXTSEL;
  // Set all sample time to 239.5 cycles
  // Sample time = (12.5 + 239.5)*6/64MHz = 23.625us
  ADC1->SMPR2 |= ADC_SMPR2_SMP0 | ADC_SMPR2_SMP1 | ADC_SMPR2_SMP2 | ADC_SMPR2_SMP3 | ADC_SMPR2_SMP8;
  ADC2->SMPR2 |= ADC_SMPR2_SMP4 | ADC_SMPR2_SMP5 | ADC_SMPR2_SMP6 | ADC_SMPR2_SMP7 | ADC_SMPR2_SMP9;
  // Number of conversion = 5 for each ADC
  ADC1->SQR1 &= ~(ADC_SQR1_L);
  ADC1->SQR1 |= ADC_SQR1_L_2;
  ADC2->SQR1 &= ~(ADC_SQR1_L);
  ADC2->SQR1 |= ADC_SQR1_L_2;
  // Sequencer
  ADC1->SQR3 = 0;
  ADC2->SQR3 = 0;
  // ADC1: Rank 1 - Channel0, Rank 2 - Channel1, Rank 3 - Channel2, Rank 4 - Channel3, Rank 5 - Channel8
  ADC1->SQR3 |= (0UL << 0U) | (1UL << 5U) | (2UL << 10U) | (3UL << 15U) | (8UL << 20U);
  // ADC2: Rank 1 - Channel4, Rank 2 - Channel5, Rank 3 - Channel6, Rank 4 - Channel7, Rank 5 - Channel9
  ADC2->SQR3 |= (4UL << 0U) | (5UL << 5U) | (6UL << 10U) | (7UL << 15U) | (9UL << 20U);
  // Enable scan mode
  ADC1->CR1 |= ADC_CR1_SCAN;
  ADC2->CR1 |= ADC_CR1_SCAN;
  // Enable DMA - ADC registers
  ADC1->CR2 |= ADC_CR2_DMA;
  ADC2->CR2 |= ADC_CR2_DMA;
  // Power up ADC
  ADC1->CR2 |= ADC_CR2_ADON;
  ADC2->CR2 |= ADC_CR2_ADON;
  // Wait for ADC to stabilize by calibrate it
  ADC1->CR2 |= ADC_CR2_RSTCAL;
  ADC2->CR2 |= ADC_CR2_RSTCAL;
  while((ADC1->CR2 & ADC_CR2_RSTCAL) || (ADC2->CR2 & ADC_CR2_RSTCAL));
  ADC1->CR2 |= ADC_CR2_CAL;
  ADC2->CR2 |= ADC_CR2_CAL;
  while((ADC1->CR2 & ADC_CR2_CAL) || (ADC2->CR2 & ADC_CR2_CAL));
  // Clear SR
  ADC1->SR = 0;
  ADC2->SR = 0;
  // Generate software start
  ADC1->CR2 |= ADC_CR2_SWSTART;
  ADC2->CR2 |= ADC_CR2_SWSTART;
  ADC1->CR2 |= ADC_CR2_ADON;
  ADC2->CR2 |= ADC_CR2_ADON;
}

