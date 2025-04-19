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
  // Put the device into sleep
  __WFI();
  // On wakeup -> resume
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}
