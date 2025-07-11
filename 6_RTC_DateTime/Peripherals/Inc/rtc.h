/*
 * rtc.h
 *
 *  Created on: Sep 11, 2021
 *      Author: THINH
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"

// RTC Date and Time structure
typedef struct
{
  uint8_t hour;     // hours, range 0 to 23
  uint8_t min;      // minutes, range 0 to 59
  uint8_t sec;      // seconds,  range 0 to 59
  uint8_t wday;     // day of the week, range 0 to 6
  uint8_t mday;     // day of the month, range 1 to 31
  uint8_t month;    // month, range 1 to 12
  uint16_t year;    // The number of years since 0
}RTC_DateTime;

/**
 * @brief LSE configuration
 */
void rtc_LSE_config();

/**
 * @brief RTC peripheral configuration
 */
void rtc_config();

/**
 * @brief RTC set UNIX counter
 */
void rtc_setUnixTime(uint32_t unix);

/**
 * @brief RTC get UNIX counter
 */
uint32_t rtc_getUnixTime(void);

/**
 * @brief Set date and time
 * @note: No need to set weekday
 */
void rtc_setDateTime(RTC_DateTime *pDateTime);

/**
 * @brief Get date and time
 * @note: This function return a valid weekday
 */
void rtc_getDateTime(RTC_DateTime *pDateTime);

#endif /* INC_RTC_H_ */
