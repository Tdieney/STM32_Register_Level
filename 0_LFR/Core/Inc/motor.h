/*
 * motor.h
 *
 *  Created on: Dec 18, 2021
 *      Author: THINH
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"

/**
 * @brief Control left motor
 * @note  Limit speed value 0->6399
 *        dir = 1: run forward
 *        dir = 0: run backward
 */
void setLeftMotor(uint16_t speed, uint8_t dir);

/**
 * @brief Control right motor
 * @note  Limit speed value 0->6399
 *        dir = 1: run forward
 *        dir = 0: run backward
 */
void setRightMotor(uint16_t speed, uint8_t dir);

/**
 * @brief Stop left motor
 */
void stopLeftMotor();

/**
 * @brief Stop right motor
 */
void stopRightMotor();

#endif /* INC_MOTOR_H_ */
