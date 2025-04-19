/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "rcc.h"

static __IO uint32_t msTick = 0;

/**
 * @brief HSE configuration
 */
void rcc_HSE_config()
{
  /**
   * Configure parameters --> STM32 Clock Tree
   *
   * HSE = 8MHz
   * PLL_M = 9
   * USB Divider = 1.5                ??????????????????
   * AHB Prescaler = 1
   * Cortex Prescaler = 1
   * --> 72MHz system clock
   *
   * APB1 Prescaler = 2 --> 36, 72MHz
   * APB2 Prescaler = 1 --> 72MHz
   * ADC Prescaler = 6 --> 12MHz
   */

  /* PLL Configuration */
  // Clear bitfields [21:18]
  //RCC->CFGR &= ~(0xFUL << 18U);     // same effects
  RCC->CFGR &= ~(RCC_CFGR_PLLMULL);   //
  // PLL_M = 9
  RCC->CFGR |= (7UL << 18U);
  // USB Divider
  //RCC->CFGR &= ~(1UL << 22U);       // same effects
  RCC->CFGR &= ~(RCC_CFGR_USBPRE);    //

  /* HSE Oscillator */
  // Enable HSE Oscillator
  RCC->CR |= RCC_CR_HSEON;
  // Wait for it to stabilize
  while((RCC->CR & RCC_CR_HSERDY) == 0);
  // Select HSE as PLL source
  RCC->CFGR |= RCC_CFGR_PLLSRC;
  // Enable PLL
  RCC->CR |= RCC_CR_PLLON;
  // Wait for PLL ready
  while((RCC->CR & RCC_CR_PLLRDY) == 0);

  // Flash prefetch and wait state
  // Clear latency fields
  FLASH->ACR &= ~(FLASH_ACR_LATENCY);
  // 2 wait state for 72MHz
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
 * @brief Systick configuration
 */
void rcc_SysTick_config()
{
  // Reset CTRL register
  SysTick->CTRL = 0;
  // Set the Reload value
  SysTick->LOAD = 71999;
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

/**
 * @brief Increment milliseconds
 */
void rcc_msIncTick()
{
  msTick++;
}

/**
 * @brief Get milliseconds
 */
uint32_t rcc_msGetTick()
{
  return msTick;
}

/**
 * @brief Milliseconds delay function
 */
void rcc_msDelay(uint32_t milliseconds)
{
  uint32_t startTick = rcc_msGetTick();
  while(rcc_msGetTick() - startTick < milliseconds);
}

void SysTick_Handler()
{
  NVIC_ClearPendingIRQ(SysTick_IRQn);
  rcc_msIncTick();
}
