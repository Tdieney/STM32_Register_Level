/*
 * tim.c
 *
 *  Created on: Aug 25, 2021
 *      Author: THINH
 */

#include "tim.h"

static __IO uint32_t msTick = 0;

/**
 * @brief TIM3 - Time Base ticks/delay
 */
void tim_TIM3_initTicks(void)
{
  // Enable TIM3
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  // Count up mode
  TIM3->CR1 &= ~(TIM_CR1_DIR);
  // Periodic
  TIM3->CR1 &= ~(TIM_CR1_OPM);
  // Mode: RESET
  TIM3->CR2 &= ~(TIM_CR2_MMS);
  // Prescaler
  TIM3->PSC = 64 - 1;
  // Period
  TIM3->ARR = 1000 - 1; // 1KHz

  // Clear update interrupt
  TIM3->SR &= ~(TIM_SR_UIF);
  // Enable update interrupt
  TIM3->DIER |= TIM_DIER_UIE;
  // Enable NVIC
  NVIC_SetPriority(TIM3_IRQn, 5);
  NVIC_EnableIRQ(TIM3_IRQn);
  // Start TIM3
  TIM3->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief Increment milliseconds
 */
void tim_msIncTick()
{
  msTick++;
}

/**
 * @brief Get milliseconds
 */
uint32_t tim_msGetTick()
{
  return msTick;
}

/**
 * @brief Milliseconds delay function
 */
void tim_msDelay(uint32_t milliseconds)
{
  uint32_t startTick = tim_msGetTick();
  while(tim_msGetTick() - startTick < milliseconds);
}

/**
 * @brief TIM2 & TIM4 PWM configuration
 */
void tim_PWM_config()
{
  // Enable TIM2 and TIM4
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM4EN;
  // Count up mode
  TIM2->CR1 &= ~(TIM_CR1_DIR);
  TIM4->CR1 &= ~(TIM_CR1_DIR);
  // Periodic
  TIM2->CR1 &= ~(TIM_CR1_OPM);
  TIM4->CR1 &= ~(TIM_CR1_OPM);
  // Mode: RESET
  TIM2->CR2 &= ~(TIM_CR2_MMS);
  TIM4->CR2 &= ~(TIM_CR2_MMS);
  // Prescaler
  TIM2->PSC = 0U;
  TIM4->PSC = 0U;
  // Period
  TIM2->ARR = 6399U; // 10KHz
  TIM4->ARR = 6399U; //
  // Clear update interrupt
  TIM2->SR &= ~(TIM_SR_UIF);
  TIM4->SR &= ~(TIM_SR_UIF);

  /* PWM: TIM2_CH1, TIM2_CH2, TIM4_CH1, TIM4_CH2 */
  // Disable OC
  TIM2->CCER = 0;
  TIM4->CCER = 0;
  // Set mode to output
  TIM2->CCMR1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_CC2S);
  TIM4->CCMR1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_CC2S);
  // PWM mode 1
  TIM2->CCMR1 &= ~(TIM_CCMR1_OC1M | TIM_CCMR1_OC2M);
  TIM4->CCMR1 &= ~(TIM_CCMR1_OC1M | TIM_CCMR1_OC2M);
  TIM2->CCMR1 |= (0x6UL << 4U) | (0x6UL << 12U);
  TIM4->CCMR1 |= (0x6UL << 4U) | (0x6UL << 12U);
  // Polarity
  TIM2->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);
  TIM4->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);
  // Set pulse width - duty cycles
  TIM2->CCR1 = 0;
  TIM2->CCR2 = 0;
  TIM4->CCR1 = 0;
  TIM4->CCR2 = 0;
  // Enable channels
  TIM2->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;
  TIM4->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;
  // Start TIM2 and TIM4
  TIM2->CR1 |= TIM_CR1_CEN;
  TIM4->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief TIM Configuration
 */
void tim_config()
{
  tim_TIM3_initTicks();
  tim_PWM_config();
}

void TIM3_IRQHandler()
{
  if(TIM3->SR & TIM_SR_UIF)
  {
    // Clear flag
    TIM3->SR &= ~TIM_SR_UIF;
    NVIC_ClearPendingIRQ(TIM3_IRQn);
    // Increase tick
    msTick++;
  }
}
