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
void adc_single_config(ADC_CHANNEL channel)
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
  // Start
//  ADC1->CR2 |= ADC_CR2_SWSTART;     // thieu van chay????????????????
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

/**
 * @brief ADC enable/disable Interrupt
 */
void adc_enableEOC_IT()
{
  // Enable EOCIE
  ADC1->CR1 |= ADC_CR1_EOCIE;
  // Enable ADC interrupt at NVIC
  NVIC_SetPriority(ADC1_2_IRQn, 1);
  NVIC_EnableIRQ(ADC1_2_IRQn);
}

void adc_disableEOC_IT()
{
  // Disable EOCIE
  ADC1->CR1 &= ~ADC_CR1_EOCIE;
  // Disable ADC interrupt at NVIC
  NVIC_DisableIRQ(ADC1_2_IRQn);
}

/**
 * @brief ADC multi channel configuration
 */
void adc_multiChannel_config()
{
  // Enable ADC1 clock
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  // Right alignment
  ADC1->CR2 &= ~(ADC_CR2_ALIGN);
  // Single conversion
  ADC1->CR2 &= ~(ADC_CR2_CONT);
//  // Software trigger
//  ADC1->CR2 |= ADC_CR2_EXTSEL;
  // TIM3_TRGO
  ADC1->CR2 |= ADC_CR2_EXTTRIG;
  // Select TIM3_TRGO as external trigger source
  ADC1->CR2 &= ~(ADC_CR2_EXTSEL);
  ADC1->CR2 |= ADC_CR2_EXTSEL_2;
  // 28 cycles -> Sample time = (12 + 28.5)/12MHz = 3.375us
  // PA1, PA2, PA3
  ADC1->SMPR2 &= ~(ADC_SMPR2_SMP1 | ADC_SMPR2_SMP2 | ADC_SMPR2_SMP3);
  ADC1->SMPR2 |= (ADC_SMPR2_SMP1_0 | ADC_SMPR2_SMP1_1 | ADC_SMPR2_SMP2_0 | \
                  ADC_SMPR2_SMP2_1 | ADC_SMPR2_SMP3_0 | ADC_SMPR2_SMP3_1);
  // Number of conversion = 3
  ADC1->SQR1 &= ~(ADC_SQR1_L);
  ADC1->SQR1 |= ADC_SQR1_L_1;
  // Sequencer
  //ADC1->SQR3 = 0;
  // Rank 1 - PA1
  ADC1->SQR3 |= (1UL << 0U);
  // Rank 2 - PA2
  ADC1->SQR3 |= (2UL << 5U);
  // Rank 3 - PA3
  ADC1->SQR3 |= (3UL << 10U);
  // Enable scan mode
  ADC1->CR1 |= ADC_CR1_SCAN;
  // Enable DMA - ADC registers
  ADC1->CR2 |= ADC_CR2_DMA;
  // Power up ADC
  ADC1->CR2 |= ADC_CR2_ADON;
  // Wait for ADC to stabilize by calibrate it
  ADC1->CR2 |= ADC_CR2_RSTCAL;
  while(ADC1->CR2 & ADC_CR2_RSTCAL);
  ADC1->CR2 |= ADC_CR2_CAL;
  while(ADC1->CR2 & ADC_CR2_CAL);
}

/**
 * @brief ADC DMA configuration
 */
void adc_multiChannel_DMA_config(uint16_t *pADCBuffer)
{
  // ADC1-> DMA1 - Channel1
  // Enable DMA1 clock
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;
  // Clear DMA1 - Channel1 status flags
  DMA1->IFCR |= 0xFUL;
  // Peripherals address (src)
  DMA1_Channel1->CPAR = (uint32_t)(&(ADC1->DR));
  // Memory address (dst)
  DMA1_Channel1->CMAR = (uint32_t)pADCBuffer;
  // Number of transfer
  DMA1_Channel1->CNDTR =  3UL;
  // Disable M2M mode
  DMA1_Channel1->CCR &= ~(DMA_CCR_MEM2MEM);
  // Set channel priority low
  DMA1_Channel1->CCR &= ~(DMA_CCR_PL);
  // Circular/normal mode
  DMA1_Channel1->CCR |= DMA_CCR_CIRC; //??????????????????
  // Enable memory increment
  DMA1_Channel1->CCR |= DMA_CCR_MINC;
  // Disable peripheral increment
  DMA1_Channel1->CCR &= ~(DMA_CCR_PINC);
  // Peripherals 16-bit
  DMA1_Channel1->CCR &= ~(DMA_CCR_PSIZE);
  DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0;
  // Memory 16-bit
  DMA1_Channel1->CCR &= ~(DMA_CCR_MSIZE);
  DMA1_Channel1->CCR |= DMA_CCR_MSIZE_0;
  // Direction = src -> dst
  DMA1_Channel1->CCR &= ~(DMA_CCR_DIR);
  // Enable DMA
  DMA1_Channel1->CCR |= DMA_CCR_EN;
  // Enable transfer complete interrupt of DMA
  DMA1_Channel1->CCR |= DMA_CCR_TCIE;

  // NVIC configuration
  NVIC_SetPriority(DMA1_Channel1_IRQn, 2);
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

/**
 * @brief ADC Analog watchdog configuration
 * @param lowThreshold/highThreshold 0 - 4095
 */
void adc_AWD_config(ADC_CHANNEL channel, uint16_t lowThreshold, uint16_t highThreshold)
{
  // Set threshold value
  ADC1->LTR = lowThreshold;
  ADC1->HTR = highThreshold;
  // Select AWD channel
  ADC1->CR1 &= ~(ADC_CR1_AWDCH);
  ADC1->CR1 |= (uint32_t)channel << 0U;
  // AWD on single channel
  ADC1->CR1 |= ADC_CR1_AWDSGL;
  // Disable injected channels AWD
  ADC1->CR1 &= ~(ADC_CR1_JAWDEN);
  // Enable regular channels AWD
  ADC1->CR1 |= ADC_CR1_AWDEN;
  // Enable AWD interrupt
  ADC1->CR1 |= ADC_CR1_AWDIE;
  // Enable ADC1 interrupt (NVIC)
  NVIC_SetPriority(ADC1_2_IRQn, 1);
  NVIC_EnableIRQ(ADC1_2_IRQn);
}
