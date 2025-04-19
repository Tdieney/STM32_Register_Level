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
void led_onAll();

/**
 * @brief Turn OFF all LED
 */
void led_offAll();

/**
 * @brief Blink all LED
 * @param miliseconds Time of each ON/OFF state
 *        num Number of times LED blinks
 */
void led_toggleAll(uint16_t miliseconds, uint8_t num);

/**
 * @brief Turn ON LED 0->6
 */
void led_on(uint8_t num);

/**
 * @brief Turn ON LED 0->6
 */
void led_off(uint8_t num);

/**
 * @brief LED 7 segment shows characters
 */
void led7seg_putc(char c);

/**
 * @brief LED 7 segment shows string by character
 */
void led7seg_string (char *str);

#endif /* LED_LED_H_ */
