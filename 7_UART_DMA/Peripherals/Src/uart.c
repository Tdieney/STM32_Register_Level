/*
 * uart.c
 *
 *  Created on: Aug 21, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "uart.h"

/**
 * @brief UART1 GPIO configuration
 */
void uart_UART1_GPIO_config()
{
  // PA9 - TX, PA10 - RX
  // Enable portA clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  // AF mode
  GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_CNF10);
  GPIOA->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_0;
  // Output max 10MHz
  GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_MODE10);
  GPIOA->CRH |= GPIO_CRH_MODE9_0;
  // No remap UART1
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  AFIO->MAPR &= ~(AFIO_MAPR_USART1_REMAP);
}

/**
 * @brief UART1 Peripherals configuration
 */
void uart_UART1_config()
{
  // Enable UART1 clock
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  // Enable transmit
  USART1->CR1 |= USART_CR1_TE;
  // Enable receive
  USART1->CR1 |= USART_CR1_RE;
  // Set parity to even
  USART1->CR1 &= ~(USART_CR1_PS);
  // Parity control enable (DISABLE)
  USART1->CR1 &= ~(USART_CR1_PCE);
  // Word length to 8-bit
  USART1->CR1 &= ~(USART_CR1_M);
  // Stop bit = 1
  USART1->CR2 &= ~(USART_CR2_STOP);
  // Disable hardware flow control CTS, RTS
  USART1->CR3 &= ~(USART_CR3_CTSE | USART_CR3_RTSE);
  // Set baud rate to 115200
  USART1->BRR = 0;
  USART1->BRR |= 39U << 4U;
  USART1->BRR |= 1U << 0;
  // Clear some flags and enable
  USART1->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
  USART1->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);
  // Enable UART
  USART1->CR1 |= USART_CR1_UE;
}

/**
 * @brief UART transmit function
 */
bool uart_UART1_transmit(uint8_t *data, uint8_t len, uint32_t timeout)
{
  // Wait for TXE to start transmit
  // Write to DR as TXE flag is HIGH (Tx buffer empty)
  uint8_t dataIdx = 0;
  uint32_t startTick = rcc_msGetTick();
  while(dataIdx < len)
  {
    if(USART1->SR & USART_SR_TXE) //Tx buffer empty
    {
      USART1->DR = data[dataIdx];
      dataIdx++;
    }
    else if(rcc_msGetTick() - startTick >= timeout) // Manage timeout
    {
      return false;
    }
  }
  // Wait for busy flag
  while(!(USART1->SR & USART_SR_TC))
  {
    if(rcc_msGetTick() - startTick >= timeout)
    {
      return false;
    }
  }
  return true;
}

/**
 * @brief UART receive function
 */
bool uart_UART1_receive(uint8_t *data, uint8_t len, uint32_t timeout)
{
  // Write to DR as RXNE flag is HIGH (Rx buffer not empty)
  uint8_t dataRemain = len;
  uint32_t startTick = rcc_msGetTick();
  while(dataRemain > 0)
  {
    if(USART1->SR & USART_SR_RXNE) // Rx buffer not empty
    {
      *data++ = (uint8_t)(USART1->DR & 0xFF);
      dataRemain--;
    }
    else if(rcc_msGetTick() - startTick >= timeout) // Manage timeout
    {
      return false;
    }
  }
  return true;
}

/**
 * @brief UART1 DMA configuration
 */
