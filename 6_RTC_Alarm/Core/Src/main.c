/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

bool alarmFlag = 0;
uint32_t rtcCounterValue, rtcCounterValue_old;

extern const char* WeekDay[7];

int main(void)
{
  // Configure 72MHz clock
  rcc_HSE_config();
  rcc_SysTick_config();
  // UART configuration
  uart_UART1_GPIO_config();
  uart_UART1_config();
  // LED configuration
  gpio_LED_config();
  // Button configuration
  gpio_PB_config();
  // Slide switch configuration
  gpio_SW_config();
  // RTC configuration
  rtc_LSE_config();
  rtc_config();
  rtc_alarm_config();
//  rtc_setUnixTime(1000);

  RTC_DateTime myTime;
  myTime.hour = 1;
  myTime.min = 10;
  myTime.sec = 0;
  myTime.mday = 12;
  myTime.month = 9;
  myTime.year = 2020;
  rtc_setDateTime(&myTime);

  myTime.hour = 1;
  myTime.min = 10;
  myTime.sec = 20;
  myTime.mday = 12;
  myTime.month = 9;
  myTime.year = 2020;
  rtc_setAlarm(&myTime);
  rtc_getAlarm(&myTime);

  printf("\nAlarm: %s %02u/%02u/%04u %02u:%02u:%02u", WeekDay[myTime.wday],
            myTime.mday, myTime.month, myTime.year, myTime.hour, myTime.min, myTime.sec);
  LED_PC13 = 1;

  while(1)
  {
    rtcCounterValue = rtc_getUnixTime();
    rtc_getDateTime(&myTime);
    if(rtcCounterValue_old != rtcCounterValue)
    {
      rtcCounterValue_old = rtcCounterValue;
      printf("\n%s %02u/%02u/%04u %02u:%02u:%02u", WeekDay[myTime.wday],
          myTime.mday, myTime.month, myTime.year, myTime.hour, myTime.min, myTime.sec);
    }
    if(alarmFlag)
    {
      alarmFlag = 0;
      LED_PC13 = 0;
      printf("\n***** RTC - Alarm triggered! *****");
    }
  }
}

void RTC_Alarm_IRQHandler()
{
  // Clear pending bit
  EXTI->PR |= EXTI_PR_PR17;
  NVIC_ClearPendingIRQ(RTC_Alarm_IRQn);
  // Notify application
  alarmFlag = 1;
}
