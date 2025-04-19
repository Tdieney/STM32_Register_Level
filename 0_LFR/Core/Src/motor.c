/*
 * motor.c
 *
 *  Created on: Dec 18, 2021
 *      Author: THINH
 */

#include "motor.h"

/**
 * @brief Control left motor
 * @note  Limit speed value 0->6399
 *        dir = 1: run forward
 *        dir = 0: run backward
 */
void setLeftMotor(uint16_t speed, uint8_t dir)
{
  if(speed < 0)
  {
    speed = 0;
  }
  else if(speed > 6399)
  {
    speed = 6399;
  }
  if(dir == 1)
  {
    TIM2->CCR1 = speed;
    TIM2->CCR2 = 0;
  }
  else if(dir == 0)
  {
    TIM2->CCR1 = 0;
    TIM2->CCR2 = speed;
  }
}

/**
 * @brief Control right motor
 * @note  Limit speed value 0->6399
 *        dir = 1: run forward
 *        dir = 0: run backward
 */
void setRightMotor(uint16_t speed, uint8_t dir)
{
  if(speed < 0)
  {
    speed = 0;
  }
  else if(speed > 6399)
  {
    speed = 6399;
  }
  if(dir == 1)
  {
    TIM4->CCR1 = speed;
    TIM4->CCR2 = 0;
  }
  else if(dir == 0)
  {
    TIM4->CCR1 = 0;
    TIM4->CCR2 = speed;
  }
}

/**
 * @brief Stop left motor
 */
void stopLeftMotor()
{
  TIM2->CCR1 = 0;
  TIM2->CCR2 = 0;
}

/**
 * @brief Stop right motor
 */
void stopRightMotor()
{
  TIM4->CCR1 = 0;
  TIM4->CCR2 = 0;
}
