/*
 * i2c.c
 *
 *  Created on: Oct 16, 2021
 *      Author: THINH
 */

#include "i2c.h"

/**
 * @brief I2C GPIO pins configuration
 */
void i2c_I2C1_GPIO_config()
{
  // PB8(SCL), PB9(SDA)
  // Enable portB clock and AFIO for remapping
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
  // Remap
  AFIO->MAPR |= AFIO_MAPR_I2C1_REMAP;
  // Mode output - speed 10MHz
  GPIOB->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_MODE9);
  GPIOB->CRH |= (GPIO_CRH_MODE8_0 | GPIO_CRH_MODE9_0);
  // Alternative function open drain
  GPIOB->CRH |= (GPIO_CRH_CNF8 | GPIO_CRH_CNF9);

}

/**
 * @brief I2C peripherals configuration
 */
void i2c_I2C1_config()
{
  // Enable I2C1 clock
  RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
  // Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
  I2C1->CR2 &= ~(I2C_CR2_FREQ);
  I2C1->CR2 |= (36U << 0U);
  // Configure the clock control registers for 100kHz speed
  I2C1->CCR = 180U;
  // Configure the rise time register
  I2C1->TRISE = 36 + 1;
  // Program the I2C_CR1 register to enable the peripheral
  I2C1->CR1 |= I2C_CR1_PE;
}

/**
 * @brief I2C check slave address
 */
bool i2c_I2C1_isSlaveAddressExist(uint8_t addrs, uint32_t timeout)
{
  uint32_t startTick = rcc_msGetTick();
  // Send start condition
  I2C1->CR1 &= ~(I2C_CR1_POS);
  I2C1->CR1 |= I2C_CR1_START;
  // Clear SB bit
  while(!(I2C1->SR1 & I2C_SR1_SB))
  {
    if(rcc_msGetTick() - startTick >= timeout)
    {
      return false;
    }
  }
  // Send slave address
  I2C1->DR = addrs;
  // Wait for ACK
  while(!(I2C1->SR1 & I2C_SR1_ADDR))
  {
    if(rcc_msGetTick() - startTick >= timeout)
    {
      return false;
    }
  }
  // Clear ADDR bit
  __IO uint32_t tempRd = I2C1->SR1;
  tempRd = I2C1->SR2;
  (void)tempRd;
  // Generate stop condition
  I2C1->CR1 |= I2C_CR1_STOP;
  // Wait for busy
  while(I2C1->SR2 & I2C_SR2_BUSY)
  {
    if(rcc_msGetTick() - startTick >= timeout)
    {
      return false;
    }
  }
  return true;
}

/**
 * @brief I2C master transmit
 */
bool i2c_I2C1_masterTransmit(uint8_t addrs, uint8_t *pData, uint8_t len, uint32_t timeout)
{
  uint32_t startTick = rcc_msGetTick();
  // Wait for busy
  while(I2C1->SR2 & I2C_SR2_BUSY)
  {
    if(rcc_msGetTick() - startTick >= timeout)
    {
      return false;
    }
  }
  // Send start condition
  I2C1->CR1 &= ~(I2C_CR1_POS);
  I2C1->CR1 |= I2C_CR1_START;
  // Clear SB bit
  while(!(I2C1->SR1 & I2C_SR1_SB))
  {
    if(rcc_msGetTick() - startTick >= timeout)
    {
      return false;
    }
  }
  // Send slave address
  I2C1->DR = addrs;
  // Wait for ACK
  while(!(I2C1->SR1 & I2C_SR1_ADDR))
  {
    if(rcc_msGetTick() - startTick >= timeout)
    {
      return false;
    }
  }
  // Clear ADDR bit
  __IO uint32_t tempRd = I2C1->SR1;
  tempRd = I2C1->SR2;
  (void)tempRd;
  // Send data
  uint8_t dataIdx = 0;
  int8_t dataSize = len;
  while(dataSize > 0)
  {
    // Check for TX buffer empty --> send byte
    while(!(I2C1->SR1 & I2C_SR1_TXE))
    {
      if(rcc_msGetTick() - startTick >= timeout)
      {
        return false;
      }
    }
    I2C1->DR = pData[dataIdx];
    dataIdx++;
    dataSize--;
    // Wait for BTF flag
    while(!(I2C1->SR1 & I2C_SR1_BTF))
    {
      if(rcc_msGetTick() - startTick >= timeout)
      {
        return false;
      }
    }
  }
  // Generate stop condition
  I2C1->CR1 |= I2C_CR1_STOP;
  return true;
}

/**
 * @brief I2C master receive
 */
