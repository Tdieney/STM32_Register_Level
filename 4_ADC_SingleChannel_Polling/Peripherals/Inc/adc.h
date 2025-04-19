/*
 * adc.h
 *
 *  Created on: Aug 23, 2021
 *      Author: THINH
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "main.h"

// ADC single channel
typedef enum
{
  ADC_SINGLE_CHANNEL1 = 1,
  ADC_SINGLE_CHANNEL2,
  ADC_SINGLE_CHANNEL3
}ADC_SINGLE_CHANNEL;

/**
 * @brief ADC GPIO pins: PA1-POT, PA2-X, PA3-Y
 */
void adc_GPIO_config();

/**
 * @brief ADC single channel configuration
 */
void adc_single_config(ADC_SINGLE_CHANNEL channel);

/**
 * @brief ADC start - SWSTART
 */
void adc_start();

/**
 * @brief ADC stop
 */
void adc_stop();

/**
 * @brief ADC poll for End of Conversion
 */
bool adc_pollForEOC(uint32_t msTimeout);

/**
 * @brief Read ADC value
 */
uint16_t adc_readValue();

#endif /* INC_ADC_H_ */
