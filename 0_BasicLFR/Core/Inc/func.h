/*
 * func.h
 *
 *  Created on: Dec 18, 2021
 *      Author: THINH
 */

#ifndef INC_FUNC_H_
#define INC_FUNC_H_

#include "main.h"

/**
 * @brief Get ADC value
 */
void readHighValue();
void readLowValue();

/**
 * @brief Calculate line threshold and save to FLASH
 */
void calcThreshold();

/**
 * @brief Get threshold saved in FLASH before
 */
void getThreshold();

/**
 * @brief Process line signal
 * @note  Black line return high analog value
 *        White line return low analog value
 *        Testing on black line
 *
 */
void sigProcessing();


/**
 * @brief Run with PID algorithm
 */
void calcPID(float Kp, float Kd, uint16_t defaultSpeed);

#endif /* INC_FUNC_H_ */