bool i2c_I2C1_masterReceive(uint8_t addrs, uint8_t *pData, uint8_t len, uint32_t timeout)
{
  uint32_t startTick = rcc_msGetTick();
  // Wait for busy
  while(I2C1->SR2 & I2C_SR2_BUSY)
  {
    if(rcc_msGetTick() - startTick >= timeout)
    {
      return false;
    }
  }
  // Send start condition
  I2C1->CR1 &= ~(I2C_CR1_POS);
  I2C1->CR1 |= I2C_CR1_ACK;
  I2C1->CR1 |= I2C_CR1_START;
  // Clear SB bit
  while(!(I2C1->SR1 & I2C_SR1_SB))
  {
    if(rcc_msGetTick() - startTick >= timeout)
    {
      return false;
    }
  }
  // Send slave address
  I2C1->DR = addrs | 0x01;
  // Wait for ACK
  while(!(I2C1->SR1 & I2C_SR1_ADDR))
  {
    if(rcc_msGetTick() - startTick >= timeout)
    {
      return false;
    }
  }
  // Data reception scheme
  if(len == 0)
  {
    // Clear ADDR bit
    __IO uint32_t tempRd = I2C1->SR1;
    tempRd = I2C1->SR2;
    (void)tempRd;
    // Generate stop condition
    I2C1->CR1 |= I2C_CR1_STOP;
    return false;
  }
  else if(len == 1)
  {
    // In the ADDR event, clear the ACK bit
    I2C1->CR1 &= ~(I2C_CR1_ACK);
    // Clear ADDR
    __IO uint32_t tempRd = I2C1->SR1;
    tempRd = I2C1->SR2;
    (void)tempRd;
    // Program the STOP/START bit
    I2C1->CR1 |= I2C_CR1_STOP;
  }
  else if(len == 2)
  {
    // Set POS
    I2C1->CR1 |= I2C_CR1_POS;
    // Clear ADDR
    __IO uint32_t tempRd = I2C1->SR1;
    tempRd = I2C1->SR2;
    (void)tempRd;
    // Clear ACK
    I2C1->CR1 &= ~(I2C_CR1_ACK);
  }
  else
  {
    // Clear ADDR
    __IO uint32_t tempRd = I2C1->SR1;
    tempRd = I2C1->SR2;
    (void)tempRd;
  }
  // Receive data
  uint8_t dataIdx = 0;
  int8_t dataSize = len;
  while(dataSize > 0)
  {
    if(dataSize <= 3)
    {
      // Read the data after the RxNE flag is set
      if(dataSize == 1)
      {
        while(!(I2C1->SR1 & I2C_SR1_RXNE))
        {
          if(rcc_msGetTick() - startTick >= timeout)
          {
            return false;
          }
        }
        pData[dataIdx] = (uint8_t)I2C1->DR;
        dataIdx++;
        dataSize--;
      }
      else if(dataSize == 2)
      {
        // Wait for BTF to be set
          while(!(I2C1->SR1 & I2C_SR1_BTF))
          {
            if(rcc_msGetTick() - startTick >= timeout)
            {
              return false;
            }
          }
          // Program STOP
          I2C1->CR1 |= I2C_CR1_STOP;
          // Read DR twice
          pData[dataIdx] = (uint8_t)I2C1->DR;
          dataIdx++;
          dataSize--;
          pData[dataIdx] = (uint8_t)I2C1->DR;
          dataIdx++;
          dataSize--;
      }
      else
      {
        // RxNE = 1 => Nothing (DataN-2 not read).
        // DataN-1 received
        // BTF = 1 because both shift and data registers are full: DataN-2 in DR and DataN-1 in the shift register => SCL tied low: no other data will be received on the bus.
        while(!(I2C1->SR1 & I2C_SR1_BTF))
        {
          if(rcc_msGetTick() - startTick >= timeout)
          {
            return false;
          }
        }
        // Clear ACK bit
        I2C1->CR1 &= ~(I2C_CR1_ACK);
        // Read DataN-2 in DR => This will launch the DataN reception in the shift register
        pData[dataIdx] = (uint8_t)I2C1->DR;
        dataIdx++;
        dataSize--;
        while(!(I2C1->SR1 & I2C_SR1_BTF))
        {
          if(rcc_msGetTick() - startTick >= timeout)
          {
            return false;
          }
        }
        // DataN received (with a NACK)
        // Program START/STOP
        I2C1->CR1 |= I2C_CR1_STOP;
        // Read DataN-1
        pData[dataIdx] = (uint8_t)I2C1->DR;
        dataIdx++;
        dataSize--;
        // RxNE = 1
        // Read DataN
        pData[dataIdx] = (uint8_t)I2C1->DR;
        dataIdx++;
        dataSize--;
      }
    }
    else // Size > 3
    {
      // Wait for RXNE
      while(!(I2C1->SR1 & I2C_SR1_RXNE))
      {
        if(rcc_msGetTick() - startTick >= timeout)
        {
          return false;
        }
      }
      pData[dataIdx] = (uint8_t)I2C1->DR;
      dataIdx++;
      dataSize--;
      // Wait for BTF flag
      while(!(I2C1->SR1 & I2C_SR1_BTF))
      {
        if(rcc_msGetTick() - startTick >= timeout)
        {
          return false;
        }
      }
    }
  }
  return true;
}
