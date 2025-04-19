/*
 * func.c
 *
 *  Created on: Dec 18, 2021
 *      Author: THINH
 */

#include "func.h"

uint8_t y;
uint8_t sum;
uint16_t highValue[7], lowValue[7], Threshold[7], convertedValue[7];
extern uint8_t mode;
extern uint16_t sensorValue[10];
float err = 0, oldErr = 0;
float P = 0, D = 0, PD = 0;
uint16_t highSpeed = 0, lowSpeed = 0;


void readHighValue()
{
  for(uint8_t x = 0; x < 7; x++)
  highValue[x] = sensorValue[x];
}

void readLowValue()
{
  for(uint8_t x = 0; x < 7; x++)
  lowValue[x] = sensorValue[x];
}

/**
 * @brief Calculate line threshold and save to FLASH
 */
void calcThreshold()
{
  for(uint8_t x = 0; x < 7; x++)
  Threshold[x] = (highValue[x] + lowValue[x])/2;
  // Save threshold to flash
  flash_unlock();
  flash_erase(0x0800FC00);
  flash_write16(0x0800FC00, Threshold, 7);
  flash_lock();
}

/**
 * @brief Get threshold saved in FLASH before
 */
void getThreshold()
{
  flash_read16(0x0800FC00, Threshold, 7);
}

/**
 * @brief Process line signal
 * @note  Black line return high analog value
 *        White line return low analog value
 *        Testing on black line
 *
 */
void sigProcessing()
{
  y = 0;
  sum = 0;
  // 7 led for 7 bottom sensors
  for(uint8_t x = 1; x < 8; x++)
  {
    // Detect black color
    if (sensorValue[x - 1] >= Threshold[x - 1])
    {
      convertedValue[x - 1] = 1;
      sum += x;
      y++;
      ledOn(x);
    }
    // Detect white color
    else
    {
      convertedValue[x - 1] = 0;
      ledOff(x);
    }
  }
  if((y > 0) && (y < 7))
  {
    err = (float)sum/y - 4;
  }
  // All sensors in line
  else if(y == 7)
  {
    err = 0;
  }
  else if((err > -1) && (err < 1))
  {
    err = 0;
  }
}


/**
 * @brief Run with PID algorithm
 */
void calcPID(float Kp, float Kd, uint16_t defaultSpeed)
{
  PD = Kp*err + Kd*(err - oldErr);
  oldErr = err;
  highSpeed = defaultSpeed + ((PD > 0) ? PD : -PD);
  lowSpeed = defaultSpeed - ((PD > 0) ? PD : -PD);

  if(err < 0)
  {
    setLeftMotor(lowSpeed, 1);
    setRightMotor(highSpeed, 1);
  }
//  else if(err > 0)
//  {
//    setLeftMotor(highSpeed, 1);
//    setRightMotor(lowSpeed, 1);
//  }
//  else
//  {
//    setLeftMotor(3700, 1);
//    setRightMotor(3700, 1);
//  }
  else
  {
    setLeftMotor(highSpeed, 1);
    setRightMotor(lowSpeed, 1);
  }

  if(sensorValue[7] < 2500)
  {
    mode = 3;
    stopLeftMotor();
    stopRightMotor();
    tim_msDelay(500);
  }
}

