/*
 * pwr.c
 *
 *  Created on: Oct 25, 2021
 *      Author: THINH
 */

#include "pwr.h"

/**
 * @brief Enter sleep mode (sleep-now)
 */
void pwr_enterSleep()
{
  // Disable SysTick interrupt (avoid waking up the MCU)
  SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk);
//  // Clear SLEEPONEXIT
//  SCB->SCR &= ~(SCB_SCR_SLEEPONEXIT_Msk);
  // Set SLEEPONEXIT
  SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
  // Clear SLEEPDEEP (SLEEPDEEP = Stop mode)
  SCB->SCR &= ~(SCB_SCR_SLEEPDEEP_Msk);
  // Put the device into sleep -> code execution is paused here
  __WFI();
  // On wakeup -> resume
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}

/**
 * @brief Enter stop mode
 */
void pwr_enterStop()
{
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  // Disable SysTick interrupt (avoid waking up the MCU)
  SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk);
  // Clear SLEEPONEXIT
  SCB->SCR &= ~(SCB_SCR_SLEEPONEXIT_Msk);
  // Set SLEEPDEEP
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  // Clear PDDS
  PWR->CR &= ~(PWR_CR_PDDS);
  // Configure LPDS bit
  PWR->CR |= PWR_CR_LPDS;
  // Clear flag and pending bits
  EXTI->PR |= 0xFFFFFUL;
  // Put the device into stop mode -> code execution is paused here
  __WFI();
  // On wakeup -> resume
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}
