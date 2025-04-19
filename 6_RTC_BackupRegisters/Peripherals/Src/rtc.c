/*
 * rtc.c
 *
 *  Created on: Sep 11, 2021
 *      Author: THINH
 */

#include "rtc.h"

time_t unixValue, alarmUnixValue;

const char* WeekDay[7] = {
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat",
    "Sun"
};

/**
 * @brief LSE configuration
 */
void rtc_LSE_config()
{
  // Enable PWR clock
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  // Enable write access to backup  domain
  PWR->CR |= PWR_CR_DBP;
  while(!(PWR->CR & PWR_CR_DBP));
  // Check if LSE already selected as RTC clock source -> return
  uint32_t rtcselBit = (RCC->BDCR & RCC_BDCR_RTCSEL);
  if(rtcselBit == RCC_BDCR_RTCSEL_0)
  {
    printf("\nLSE has been already selected as RTC clock source!");
    return;
  }
  // Reset backup domain (change clock source)
  __IO uint32_t bdcrTempValue = (RCC->BDCR & ~RCC_BDCR_RTCSEL);
  RCC->BDCR = RCC_BDCR_BDRST;
  RCC->BDCR = 0;                                    //???????????????????
  // Restore backup register value
  RCC->BDCR = bdcrTempValue;
  // Enable LSE
  RCC->BDCR |= RCC_BDCR_LSEON;
  while(!(RCC->BDCR & RCC_BDCR_LSERDY));
  // Select LSE as source
  RCC->BDCR |= RCC_BDCR_RTCSEL_0;
  // Enable RTC
  RCC->BDCR |= RCC_BDCR_RTCEN;
}

/**
 * @brief RTC peripheral configuration
 */
void rtc_config()
{
  // Poll RTOFF, wait until its value goes to ‘1’
  while(!(RTC->CRL & RTC_CRL_RTOFF));
  // Set the CNF bit to enter configuration mode
  RTC->CRL |= RTC_CRL_CNF;
  // Set prescaler
  RTC->PRLH = 0;
  RTC->PRLL = 0x7FFF;
  // Clear the CNF bit to exit configuration mode
  RTC->CRL &= ~RTC_CRL_CNF;
  // Poll RTOFF, wait until its value goes to ‘1’ to check the end of the write operation.
  while(!(RTC->CRL & RTC_CRL_RTOFF));
}

/**
 * @brief RTC set UNIX counter
 */
void rtc_setUnixTime(uint32_t unix)
{
  // Poll RTOFF, wait until its value goes to ‘1’
  while(!(RTC->CRL & RTC_CRL_RTOFF));
  // Set the CNF bit to enter configuration mode
  RTC->CRL |= RTC_CRL_CNF;
  // Set counter
  RTC->CNTH = (unix >> 16) & 0xFFFF;
  RTC->CNTL = unix & 0xFFFF;
  // Clear the CNF bit to exit configuration mode
  RTC->CRL &= ~RTC_CRL_CNF;
  // Poll RTOFF, wait until its value goes to ‘1’ to check the end of the write operation.
  while(!(RTC->CRL & RTC_CRL_RTOFF));
}

/**
 * @brief RTC get UNIX counter
 */
uint32_t rtc_getUnixTime(void)
{
  return (uint32_t) (RTC->CNTH << 16) | (RTC->CNTL);
}

/**
 * @brief Set date and time
 * @note: No need to set weekday
 */
void rtc_setDateTime(RTC_DateTime *pDateTime)
{
  struct tm myTime;
  struct tm *myTimePtr = &myTime;
  // Copy parameters from out structure to time.h structure
  myTimePtr->tm_hour = pDateTime->hour;
  myTimePtr->tm_min = pDateTime->min;
  myTimePtr->tm_sec = pDateTime->sec;

  myTimePtr->tm_mday = pDateTime->mday;
  myTimePtr->tm_mon = pDateTime->month - 1;
  myTimePtr->tm_year = pDateTime->year - 1900;
  // Convert to Unix value
  unixValue = mktime(myTimePtr);
  // Set RTC value
  rtc_setUnixTime((uint32_t)unixValue);
}

/**
 * @brief Get date and time
 * @note: This function return a valid weekday
 */
