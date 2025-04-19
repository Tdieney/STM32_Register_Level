/*
 * i2c.h
 *
 *  Created on: Oct 16, 2021
 *      Author: THINH
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "main.h"

/**
 * @brief I2C peripherals configuration
 */
void i2c_config();

/**
 * @brief I2C check slave address
 */
bool i2c_I2C1_isSlaveAddressExist(uint8_t addrs, uint32_t timeout);

/**
 * @brief I2C master transmit
 */
bool i2c_I2C1_masterTransmit(uint8_t addrs, uint8_t *pData, uint8_t len, uint32_t timeout);

/**
 * @brief I2C master receive
 */
bool i2c_I2C1_masterReceive(uint8_t addrs, uint8_t *pData, uint8_t len, uint32_t timeout);

#endif /* INC_I2C_H_ */
