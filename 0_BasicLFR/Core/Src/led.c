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
void led_onAll()
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
void led_offAll()
{
  GPIOA->ODR = 0x0000;
  GPIOB->ODR = 0x0000;
}

/**
 * @brief Blink all LED
 * @param miliseconds Time of each ON/OFF state
 *        num Number of times LED blinks
 */
void led_toggleAll(uint16_t miliseconds, uint8_t num)
{
  for(uint8_t n = 0; n < num; n++)
  {
    uint8_t a = miliseconds/10;
    for(uint8_t b = 0; b < a; b++)
    {
      led_onAll();
    }
    led_offAll();
    tim_msDelay(miliseconds);
  }
}

/**
 * @brief Turn ON LED 1->7
 */
void led_on(uint8_t num)
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
void led_off(uint8_t num)
{
  // Disable LED
  GPIOA->BSRR |= (1 << 11);
  // Enable LED7SEG
  GPIOA->BRR |= (1 << 12);
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

/**
 * @brief LED 7 segment shows characters
 */
void led7seg_putc(char c)
{
  // Disable LED
  GPIOA->BSRR |= (0x1 << 11);
  // Enable LED7SEG
  GPIOA->BRR |= (0x1 << 12);
  // Clear LED7SEG
  GPIOA->ODR &= ~(0x7 << 8);
  GPIOB->ODR &= ~(0xF << 12);
  /*
   * PB12: SEG_A
   * PB13: SEG_B
   * PB14: SEG_C
   * PB15: SEG_D
   * PA8:  SEG_F
   * PA9:  SEG_G
   * PA10: SEG_E
   */
  switch(c)
  {
    case '0':
    {
      GPIOA->ODR |= (0x5 << 8);
      GPIOB->ODR |= (0xF << 12);
      break;
    }
    case '1':
    {
      GPIOB->ODR |= (0x3 << 13);
      break;
    }

    case '2':
    {
      GPIOA->ODR |= (0x3 << 9);
      GPIOB->ODR |= (0xB << 12);
      break;
    }
    case '3':
    {
      GPIOA->ODR |= (0x1 << 9);
      GPIOB->ODR |= (0xF << 12);
      break;
    }

    case '4':
    {
      GPIOA->ODR |= (0x3 << 8);
      GPIOB->ODR |= (0x3 << 13);
      break;
    }
    case '5':
    {
      GPIOA->ODR |= (0x3 << 8);
      GPIOB->ODR |= (0xD << 12);
      break;
    }
    case '6':
    {
      GPIOA->ODR |= (0xF << 8);
      GPIOB->ODR |= (0xD << 12);
      break;
    }

    case '7':
    {
      GPIOB->ODR |= (0x7 << 12);
      break;
    }
    case '8':
    {
      GPIOA->ODR |= (0x7 << 8);
      GPIOB->ODR |= (0xF << 12);
      break;
    }

    case '9':
    {
      GPIOA->ODR |= (0x3 << 8);
      GPIOB->ODR |= (0xF << 12);
      break;
    }
    case 'a':
    {
      GPIOA->ODR |= (0x3 << 9);
      GPIOB->ODR |= (0xF << 12);
      break;
    }
    case 'b':
    {
      GPIOA->ODR |= (0x7 << 8);
      GPIOB->ODR |= (0x3 << 14);
      break;
    }
    case 'c':
    {
      GPIOA->ODR |= (0x3 << 9);
      GPIOB->ODR |= (0x1 << 15);
      break;
    }
    case 'd':
    {
      GPIOA->ODR |= (0x3 << 9);
      GPIOB->ODR |= (0x7 << 13);
      break;
    }
    case 'e':
    {
      GPIOA->ODR |= (0x7 << 8);
      GPIOB->ODR |= (0x9 << 12);
      break;
    }
    case 'f':
    {
      GPIOA->ODR |= (0x7 << 8);
      GPIOB->ODR |= (0x1 << 12);
      break;
    }
    case 'g':
    {
      GPIOA->ODR |= (0x3 << 8);
      GPIOB->ODR |= (0x7 << 12);
      break;
    }
    case 'h':
    {
      GPIOA->ODR |= (0x7 << 8);
      GPIOB->ODR |= (0x3 << 13);
      break;
    }

    case 'L':
    {
      GPIOA->ODR |= (0x5 << 8);
      GPIOB->ODR |= (0x1 << 15);
      break;
    }

    case 'p':
    case 'P':
    {
      GPIOA->ODR |= (0x7 << 8);
      GPIOB->ODR |= (0x3 << 12);
      break;
    }

    case 'r':
    {
      GPIOA->ODR |= (0x3 << 9);
      break;
    }

    case 't':
    {
      GPIOA->ODR |= (0x7 << 8);
      GPIOB->ODR |= (0x9 << 12);
      break;
    }

    case 'u':
    {
      GPIOA->ODR |= (0x1 << 10);
      GPIOB->ODR |= (0x3 << 14);
      break;
    }

    case ' ':
    {
      break;
    }

    case '=':
    {
      GPIOA->ODR |= (0x1 << 9);
      GPIOB->ODR |= (0x1 << 15);
    }

    default:
    {
      // Do nothing
    }
  }
}

/**
 * @brief LED 7 segment shows string by character
 * @note  All character must be a case in led7seg_putc() function
 */
void led7seg_string(char *str)
{
  while (*str)
  {
    led7seg_putc(*str++);
    tim_msDelay(500);
    led7seg_putc(' ');
    tim_msDelay(100);
  }
}

