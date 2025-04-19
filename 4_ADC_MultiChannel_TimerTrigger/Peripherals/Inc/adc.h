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
  ADC_CHANNEL0 = 0,
  ADC_CHANNEL1,
  ADC_CHANNEL2,
  ADC_CHANNEL3,
  ADC_CHANNEL4,
  ADC_CHANNEL5,
  ADC_CHANNEL6,
  ADC_CHANNEL7,
  ADC_CHANNEL8,
  ADC_CHANNEL9,
  ADC_CHANNEL10,
  ADC_CHANNEL11,
  ADC_CHANNEL12,
  ADC_CHANNEL13,
  ADC_CHANNEL14,
  ADC_CHANNEL15
}ADC_CHANNEL;

/**
 * @brief ADC GPIO pins: PA1-POT, PA2-X, PA3-Y
 */
void adc_GPIO_config();

/**
 * @brief ADC single channel configuration
 */
void adc_single_config(ADC_CHANNEL channel);

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

/**
 * @brief ADC enable/disable Interrupt
 */
void adc_enableEOC_IT();
void adc_disableEOC_IT();

/**
 * @brief ADC multi channel configuration
 */
void adc_multiChannel_config();

/**
 * @brief ADC DMA configurtion
 */
void adc_multiChannel_DMA_config(uint16_t *pADCBuffer);

#endif /* INC_ADC_H_ */
