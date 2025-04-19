/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

uint8_t rxBuf[10];

int main(void)
{
  // Configure 72MHz clock
  rcc_HSE_config();
  rcc_SysTick_config();
  // UART configuration
  uart_UART1_GPIO_config();
  uart_UART1_IT_config();
  // LED configuration
  gpio_LED_config();
  // Button configuration
  gpio_PB_config();
  // Slide switch configuration
  gpio_SW_config();

  while(1)
  {

  }
}

void USART1_IRQHandler(void)
{
  // Check if we are here because of RXNE interrupt
  if(USART1->SR & USART_SR_RXNE) // if RX is not empty
  {
    // Fetch received data
    char temp = USART1->DR;
    // Send it back
    USART1->DR = temp;
    while(!(USART1->SR & USART_SR_TXE));
  }
  // Check if we are here because of RXNE interrupt
  if(USART1->SR & USART_SR_TXE) // if TX is empty
  {
    // Handle trasmit
    // USART1->DR = 0x54;
  }
}


