/*
 * flash.c
 *
 *  Created on: Oct 25, 2021
 *      Author: THINH
 */

#include "flash.h"

/**
 * @brief Unlock
 */
void flash_unlock()
{
  // Check for the FPEC and FLASH_CR are locked
  if(FLASH->CR & FLASH_CR_LOCK)
  {
    // Do unlock
    FLASH->KEYR = 0x45670123UL;
    FLASH->KEYR = 0xCDEF89ABUL;
  }
}

/**
 * @brief Lock
 */
void flash_lock()
{
  FLASH->CR |= FLASH_CR_LOCK;
}

/**
 * @brief Erase
 */
void flash_erase(uint32_t pgAddr)
{
  // Check that no Flash memory operation is ongoing
  while(FLASH->SR & FLASH_SR_BSY);
  // Set the PER bit
  FLASH->CR |= FLASH_CR_PER;
  // Program the FLASH_AR register to select a page to erase
  FLASH->AR = pgAddr;
  // Set the STRT bit
  FLASH->CR |= FLASH_CR_STRT;
  // Wait for the BSY bit to be reset
  while(FLASH->SR & FLASH_SR_BSY);
  // Clear the PER bit
  FLASH->CR &= ~(FLASH_CR_PER);
}

/**
 * @brief Write-16bits
 */
void flash_write16(uint32_t addr, uint16_t *pBuf, uint32_t len)
{
  // Set the PG bit
  FLASH->CR |= FLASH_CR_PG;
  // Loop
  for(uint32_t i = 0; i < len; i++)
  {
    // Perform the data write (half-word) at the desired address
    *(__IO uint16_t *)addr = pBuf[i];
    addr += 2;
    // Wait for the BSY bit to be reset
    while(FLASH->SR & FLASH_SR_BSY);
  }
  // Clear the PG bit
  FLASH->CR &= ~(FLASH_CR_PG);
}

/**
 * @brief Read-16bits
 */
void flash_read16(uint32_t addr, uint16_t *pBuf, uint32_t len)
{
  // Loop
  for(uint32_t i = 0; i < len; i++)
  {
    pBuf[i] = *(__IO uint16_t *)addr;
    addr += 2;
  }
}

