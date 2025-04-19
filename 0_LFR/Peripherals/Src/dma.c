/*
 * dma.c
 *
 *  Created on: Dec 18, 2021
 *      Author: THINH
 */

#include "dma.h"

bool tcFlag = false;

/**
 * @brief DMA configuration
 */
void dma_config(uint32_t *pADCBuffer)
{
  // DMA1 - Channel1
  // Enable DMA1 clock
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;
  // Clear DMA1 - Channel1 status flags
  DMA1->IFCR |= 0xFUL;
  // Peripherals address (src)
  DMA1_Channel1->CPAR = (uint32_t)(&(ADC1->DR));
  // Memory address (dst)
  DMA1_Channel1->CMAR = (uint32_t)pADCBuffer;
  // Number of transfer
  DMA1_Channel1->CNDTR = 5UL;
  // Disable M2M mode
  DMA1_Channel1->CCR &= ~(DMA_CCR_MEM2MEM);
  // Set channel priority low
  DMA1_Channel1->CCR &= ~(DMA_CCR_PL);
  // Circular/normal mode
  DMA1_Channel1->CCR |= DMA_CCR_CIRC;
  // Enable memory increment
  DMA1_Channel1->CCR |= DMA_CCR_MINC;
  // Disable peripheral increment
  DMA1_Channel1->CCR &= ~(DMA_CCR_PINC);
  // Peripherals 32-bit
  DMA1_Channel1->CCR &= ~(DMA_CCR_PSIZE);
  DMA1_Channel1->CCR |= DMA_CCR_PSIZE_1;
  // Memory 32-bit
  DMA1_Channel1->CCR &= ~(DMA_CCR_MSIZE);
  DMA1_Channel1->CCR |= DMA_CCR_MSIZE_1;
  // Direction = src -> dst
  DMA1_Channel1->CCR &= ~(DMA_CCR_DIR);
  // Enable DMA
  DMA1_Channel1->CCR |= DMA_CCR_EN;
  // Enable transfer complete interrupt of DMA
  DMA1_Channel1->CCR |= DMA_CCR_TCIE;

  // NVIC configuration
  NVIC_SetPriority(DMA1_Channel1_IRQn, 1);
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);
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

