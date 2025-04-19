/*
 * tim.c
 *
 *  Created on: Aug 25, 2021
 *      Author: THINH
 */

#include "tim.h"

/**
 * @brief TIM3 trigger output event configuration
 */
void tim_TIM3_config()
{
  // Enable TIM3 timer
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  // Count up mode
  TIM3->CR1 &= ~(TIM_CR1_DIR);
  // Periodic
  TIM3->CR1 &= ~(TIM_CR1_OPM);
  // Mode: TRGO
  TIM3->CR2 &= ~(TIM_CR2_MMS);
  TIM3->CR2 |= TIM_CR2_MMS_1;
  // APB1 timer clock = 72MHz
  // Prescaler (16-bit)
  TIM3->PSC = 7200 - 1; //10kHz
  // Period (ARR)
  TIM3->ARR = 5000 - 1; //2Hz
  // Update registers on event
  TIM3->EGR |= 1;
  // Start timer
  TIM3->CR1 |= TIM_CR1_CEN;
}
