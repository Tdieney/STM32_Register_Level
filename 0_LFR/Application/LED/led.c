/*
 * led.c
 *
 *  Created on: Dec 18, 2021
 *      Author: THINH
 */

#include "led.h"

/**
 * @brief Turn ON all LED
 */
void allLedOn()
{
  GPIOA->ODR = 0x1700;
  GPIOB->ODR = 0xF000;
  tim_msDelay(5);
  GPIOA->ODR = 0x0F00;
  GPIOB->ODR = 0xF000;
  tim_msDelay(5);
}

/**
 * @brief Turn OFF all LED
 */
void allLedOff()
{
  GPIOA->ODR = 0x0000;
  GPIOB->ODR = 0x0000;
}

/**
 * @brief Blink all LED
 * @param miliseconds Time of each ON/OFF state
 *        num Number of times LED blinks
 */
void allLedToggle(uint16_t miliseconds, uint8_t num)
{
  for(uint8_t n = 0; n < num; n++)
  {
    uint8_t a = miliseconds/10;
    for(uint8_t b = 0; b < a; b++)
    {
      allLedOn();
    }
    allLedOff();
    tim_msDelay(miliseconds);
  }
}

/**
 * @brief Turn ON LED 1->7
 */
void ledOn(uint8_t num)
{
  // Disable LED7SEG
  GPIOA->BRR |= (1 << 11);
  // Enable LED
  GPIOA->BSRR |= (1 << 12);
  // Turn ON LED
  if(num < 4)
  {
    GPIOA->BSRR |= (1 << (num + 7));
  }
  else
  {
    GPIOB->BSRR |= (1 << (19 - num));
  }
}

/**
 * @brief Turn ON LED 1->7
 */
void ledOff(uint8_t num)
{
  // Disable LED
  GPIOA->BRR |= (1 << 11);
  // Enable LED7SEG
  GPIOA->BSRR |= (1 << 12);
  // Turn OFF LED
  if(num < 4)
  {
    GPIOA->BRR |= (1 << (num + 7));
  }
  else
  {
    GPIOB->BRR |= (1 << (19 - num));
  }
}
