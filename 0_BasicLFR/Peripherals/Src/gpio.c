/*
 * gpio.c
 *
 *  Created on: Aug 22, 2021
 *      Author: THINH
 */

#include "gpio.h"

/**
 * @brief GPIO configuration
 */
void gpio_config()
{
  // Enable clocks
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  // Remap
  AFIO->MAPR = 0x07000102UL;


  GPIOA->CRL = 0x00000000;
  GPIOA->CRH = 0xA8822222;
  GPIOB->CRL = 0xAA44A400;
  GPIOB->CRH = 0x222242DD;
  GPIOC->CRH = 0x44244444;
}
