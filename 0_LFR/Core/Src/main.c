/*
 * main.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"
#include "cmsis_os.h"

#define KP 200
#define KD 0
#define DEFAULT_SPEED 3200
#define ACTIVATE_THRESHOLD 2500

extern bool tcFlag;
uint8_t t, n, mode;
uint16_t sensorValue[10];
uint32_t adcValue[5];
extern uint16_t Threshold[7];

osThreadId ReadIRSensorHandle;
osThreadId WriteIOHandle;
void ReadIRSensorHandler(void const *argument);
void WriteIOHandler(void const *argument);

int main()
{
  // Configure 64MHz clock
  rcc_config();
  systick_config();
  adc_config();
  gpio_config();
  tim_config();
  adc_config();
  dma_config(adcValue);

  mode = 1;

  // Thread1 initialization
  osThreadDef(ReadIRSensor, ReadIRSensorHandler, osPriorityNormal, 0, 128);
  ReadIRSensorHandle = osThreadCreate(osThread(ReadIRSensor), NULL);
  // Thread2 initialization
  osThreadDef(WriteIO, WriteIOHandler, osPriorityNormal, 0, 128);
  WriteIOHandle = osThreadCreate(osThread(WriteIO), NULL);

  // Start scheduler
  osKernelStart();
}

void ReadIRSensorHandler(void const *argument)
{
  while(1)
  {
    if(tcFlag)
    {
      // Clear flag
      tcFlag = false;
      // Get and sort analog value
      sensorValue[9] =  adcValue[0] & 0x0000FFFF;
      sensorValue[8] = (adcValue[0] & 0xFFFF0000) >> 16;
      sensorValue[6] =  adcValue[1] & 0x0000FFFF;
      sensorValue[3] = (adcValue[1] & 0xFFFF0000) >> 16;
      sensorValue[5] =  adcValue[2] & 0x0000FFFF;
      sensorValue[7] = (adcValue[2] & 0xFFFF0000) >> 16;
      sensorValue[4] =  adcValue[3] & 0x0000FFFF;
      sensorValue[2] = (adcValue[3] & 0xFFFF0000) >> 16;
      sensorValue[0] =  adcValue[4] & 0x0000FFFF;
      sensorValue[1] = (adcValue[4] & 0xFFFF0000) >> 16;
    }
  }
}

void WriteIOHandler(void const *argument)
{
  while(1)
  {
//    while(sensorValue[7] > ACTIVATE_THRESHOLD);
//    setLeftMotor(2500, 1);
//    setRightMotor(2500, 0);
    switch(mode)
    {
      // Parameters calibration
      case 0:
        allLedToggle(500, 4);
        readHighValue();
        allLedToggle(200, 10);
        readLowValue();
        calcThreshold();
        while(sensorValue[7] > ACTIVATE_THRESHOLD);
        mode++;
        break;

      // Start signal by buzzer
      case 1:
        // Get threshold in FLASH
        getThreshold();

        for(n = 0; n < 2; n++)
        {
          GPIOB->BSRR |= (1 << 10);
          tim_msDelay(200);
          GPIOB->BRR |= (1 << 10);
          tim_msDelay(800);
        }
        GPIOB->BSRR |= (1 << 10);
        tim_msDelay(1000);
        GPIOB->BRR |= (1 << 10);
        mode++;

      // Run mode
      case 2:
        sigProcessing();
        calcPID(KP, KD, DEFAULT_SPEED);
        break;

      //stop mode
      case 3:
        stopLeftMotor();
        stopRightMotor();
        allLedOff();
        while(sensorValue[7] > ACTIVATE_THRESHOLD);
        mode = 1;
    }
  }
}


