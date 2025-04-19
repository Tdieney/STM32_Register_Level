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
  // Set parity to even
  USART1->CR1 &= ~(USART_CR1_PS);
  // Parity control enable
  USART1->CR1 &= ~(USART_CR1_PCE);
  // Word length to 8-bit
  USART1->CR1 &= ~(USART_CR1_M);
  // Stop bit = 1
  USART1->CR2 &= ~(USART_CR2_STOP);
  // Disable hardware flow control CTS, RTS
  USART1->CR3 &= ~(USART_CR3_CTSE | USART_CR3_RTSE);
  // Set baud rate to 115200
  USART1->BRR = 0;
  USART1->BRR |= 34U << 4U;
  USART1->BRR |= 12U << 0;
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
  uint32_t startTick = RCC_msGetTick();
  while(dataIdx < len)
  {
    if(USART1->SR & USART_SR_TXE) //Tx buffer empty
    {
      USART1->DR = data[dataIdx];
      dataIdx++;
    }
    else // Manage timeout
    {
      if(RCC_msGetTick() - startTick >= timeout)
      {
        return false;
      }
    }
  }
  // Wait for busy flag
  while(USART1->SR & USART_SR_TC)
  {
    if(RCC_msGetTick() - startTick >= timeout)
    {
      return false;
    }
  }
  return true;
}
