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
  // Input with pull-up/pull-down
  GPIOA->CRL &= ~(GPIO_CRL_CNF0);
  GPIOA->CRL |= GPIO_CRL_CNF0_1;
  // Input pull-up
  GPIOA->ODR |= GPIO_ODR_ODR0;
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

/**
 * @brief TIM1_CH1N GPIO configuration
 */
void gpio_TIM1_CH1N_config()
{
  // Enable clock for portB in APB2
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
  // 50MHz output mode
  GPIOB->CRH |= (GPIO_CRH_MODE13);
  // Alternative push-pull
  GPIOB->CRH &= ~(GPIO_CRH_CNF13);
  GPIOB->CRH |= (GPIO_CRH_CNF13_1);
}

/**
 * @brief RGB LED GPIO configuration (PWM) - TIM3 CH1 (PB4) -> R, CH1 (PB5) -> G, CH3 (PB0) -> B
 */
void gpio_TIM3_PWM_RGB_config()
{
  // Enable clock for portB in APB2
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;  // in order to access alternate function demain
  // Partial remap
  AFIO->MAPR &= ~(AFIO_MAPR_TIM3_REMAP);
  AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_1;
  // 50MHz output mode
  GPIOB->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE4 | GPIO_CRL_MODE5);
  // Alternative push-pull
  GPIOB->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF4 | GPIO_CRL_CNF5);
  GPIOB->CRL |= (GPIO_CRL_CNF0_1 | GPIO_CRL_CNF4_1 | GPIO_CRL_CNF5_1);
}

