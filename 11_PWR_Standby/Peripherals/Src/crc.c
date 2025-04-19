/*
 * crc.c
 *
 *  Created on: Oct 22, 2021
 *      Author: THINH
 */

#include "crc.h"

/**
 * @brief CRC enable/disable
 */
void crc_enable()
{
  // Enable CRC clock
  RCC->AHBENR |= RCC_AHBENR_CRCEN;
  // Reset CRC with it's initialize values
  CRC->CR |= CRC_CR_RESET;

}
void crc_disable()
{
  // Disable CRC clock
  RCC->AHBENR &= ~(RCC_AHBENR_CRCEN);
}

/**
 * @brief CRC reset
 */
void crc_reset()
{
  CRC->CR |= CRC_CR_RESET;
}

/**
 * @brief CRC accumulate
 */
void crc_accumulate(uint32_t value)
{
  CRC->DR = value;
}

/**
 * @brief CRC read
 */
uint32_t crc_read(void)
{
  return (CRC->DR); // Calculated CRC from all our accumulated data points
}


