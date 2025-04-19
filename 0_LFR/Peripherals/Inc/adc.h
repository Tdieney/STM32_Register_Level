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
 * @brief ADC1 and ADC2 configuration
 */
void adc_config();

#endif /* INC_ADC_H_ */
