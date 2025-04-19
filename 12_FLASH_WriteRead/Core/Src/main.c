/*
 * main.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

// Flash: constant + code

#include "main.h"

int main()
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

  // Flash - 0x0800 FC00
  // Write
  flash_unlock();
  flash_erase(0x0800FC00);
  uint16_t flashWrite[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
  flash_write16(0x0800FC00, flashWrite, 5);
  flash_lock();

  // Read
  uint16_t flashRead[5];
  flash_read16(0x0800FC00, flashRead, 5);

  // Display result
  for(uint8_t i = 0; i < 5; i++)
  {
    printf("Flash[%u] = 0x%02X\n", i, flashRead[i]);
    rcc_msDelay(1000);
  }

  while(1)
  {
    LED_PC13 = !LED_PC13;
    rcc_msDelay(1000);
  }
}
