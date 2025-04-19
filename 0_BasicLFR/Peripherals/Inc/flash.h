/*
 * flash.h
 *
 *  Created on: Oct 25, 2021
 *      Author: THINH
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "main.h"

/**
 * @brief Unlock
 */
void flash_unlock();

/**
 * @brief Lock
 */
void flash_lock();

/**
 * @brief Erase
 */
void flash_erase(uint32_t pgAddr);

/**
 * @brief Write-16bits
 */
void flash_write16(uint32_t addr, uint16_t *pBuf, uint32_t len);

/**
 * @brief Read-16bits
 */
void flash_read16(uint32_t addr, uint16_t *pBuf, uint32_t len);

#endif /* INC_FLASH_H_ */
