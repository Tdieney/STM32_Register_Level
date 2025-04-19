/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "rcc.h"

/**
 * @brief RCC configuration
 */
void rcc_config()
{
  /* PLL Configuration */
  // Set bitfields [21:18] -> PLL_M = 16
  RCC->CFGR |= RCC_CFGR_PLLMULL;
  // USB Divider
  RCC->CFGR &= ~(RCC_CFGR_USBPRE);

  /* HSI Oscillator */
  // Enable HSI Oscillator
  RCC->CR |= RCC_CR_HSION;
  // Wait for it to stabilize
  while((RCC->CR & RCC_CR_HSIRDY) == 0);
  // Select HSI as PLL source
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC);
  // Enable PLL
  RCC->CR |= RCC_CR_PLLON;
  // Wait for PLL ready
  while((RCC->CR & RCC_CR_PLLRDY) == 0);

  // Flash prefetch and wait state
  // Clear latency fields
  FLASH->ACR &= ~(FLASH_ACR_LATENCY);
  // 2 wait state for 64MHz
  FLASH->ACR |= FLASH_ACR_LATENCY_1;
  // Enable prefetch buffer
  FLASH->ACR |= FLASH_ACR_PRFTBE;

  // Select system clock
  // Clear SW bits
  RCC->CFGR &= ~(RCC_CFGR_SW);
  // PLL selected as system clock
  RCC->CFGR |= RCC_CFGR_SW_1;
  // Wait for PLL to be the active clock source
  while((RCC->CFGR & RCC_CFGR_SWS_1) == 0);

  // Peripherals clock setup
  // AHB Prescaler
  RCC->CFGR &= ~(RCC_CFGR_HPRE);
  // APB1 Prescaler
  RCC->CFGR &= ~(RCC_CFGR_PPRE1);
  RCC->CFGR |= RCC_CFGR_PPRE1_2;
  // APB2 Prescaler
  RCC->CFGR &= ~(RCC_CFGR_PPRE2);
  // ADC Prescaler
  RCC->CFGR &= ~(RCC_CFGR_ADCPRE);
  RCC->CFGR |= RCC_CFGR_ADCPRE_1;
}

/**
 * @brief SysTick configuration
 */
void systick_config()
{
  // Reset CTRL register
  SysTick->CTRL = 0;
  // Set the Reload value
  SysTick->LOAD = 63999;
  // It has always enabled
  // Set priority to SysTick Interrupt (NVIC)
  NVIC_SetPriority(SysTick_IRQn, 0);
  // Reset SysTick value to 0
  SysTick->VAL = 0;
  // Enable SysTick from CTRL register
  SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}
