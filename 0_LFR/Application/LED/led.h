/*
 * led.h
 *
 *  Created on: Dec 18, 2021
 *      Author: THINH
 */

#ifndef LED_LED_H_
#define LED_LED_H_

#include "main.h"


/**
 * @brief Turn ON all LED
 */
void allLedOn();

/**
 * @brief Turn OFF all LED
 */
void allLedOff();

/**
 * @brief Blink all LED
 * @param miliseconds Time of each ON/OFF state
 *        num Number of times LED blinks
 */
void allLedToggle(uint16_t miliseconds, uint8_t num);

/**
 * @brief Turn ON LED 0->6
 */
void ledOn(uint8_t num);

/**
 * @brief Turn ON LED 0->6
 */
void ledOff(uint8_t num);

#endif /* LED_LED_H_ */
