/*
 * spi.c
 *
 *  Created on: Oct 14, 2021
 *      Author: THINH
 */

#include "spi.h"

/**
 * @brief SPI GPIO pins setup
 */
void spi_GPIO_config()
{
  // Enable portA clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  // PA5(SCK) and PA7(MOSI) as output
  // Mode output - speed 10MHz
  GPIOA->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_MODE7);
  GPIOA->CRL |= (GPIO_CRL_MODE5_0 | GPIO_CRL_MODE7_0);
  // Alternative function push-pull
  GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_CNF7);
  GPIOA->CRL |= (GPIO_CRL_CNF5_1 | GPIO_CRL_CNF7_1);
  // PA6(MISO) as input
  // Input mode
  GPIOA->CRL &= ~(GPIO_CRL_MODE6);
  // Floating input
  GPIOA->CRL &= ~(GPIO_CRL_CNF6);
  GPIOA->CRL |= GPIO_CRL_CNF6_0;
//  // PB0 as fake 3.3v for RST pin
//  // Mode output - speed 10MHz
//  GPIOB->CRL &= ~(GPIO_CRL_MODE0);
//  GPIOB->CRL |= (GPIO_CRL_MODE0_0);
//  // General purpose push-pull
//  GPIOB->CRL &= ~(GPIO_CRL_CNF0);
}

/**
 * @brief SPI peripherals configuration
 */
void spi_config()
{
  // Enable SPI clock
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
  // Clock phase
  SPI1->CR1 |= SPI_CR1_CPHA;
  // Clock polarity
  SPI1->CR1 |= SPI_CR1_CPOL;
  // Mode master/slave
  SPI1->CR1 |= SPI_CR1_MSTR;
  // Baud rate
  SPI1->CR1 &= ~(SPI_CR1_BR);
  SPI1->CR1 |= (SPI_CR1_BR_2 | SPI_CR1_BR_1);
  // MSB first
  SPI1->CR1 &= ~(SPI_CR1_LSBFIRST);
  // Duplex
  SPI1->CR1 &= ~(SPI_CR1_RXONLY);
  // Data format 8/16
  SPI1->CR1 &= ~(SPI_CR1_DFF);
  // Slave select
  SPI1->CR1 |= (SPI_CR1_SSI | SPI_CR1_SSM);
  // Enable SPI
  SPI1->CR1 |= SPI_CR1_SPE;
  // Clear flags
  __IO uint32_t tempRd = SPI1->SR;
  (void)tempRd;
}

/**
 * @brief SPI transmit
 */
bool spi_transmit(uint8_t *pData, uint8_t len, uint32_t timeout)
{
  // Enable SPI if not
  SPI1->CR1 |= SPI_CR1_SPE;
  // Timeout initial ticks
  uint8_t dataIdx = 0;
  uint32_t startTick = rcc_msGetTick();
  // While loop, transmitting data, managing timeout
  while(dataIdx < len)
  {
    if(SPI1->SR & SPI_SR_TXE) //Tx buffer empty
    {
      SPI1->DR = pData[dataIdx];
      dataIdx++;
    }
    else if(rcc_msGetTick() - startTick >= timeout) // Manage timeout
    {
      return false;
    }
  }
  // Wait for busy flag
  while(SPI1->SR & SPI_SR_BSY)
  {
    if(rcc_msGetTick() - startTick >= timeout)
    {
      return false;
    }
  }
  // Clear overrun --> DR, SR
  __IO uint32_t tempRead = SPI1->DR;
  tempRead = SPI1->SR;
  (void)tempRead;
  return true;
}

/**
 * @brief SPI receive
 */
bool spi_receive(uint8_t *pData, uint8_t len, uint32_t timeout)
{
  // Enable SPI if not
  SPI1->CR1 |= SPI_CR1_SPE;
  // Timeout initial ticks
  uint8_t dataIdx = 0;
  uint32_t startTick = rcc_msGetTick();
  bool isTransmit = true;
  // While loop, transmitting data, managing timeout
  while(dataIdx < len)
  {
    // Transmit dummy data
    if((SPI1->SR & SPI_SR_TXE) && isTransmit)
    {
      SPI1->DR = 0xFF;
      isTransmit = false;
    }
    if(SPI1->SR & SPI_SR_RXNE)
    {
      pData[dataIdx] = SPI1->DR;
      dataIdx++;
      isTransmit = true;
    }
    else if(rcc_msGetTick() - startTick >= timeout) // Manage timeout
    {
      return false;
    }
  }
  // Wait for busy flag
  while(SPI1->SR & SPI_SR_BSY)
  {
    if(rcc_msGetTick() - startTick >= timeout)
    {
      return false;
    }
  }
  // Clear overrun --> DR, SR
  __IO uint32_t tempRead = SPI1->DR;
  tempRead = SPI1->SR;
  (void)tempRead;
  return true;
}

/**
 * @brief SPI CS pin configuration
 */
void spi_RFID_CS_config()
{
  // PA4
  // Enable portA clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  // Mode output - speed 2MHz
  GPIOA->CRL &= ~(GPIO_CRL_MODE4);
  GPIOA->CRL |= (GPIO_CRL_MODE4_1);
  // General purpose push-pull
  GPIOA->CRL &= ~(GPIO_CRL_CNF4);
  // Default value high
  GPIOA->BSRR |= GPIO_BSRR_BS4;
}

/**
 * @brief Write CS
 */
void spi_RFID_CS_write(bool state)
{
  if(state)
  {
    GPIOA->BSRR |= GPIO_BSRR_BS4;
  }
  else
  {
    GPIOA->BSRR |= GPIO_BSRR_BR4;
  }
}
