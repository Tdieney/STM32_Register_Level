/*
 * exti.c
 *
 *  Created on: Aug 23, 2021
 *      Author: THINH
 */

#include "exti.h"

bool exti2Flag = false;
bool exti11Flag = false;

/**
 * @brief Push button EXTI configuration
 */
void exti_config()
{
  // PB2, PB11 maps to EXTI2, EXTI11
  AFIO->EXTICR[0] &= ~(AFIO_EXTICR1_EXTI2);
  AFIO->EXTICR[0] |=  (AFIO_EXTICR1_EXTI2_PB);
  AFIO->EXTICR[2] &= ~(AFIO_EXTICR3_EXTI11);
  AFIO->EXTICR[2] |=  (AFIO_EXTICR3_EXTI11_PB);
  // Unblock EXTI2, EXTI11 interrupt
  EXTI->IMR |= EXTI_IMR_IM2 | EXTI_IMR_IM11;
  // Enable falling edge only
  EXTI->RTSR &= ~(EXTI_RTSR_RT2 | EXTI_RTSR_RT11);
  EXTI->FTSR |= EXTI_FTSR_FT2 | EXTI_FTSR_FT11;

  NVIC_SetPriority(EXTI2_IRQn, 5);
  NVIC_SetPriority(EXTI15_10_IRQn, 5);
  NVIC_EnableIRQ(EXTI2_IRQn);
  NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI2_IRQHandler()
{
  NVIC_ClearPendingIRQ(EXTI2_IRQn);
  if(EXTI->PR & EXTI_PR_PR2)
  {
    EXTI->PR |= EXTI_PR_PR2;
  }
  // Mask EXTI2 to avoid button debounce
  EXTI->IMR &= ~(EXTI_IMR_IM2);
  // Application
  exti2Flag = true;
}

void EXTI15_10_IRQHandler()
{
  NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
  if(EXTI->PR & EXTI_PR_PR11)
  {
    EXTI->PR |= EXTI_PR_PR11;
  }
  // Mask EXTI11 to avoid button debounce
  EXTI->IMR &= ~(EXTI_IMR_IM11);
  // Application
  exti11Flag = true;
}
