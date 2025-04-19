/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

#define LCD1602_I2C_ADDR  (0x4E)

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
  // I2C configuration
  i2c_I2C1_GPIO_config();
  i2c_I2C1_config();
  // LCD initialize
  lcd_init();

  lcd_goto_xy(0,4);
  lcd_string("VanThinh");
  lcd_goto_xy(1,4);
  lcd_string("18142390");
  rcc_msDelay(2000);

  while(1)
  {
    lcd_clear();
    lcd_goto_xy(0,4);
    lcd_string("VanThinh");
    lcd_goto_xy(1,4);
    lcd_string("18142390");
    rcc_msDelay(2000);
    lcd_clear();
    rcc_msDelay(2000);
    for(int i = 0; i < 16; i++)
    {
      lcd_clear();
      lcd_16x2_2line_num(4, i);
      rcc_msDelay(500);
    }
  }
}
