/*
 * rcc.c
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
  gpio_LED_write(0);
  // SPI configuration
  spi_RFID_CS_config();
  spi_GPIO_config();
  spi_config();
//  // Set PB0 to 3.3v
//  GPIOB->BSRR |= GPIO_BSRR_BS0;
//  rcc_msDelay(500);
  // Read RFID registers using SPI
//  for(uint8_t i = 0; i < 0x40; i++)
//  {
//    printf("Register[0x%02X] = 0x%02X\n", i, rc522_regRead8(i));
//    rcc_msDelay(50);
//  }
  // RFID module
  rc522_init();
  uint8_t myID[5] = {0xD3, 0x18, 0xE3, 0x9A, 0xB2};
  uint8_t cardID[5];

  // Simple RFID card reader
  printf("Place your card...\n");

  while(1)
  {
    if(rc522_checkCard(cardID))
    {
      gpio_LED_write(1);
      printf("Card is detected with ID:\n");
      for(uint8_t i = 0; i < 5; i++)
      {
        printf("ID[%u] = 0x%02X\n", i, cardID[i]);
      }
      if(rc522_compareIds(cardID, myID))
      {
        printf("Success, access granted!\n");
      }
      else
      {
        printf("Failed, access denied.\n");
      }
      printf("*************************************");
      rcc_msDelay(2000);
      gpio_LED_write(0);
    }
    rcc_msDelay(2000);
  }
}
