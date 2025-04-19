/*
 * tim.c
 *
 *  Created on: Aug 25, 2021
 *      Author: THINH
 */

#include "tim.h"
#include "rcc.h"

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
 * @brief TIM2 milliseconds delay configuration
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
  // Start TIM2
  TIM2->CR1 |= TIM_CR1_CEN;
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
 * @brief TIM2 milliseconds delay function
 */
void tim_TIM2_msDelay(uint32_t milliseconds)
{
  // Set period time
  TIM2->PSC = (uint32_t)(milliseconds * 10 - 1);
  // Start TIM2
  TIM2->CR1 |= TIM_CR1_CEN;
  while(!(TIM2->SR & TIM_SR_UIF));
  TIM2->SR &= ~TIM_SR_UIF;
}

void delay_us(uint32_t microSeconds)
{
  // Set period time
  TIM2->CNT = 0;
  while((TIM2->CNT) < microSeconds);
}

void delay_ms(uint32_t milliSeconds)
{
  while(milliSeconds)
  {
    delay_us(1000);
    milliSeconds--;
  }
}

/**
 * @brief Periodic TIM2 interrupt configuration
 */
void tim_TIM2_periodicINTConfig()
{
  // Enable TIM2 timer
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  // Count up mode
  TIM2->CR1 &= ~(TIM_CR1_DIR);
  // Periodic
  TIM2->CR1 &= ~(TIM_CR1_OPM);
  // Mode: RESET
  TIM2->CR2 &= ~(TIM_CR2_MMS);
  // Prescaler
  TIM2->PSC = (uint32_t)(1000 * 10 - 1); // 1000ms
  // Period
  TIM2->ARR = (uint32_t)7199;

  // Clear update interrupt
  TIM2->SR &= ~(TIM_SR_UIF);
  // Enable update interrupt
  TIM2->DIER |= TIM_DIER_UIE;
  // Enable NVIC
  NVIC_SetPriority(TIM2_IRQn, 4);
  NVIC_EnableIRQ(TIM2_IRQn);
  // Start TIM2
  TIM2->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief TIM1_CH1N output compare (OC) configuration
 */
void tim_TIM1_CH1N_OC_config()
{
  // Enable TIM1 clock
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  // Count up mode
  TIM1->CR1 &= ~(TIM_CR1_DIR);
  // Periodic
  TIM1->CR1 &= ~(TIM_CR1_OPM);
  // Mode: RESET
  TIM1->CR2 &= ~(TIM_CR2_MMS);
  // Prescaler
  TIM1->PSC = (uint16_t)(1000 * 10 - 1); // 1000ms
  // Period
  TIM1->ARR = (uint16_t)7199;
  // Clear update interrupt
  TIM1->SR &= ~(TIM_SR_UIF);

  /* Output Compare - TIM1_CH1N */
  // Disable OC
  TIM1->CCER = 0;
  // Set CH1N as output
  TIM1->CCMR1 &= ~(TIM_CCMR1_CC1S);
  // Toggle output periodic
  TIM1->CCMR1 &= ~(TIM_CCMR1_OC1M);
  TIM1->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1;
  // Set output polarity
  TIM1->CCER &= ~(TIM_CCER_CC1NP);
  // Counter value to toggle out
  TIM1->CCR1 = 10;
  // Enable CH1N
  TIM1->CCER |= TIM_CCER_CC1NE;
  // Slave control reset
  TIM1->SMCR = 0;
  // Enable MOE
  TIM1->BDTR |= TIM_BDTR_MOE; // only apply for advanced timer
  // Start TIM1
  TIM1->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief TIM3 PWM configuration
 */
void tim_TIM3_PWM_RGB_config()
{
  // Enable TIM3 clock
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  // Count up mode
  TIM3->CR1 &= ~(TIM_CR1_DIR);
  // Periodic
  TIM3->CR1 &= ~(TIM_CR1_OPM);
  // Mode: RESET
  TIM3->CR2 &= ~(TIM_CR2_MMS);
  // Prescaler
  TIM3->PSC = 0U;
  // Period
  TIM3->ARR = 7199U;
  // Clear update interrupt
  TIM3->SR &= ~(TIM_SR_UIF);

  /* PWM: TIM3 CH1, CH2, CH3 */
  // Disable OC
  TIM3->CCER = 0;
  // Set mode to output
  TIM3->CCMR1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_CC2S);
  TIM3->CCMR2 &= ~(TIM_CCMR2_CC3S);
  // PWM mode 2 because of RGB LED common anode
  TIM3->CCMR1 |= TIM_CCMR1_OC1M | TIM_CCMR1_OC2M;
  TIM3->CCMR2 |= TIM_CCMR2_OC3M;
  // Polarity
  TIM3->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P | TIM_CCER_CC3P);
  // Set pulse width - duty cycles
  TIM3->CCR1 = 0;
  TIM3->CCR2 = 0;
  TIM3->CCR3 = 0;
  // Enable channels
  TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E;
  // Start TIM3
  TIM3->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief Set PWM duty cycles for RGB (0 - 255)
 */
void tim_TIM3_PWM_setRGB(uint8_t R, uint8_t G, uint8_t B)
{
  TIM3->CCR1 = (uint16_t)(7199.0f * R / 255.0f);
  TIM3->CCR2 = (uint16_t)(7199.0f * G / 255.0f);
  TIM3->CCR3 = (uint16_t)(7199.0f * B / 255.0f);
}

/**
 * @brief Encoder TIM4 Peripherals configuration
 */
void tim_TIM4_Encoder_config()
{
  // Enable TIM4 clock
  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
  // Count up mode
  TIM4->CR1 &= ~(TIM_CR1_DIR);
  // Periodic
  TIM4->CR1 &= ~(TIM_CR1_OPM);
  // Mode: RESET
  TIM4->CR2 &= ~(TIM_CR2_MMS);
  // Prescaler
  TIM4->PSC = 0U;
  // Period
  TIM4->ARR = 65535U;
  // Clear update interrupt
  TIM4->SR &= ~(TIM_SR_UIF);

  /* Encoder mode settings */
  // Reset SMCR register bitfields for external clock
  TIM4->SMCR &= ~(TIM_SMCR_ECE | TIM_SMCR_SMS);
  // Set Encoder mode SMCR
  TIM4->SMCR |= TIM_SMCR_SMS_0;
  // Set CC as IC
  TIM4->CCMR1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_CC2S);
  TIM4->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
  // Set CC prescaler = 0
  TIM4->CCMR1 &= ~(TIM_CCMR1_IC1PSC | TIM_CCMR1_IC2PSC);
  // Input filter
  TIM4->CCMR1 &= ~(TIM_CCMR1_IC1F | TIM_CCMR1_IC2F);
  TIM4->CCMR1 |= TIM_CCMR1_IC1F_1 | TIM_CCMR1_IC2F_1;
  // Set polarity to rising
  TIM4->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);
  // Enable Encoder
  TIM4->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;
  // Start TIM4
  TIM4->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief TIM2 - Time Base ticks/delay
 */
void tim_TIM2_initTicks(void)
{
  // Enable TIM2 timer
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  // Count up mode
  TIM2->CR1 &= ~(TIM_CR1_DIR);
  // Periodic
  TIM2->CR1 &= ~(TIM_CR1_OPM);
  // Mode: RESET
  TIM2->CR2 &= ~(TIM_CR2_MMS);
  // Prescaler
  TIM2->PSC = 72 - 1;
  // Period
  TIM2->ARR = 1000 - 1; // 1KHz

  // Clear update interrupt
  TIM2->SR &= ~(TIM_SR_UIF);
  // Enable update interrupt
  TIM2->DIER |= TIM_DIER_UIE;
  // Enable NVIC
  NVIC_SetPriority(TIM2_IRQn, 5);
  NVIC_EnableIRQ(TIM2_IRQn);
  // Start TIM2
  TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_IRQHandler()
{
  if(TIM2->SR & TIM_SR_UIF)
  {
    // Clear flag
    TIM2->SR &= ~TIM_SR_UIF;
    NVIC_ClearPendingIRQ(TIM2_IRQn);
    // Increase tick
    rcc_msIncTick();
  }
}
