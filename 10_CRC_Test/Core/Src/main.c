/*
 * main.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

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
  // Slide switch configuration
  gpio_SW_config();

  // CRC configuration
  crc_enable();
  // Test CRC calculation
  crc_reset();
  crc_accumulate(0x00110022);
  crc_accumulate(0x00330044);
  // Read CRC
  uint32_t calcCRC = crc_read();

  printf("Result of CRC-32 calculation on STM32: 0x%08X\n", (unsigned int)calcCRC);

  while(1)
  {

  }
}
