/*
 * printf_redirect.c
 *
 *  Created on: Aug 22, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "uart.h"

int __io_putchar(int ch);
int _write(int file, char *ptr, int len);

int __io_putchar(int ch)
{
  uint8_t c[1];
  c[0] = ch & 0x00FF;
  uart_UART1_transmit(&c[0], 1, 100);
  return ch;
}

int _write(int file, char *ptr, int len)
{
  for(int DataIdx = 0; DataIdx < len; DataIdx++)
  {
    __io_putchar(*ptr++);
  }
  return len;
}
