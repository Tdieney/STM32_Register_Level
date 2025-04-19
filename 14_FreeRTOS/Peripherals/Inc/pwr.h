/*
 * pwr.h
 *
 *  Created on: Oct 25, 2021
 *      Author: THINH
 */

#ifndef INC_PWR_H_
#define INC_PWR_H_

#include "main.h"

/**
 * @brief Enter sleep mode (sleep-now)
 */
void pwr_enterSleep();

/**
 * @brief Enter stop mode
 */
void pwr_enterStop();

/**
 * @brief Enter standby mode
 */
void pwr_enterStandby();

#endif /* INC_PWR_H_ */
