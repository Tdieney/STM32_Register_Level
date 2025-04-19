/*
 * gpio.c
 *
 *  Created on: Aug 22, 2021
 *      Author: THINH
 */

#include "gpio.h"

/**
 * @brief LED GPIO configuration (PC13)
 */
void gpio_LED_config()
{
  // Enable clock for portC in APB2
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
  // 50MHz output mode
  GPIOC->CRH |= (GPIO_CRH_MODE13);
  // Output push-pull
  GPIOC->CRH &= ~(GPIO_CRH_CNF13);
}

/**
 * @brief Write/Toggle LED functions
 */
void gpio_LED_write(bool state)
{
  // LED on
  if(state)
  {
    GPIOC->ODR |= GPIO_ODR_ODR13;
  }
  // LED off
  else
  {
    GPIOC->ODR &= ~(GPIO_ODR_ODR13);
  }
}

void gpio_LED_toggle()
{
  GPIOC->ODR ^= GPIO_ODR_ODR13;
}

/**
 * @brief Button configuration (PA0)
 */
void gpio_PB_config()
{
  // Enable clock for portA in APB2
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  // Input mode
  GPIOA->CRL &= ~(GPIO_CRL_MODE0);
  // Input - floating
  GPIOA->CRL &= ~(GPIO_CRL_CNF0);
  GPIOA->CRL |= GPIO_CRL_CNF0_0;
}

/**
 * @brief Read push-button function
 */
bool gpio_PB_read()
{
  return (bool)(GPIOA->IDR & GPIO_IDR_IDR0);
}

/**
 * @brief Slide switchs configuration (PA8, PA15)
 */
void gpio_SW_config()
{
  // Enable clock for portA in APB2
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  // Remap
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  AFIO->MAPR &= ~(AFIO_MAPR_SWJ_CFG);
  AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_1;
  // Input mode
  GPIOA->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_MODE15);
  // Input - floating mode
  GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_CNF15);
  GPIOA->CRH |= (GPIO_CRH_CNF8_0 | GPIO_CRH_CNF15_0);
}

/**
 * @brief Read Slide switchs function (PA8, PA15)
 */
bool gpio_SW1_read()
{
  return (bool)(GPIOA->IDR & GPIO_IDR_IDR8);
}

bool gpio_SW2_read()
{
  return (bool)(GPIOA->IDR & GPIO_IDR_IDR15);
}
