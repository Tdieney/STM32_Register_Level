/*
 * main.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"
#include "cmsis_os.h"

#define LED_PB0    BIT_BAND((uint32_t)&(GPIOB->ODR), 0)
#define LED_PB1    BIT_BAND((uint32_t)&(GPIOB->ODR), 1)

// Thread1
osThreadId Thread1Handle;
void Thread1Handler(void const *argument);
// Thread2
osThreadId Thread2Handle;
void Thread2Handler(void const *argument);

int main()
{
  // Configure 72MHz clock
  rcc_HSE_config();
  rcc_SysTick_config();
  tim_TIM2_initTicks();
  // UART configuration
  uart_UART1_GPIO_config();
  uart_UART1_config();
  // LED configuration
  gpio_LED_config();
  // Button configuration
  gpio_PB_config();
  // Slide switch configuration
  gpio_SW_config();

  // Thread1 initialization
  osThreadDef(Thread1, Thread1Handler, osPriorityNormal, 0, 128);
  Thread1Handle = osThreadCreate(osThread(Thread1), NULL);
  // Thread2 initialization
  osThreadDef(Thread2, Thread2Handler, osPriorityNormal, 0, 128);
  Thread2Handle = osThreadCreate(osThread(Thread2), NULL);

  // Start scheduler
  osKernelStart();

  while(1)
  {
  }
}

// Thread1
void Thread1Handler(void const *argument)
{
  while(1)
  {
    LED_PB0 =! LED_PB0;
    osDelay(2000);
  }
}

// Thread2
void Thread2Handler(void const *argument)
{
  while(1)
  {
    LED_PB1 =! LED_PB1;
    osDelay(4000);
  }
}