void uart_UART1_DMA_config()
{
  // Enable UART1 DMA
  USART1->CR3 |= USART_CR3_DMAR | USART_CR3_DMAT;
  // Enable DMA1 clock
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;

  /* Tx channel DMA configuration - DMA1_channel4 */
  // Clear DMA1 - Channel4 status flags
  DMA1->IFCR |= (0xFUL << 12U);
  // Peripherals address
  DMA1_Channel4->CPAR = (uint32_t)(&(USART1->DR));
  // Disable M2M mode
  DMA1_Channel4->CCR &= ~(DMA_CCR_MEM2MEM);
  // Set channel priority low
  DMA1_Channel4->CCR &= ~(DMA_CCR_PL);
  // Normal mode
  DMA1_Channel4->CCR &= ~(DMA_CCR_CIRC);
  // Enable memory increment
  DMA1_Channel4->CCR |= DMA_CCR_MINC;
  // Disable peripheral increment
  DMA1_Channel4->CCR &= ~(DMA_CCR_PINC);
  // Peripherals 8-bit
  DMA1_Channel4->CCR &= ~(DMA_CCR_PSIZE);
  // Memory 8-bit
  DMA1_Channel4->CCR &= ~(DMA_CCR_MSIZE);
  // Direction
  DMA1_Channel4->CCR |= DMA_CCR_DIR;
  // Disable DMA
  DMA1_Channel4->CCR &= ~(DMA_CCR_EN);
  // Enable transfer complete interrupt of DMA
  DMA1_Channel4->CCR |= DMA_CCR_TCIE;

  /* Rx channel DMA configuration - DMA1_channel5 */
  // Clear DMA1 - Channel5 status flags
  DMA1->IFCR |= (0xFUL << 16U);
  // Peripherals address
  DMA1_Channel5->CPAR = (uint32_t)(&(USART1->DR));
  // Disable M2M mode
  DMA1_Channel5->CCR &= ~(DMA_CCR_MEM2MEM);
  // Set channel priority low
  DMA1_Channel5->CCR &= ~(DMA_CCR_PL);
  // Normal mode
  DMA1_Channel5->CCR &= ~(DMA_CCR_CIRC);
  // Enable memory increment
  DMA1_Channel5->CCR |= DMA_CCR_MINC;
  // Disable peripheral increment
  DMA1_Channel5->CCR &= ~(DMA_CCR_PINC);
  // Peripherals 8-bit
  DMA1_Channel5->CCR &= ~(DMA_CCR_PSIZE);
  // Memory 8-bit
  DMA1_Channel5->CCR &= ~(DMA_CCR_MSIZE);
  // Direction
  DMA1_Channel5->CCR &= ~(DMA_CCR_DIR);
  // Disable DMA
  DMA1_Channel5->CCR &= ~(DMA_CCR_EN);
  // Enable transfer complete interrupt of DMA
  DMA1_Channel5->CCR |= DMA_CCR_TCIE;

  // Enable DMA interrupt
  NVIC_SetPriority(DMA1_Channel4_IRQn, 6);
  NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  NVIC_SetPriority(DMA1_Channel5_IRQn, 6);
  NVIC_EnableIRQ(DMA1_Channel5_IRQn);
}

/**
 * @brief UART transmit function
 */
void uart_UART1_DMA_transmit(uint8_t *data, uint8_t len)
{
  // Clear DMA1 - Channel4 status flags
  DMA1->IFCR |= (0xFUL << 12U);
  // Memory address
  DMA1_Channel4->CMAR = (uint32_t)data;
  // Number of transfer
  DMA1_Channel4->CNDTR = (uint16_t)len;
  // Enable DMA
  DMA1_Channel4->CCR |= DMA_CCR_EN;
}

/**
 * @brief UART receive function
 */
void uart_UART1_DMA_receive(uint8_t *data, uint8_t len)
{
  // Clear interrupt flags by overrun error
  __IO uint32_t readTemp;
  readTemp = USART1->SR;
  readTemp = USART1->DR;
  (void)readTemp; // prevent compiler warning
  // Clear DMA1 - Channel5 status flags
  DMA1->IFCR |= (0xFUL << 16U);
  // Memory address
  DMA1_Channel5->CMAR = (uint32_t)data;
  // Number of transfer
  DMA1_Channel5->CNDTR = (uint16_t)len;
  // Enable DMA
  DMA1_Channel5->CCR |= DMA_CCR_EN;
}

