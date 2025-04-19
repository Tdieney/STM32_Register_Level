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

/**
 * @brief TIM2 miliseconds delay configuration
 */
void tim_TIM2_delayConfig()
{
  // Enable TIM2 timer
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  // Count up mode
  TIM2->CR1 &= ~(TIM_CR1_DIR);
  // One-pulse mode
  TIM2->CR1 |= TIM_CR1_OPM;
  // Mode: RESET
  TIM2->CR2 &= ~(TIM_CR2_MMS);
  // Prescaler
  TIM2->PSC = (uint32_t)0;
  // Period
  TIM2->ARR = (uint32_t)7199;
}

void tim_TIM2_myDelayConfig()
{
  // Enable TIM2 timer
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  // Count up mode
  TIM2->CR1 &= ~(TIM_CR1_DIR);
  // Mode: RESET
  TIM2->CR2 &= ~(TIM_CR2_MMS);
  // Prescaler
  TIM2->PSC = 71U;
  // Period
  TIM2->ARR = 0xFFFFU;
  // Start TIM2
  TIM2->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief TIM2 miliseconds delay function
 */
void tim_TIM2_msDelay(uint32_t miliseconds)
{
  // Set period time
  TIM2->PSC = (uint32_t)(miliseconds * 10);
  // Start TIM2
  TIM2->CR1 |= TIM_CR1_CEN;
  while(!(TIM2->SR & TIM_SR_UIF));
  TIM2->SR &= ~TIM_SR_UIF;
}

void delay_us(uint32_t microSeconds)
{
  // Set period time
  TIM2->CNT = 0;
  while((TIM2->CNT)<microSeconds);
}

void delay_ms(uint32_t miliSeconds)
{
  while(miliSeconds)
  {
    delay_us(1000);
    miliSeconds--;
  }
}