void rtc_getDateTime(RTC_DateTime *pDateTime)
{
  struct tm myTime;
  struct tm *myTimePtr = &myTime;
  // Get RTC value
  unixValue = (time_t)rtc_getUnixTime();
  // Convert back to user time structure
  myTimePtr = gmtime(&unixValue);
  pDateTime->hour = myTimePtr->tm_hour;
  pDateTime->min = myTimePtr->tm_min;
  pDateTime->sec = myTimePtr->tm_sec;
  pDateTime->wday = myTimePtr->tm_wday;
  pDateTime->mday = myTimePtr->tm_mday;
  pDateTime->month = myTimePtr->tm_mon + 1;
  pDateTime->year = myTimePtr->tm_year + 1900;
}

/**
 * @brief RTC set UNIX alarm
 */
void rtc_setUnixAlarm(uint32_t unix)
{
  // Poll RTOFF, wait until its value goes to ‘1’
  while(!(RTC->CRL & RTC_CRL_RTOFF));
  // Set the CNF bit to enter configuration mode
  RTC->CRL |= RTC_CRL_CNF;
  // Set counter
  RTC->ALRH = (unix >> 16) & 0xFFFF;
  RTC->ALRL = unix & 0xFFFF;
  // Clear the CNF bit to exit configuration mode
  RTC->CRL &= ~RTC_CRL_CNF;
  // Poll RTOFF, wait until its value goes to ‘1’ to check the end of the write operation.
  while(!(RTC->CRL & RTC_CRL_RTOFF));
}

/**
 * @brief RTC get UNIX alarm
 */
uint32_t rtc_getUnixAlarm(void)
{
  return (uint32_t) (RTC->ALRH << 16) | (RTC->ALRL);
}

/**
 * @brief Alarm configuration
 */
void rtc_alarm_config()
{
  // Clear pending bit of EXTI line 17          //?????????????????????
  EXTI->PR |= EXTI_PR_PR17;                     //
  // Configure the mask bits of the Interrupt line 17 (EXTI_IMR)
  EXTI->IMR |= EXTI_IMR_IM17;
  // Configure the Trigger Selection bits of the Interrupt line 17 (EXTI_RTSR and EXTI_FTSR)
  EXTI->RTSR |= EXTI_RTSR_RT17;
  EXTI->FTSR &= ~EXTI_FTSR_FT17;
  // Configure the enable and mask bits that control the NVIC IRQ channel mapped to the EXTI line 17
  NVIC_SetPriority(RTC_Alarm_IRQn, 5);
  NVIC_EnableIRQ(RTC_Alarm_IRQn);
}

/**
 * @brief Set alarm
 */
void rtc_setAlarm(RTC_DateTime *pAlarm)
{
  struct tm myAlarm;
  struct tm *myAlarmPtr = &myAlarm;
  // Copy parameters from out structure to time.h structure
  myAlarmPtr->tm_hour = pAlarm->hour;
  myAlarmPtr->tm_min = pAlarm->min;
  myAlarmPtr->tm_sec = pAlarm->sec;

  myAlarmPtr->tm_mday = pAlarm->mday;
  myAlarmPtr->tm_mon = pAlarm->month - 1;
  myAlarmPtr->tm_year = pAlarm->year - 1900;
  // Convert to Unix value
  alarmUnixValue = mktime(myAlarmPtr);
  // Set RTC alarm value
  rtc_setUnixAlarm((uint32_t)alarmUnixValue);
}

/**
 * @brief Get alarm
 */
void rtc_getAlarm(RTC_DateTime *pAlarm)
{
  struct tm myAlarm;
  struct tm *myAlarmPtr = &myAlarm;
  // Get RTC value
  alarmUnixValue = (time_t)rtc_getUnixAlarm();
  // Convert back to user time structure
  myAlarmPtr = gmtime(&alarmUnixValue);
  pAlarm->hour = myAlarmPtr->tm_hour;
  pAlarm->min = myAlarmPtr->tm_min;
  pAlarm->sec = myAlarmPtr->tm_sec;
  pAlarm->wday = myAlarmPtr->tm_wday;
  pAlarm->mday = myAlarmPtr->tm_mday;
  pAlarm->month = myAlarmPtr->tm_mon + 1;
  pAlarm->year = myAlarmPtr->tm_year + 1900;
}

/**
 * @brief Enable write access to backup register
 */
void rtc_backupRegs_writeEnable()
{
  // Enable the power and backup interface clocks in the RCC_APB1ENR register
  RCC->APB1ENR |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN;
  // Set the DBP bit the Power Control Register (PWR_CR) to enable access to the Backup registers and RTC
  PWR->CR |= PWR_CR_DBP;
}
