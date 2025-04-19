/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

bool uartDMAReceiveFlag = 0;
bool uartDMATransmitFlag = 0;
uint8_t rxBuf[10];

int main(void)
{
  // Configure 72MHz clock
  rcc_HSE_config();
  rcc_SysTick_config();
  // UART configuration
  uart_UART1_GPIO_config();
  uart_UART1_config();
  uart_UART1_DMA_config();
  // LED configuration
  gpio_LED_config();
  // Button configuration
  gpio_PB_config();
  // Slide switch configuration
  gpio_SW_config();

  printf("Write 5 bytes to terminal:\n");
  // Start DMA receive
  uart_UART1_DMA_receive(rxBuf, 5);

  while(1)
  {
    if(uartDMAReceiveFlag)
    {
      uartDMAReceiveFlag = 0;
      uart_UART1_DMA_transmit(rxBuf, 5);
      while(!uartDMATransmitFlag);
      uartDMATransmitFlag = 0;
      printf("Write 5 bytes to terminal:\n");
      // Start DMA receive
      uart_UART1_DMA_receive(rxBuf, 5);
    }
    // DMA counter
    printf("DMA receive counter = %d\n", (int)DMA1_Channel5->CNDTR);
    LED_PC13 = !LED_PC13;
    rcc_msDelay(500);
  }
}

// UART DMA - TX
void DMA1_Channel4_IRQHandler()
{
  if(DMA1->ISR & DMA_ISR_TCIF4)
  {
    // Disable DMA
    DMA1_Channel4->CCR &= ~(DMA_CCR_EN);
    // Clear flags
    DMA1->IFCR |= DMA_IFCR_CGIF4 | DMA_IFCR_CTCIF4;
//    NVIC_ClearPendingIRQ(DMA1_Channel4_IRQn);
    // Notify application
    uartDMATransmitFlag = 1;
  }
  // Check error transfer
  if(DMA1->ISR & DMA_ISR_TEIF4)
  {
    // Clear flags
    DMA1->IFCR |= DMA_IFCR_CGIF4 | DMA_IFCR_CTEIF4;
//    NVIC_ClearPendingIRQ(DMA1_Channel4_IRQn);
  }
}
// UART DMA - RX
void DMA1_Channel5_IRQHandler()
{
  if(DMA1->ISR & DMA_ISR_TCIF5)
  {
    // Disable DMA
    DMA1_Channel5->CCR &= ~(DMA_CCR_EN);
    // Clear flags
    DMA1->IFCR |= DMA_IFCR_CGIF5 | DMA_IFCR_CTCIF5;
//    NVIC_ClearPendingIRQ(DMA1_Channel5_IRQn);
    // Notify application
    uartDMAReceiveFlag = 1;
  }
  // Check error transfer
  if(DMA1->ISR & DMA_ISR_TEIF5)
  {
    // Clear flags
    DMA1->IFCR |= DMA_IFCR_CGIF5 | DMA_IFCR_CTEIF5;
//    NVIC_ClearPendingIRQ(DMA1_Channel5_IRQn);
  }
}


