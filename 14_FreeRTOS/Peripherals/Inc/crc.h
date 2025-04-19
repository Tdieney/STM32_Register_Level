/*
 * crc.h
 *
 *  Created on: Oct 22, 2021
 *      Author: THINH
 */

#ifndef INC_CRC_H_
#define INC_CRC_H_

#include "main.h"

/**
 * @brief CRC enable/disable
 */
void crc_enable();
void crc_disable();

/**
 * @brief CRC reset
 */
void crc_reset();

/**
 * @brief CRC accumulate
 */
void crc_accumulate(uint32_t value);

/**
 * @brief CRC read
 */
uint32_t crc_read(void);

#endif /* INC_CRC_H_ */
