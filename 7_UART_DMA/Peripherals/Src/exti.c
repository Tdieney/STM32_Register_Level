/*
 * exti.c
 *
 *  Created on: Aug 23, 2021
 *      Author: THINH
 */

#include "exti.h"

/**
 * @brief Push button EXTI configuration
 */
void exti_PB_config()
{
  // Enable AFIO clock
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  // PA0 maps to EXTI0
  AFIO->EXTICR[0] &= ~(AFIO_EXTICR1_EXTI0);
  // Unblock EXTI0 interrupt
  EXTI->IMR |= EXTI_IMR_IM0;
  // Enable falling edge only
  EXTI->RTSR &= ~(EXTI_RTSR_RT0);
  EXTI->FTSR |= EXTI_FTSR_FT0;

  NVIC_SetPriority(EXTI0_IRQn, 5);
  NVIC_EnableIRQ(EXTI0_IRQn);
}
