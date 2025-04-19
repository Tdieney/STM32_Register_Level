/*
 * spi.h
 *
 *  Created on: Oct 14, 2021
 *      Author: THINH
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "main.h"

/**
 * @brief SPI GPIO pins setup
 */
void spi_GPIO_config();

/**
 * @brief SPI peripherals configuration
 */
void spi_config();

/**
 * @brief SPI transmit
 */
bool spi_transmit(uint8_t *pData, uint8_t len, uint32_t timeout);

/**
 * @brief SPI receive
 */
bool spi_receive(uint8_t *pData, uint8_t len, uint32_t timeout);

/**
 * @brief SPI CS pin configuration
 */
void spi_RFID_CS_config();

/**
 * @brief Write CS
 */
void spi_RFID_CS_write(bool state);

#endif /* INC_SPI_H_ */
