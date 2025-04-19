/*
 * main.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

#define KP                  385
#define KD                  147
#define DEFAULT_SPEED       3800
#define ACTIVATE_THRESHOLD  2500
#define MPU6050_I2C_ADDR    (0x68 << 1)
#define MPU6050             (0xD0)


uint8_t i, j, mode;
uint16_t sensorValue[10];
uint32_t adcValue[5];
extern uint16_t Threshold[7];
extern bool exti2Flag, exti11Flag;
uint16_t P, D; // 2 variables for finding PID coefficients
char str[10];
float x_mpu, y_mpu, z_mpu;
uint8_t data;

int main(void)
{
  // Initialize system
  rcc_config();
  //systick_config();
  gpio_config();
  exti_config();
  tim_config();
  adc_config();
  dma_config();
  i2c_config();

  // Read accelerometer x, y, z values
  MPU_ConfigTypeDef myConfig;
  myConfig.Accel_Full_Scale = AFS_SEL_4g;
  myConfig.ClockSource = Internal_8MHz;
  myConfig.CONFIG_DLPF = DLPF_184A_188G_Hz;
  myConfig.Sleep_Mode_Bit = 0;
  myConfig.Gyro_Full_Scale = FS_SEL_500;
  MPU6050_Config(&myConfig);
  ScaledData_Def myAccel;

  P = 0;
  mode = 0;

  while(1)
  {
    switch(mode)
    {
      // Setting mode
      case 0:
//        // Set and display P or D for PID algorithm coefficients fix
//        if(exti2Flag)
//        {
//          exti2Flag = false;
//          // Handle interrupt
//          P += 10;
//          // Unmask EXTI2
//          EXTI->IMR |= EXTI_IMR_IM2;
//        }
//        if(exti11Flag)
//        {
//          exti11Flag = false;
//          // Handle interrupt
//          mode++;
//          // Unmask EXTI11
//          EXTI->IMR |= EXTI_IMR_IM11;
//        }
//        sprintf(str, "P=%u", (unsigned int)P);
//        led7seg_string(str);


//        // MPU6050 test
//        MPU6050_Get_Accel_Scale(&myAccel);
//        x_mpu = myAccel.x;
//        y_mpu = myAccel.y;
//        z_mpu = myAccel.z;
//        tim_msDelay(100);

//        // Parameters calibration
//        led_toggleAll(500, 4);
//        readHighValue();
//        led_toggleAll(200, 10);
//        readLowValue();
//        // Calculate threshold and write to flash
//        calcThreshold();

        if(sensorValue[7] < ACTIVATE_THRESHOLD)
        {
          mode++;
        }
        break;

      // Start signal by buzzer
      case 1:
        // Get threshold in FLASH
        getThreshold();

        for(i = 0; i < 3; i++)
        {
          GPIOB->BSRR |= (1 << 10);
          for(j = 7; j > 0; j--)
          {
            led_on(j);
            tim_msDelay(10);
          }
          led_offAll();
          GPIOB->BRR |= (1 << 10);
          tim_msDelay(1000);
        }
        GPIOA->ODR = 0x1700;
        GPIOB->ODR = 0xF400;
        tim_msDelay(1000);
        led_offAll();
        GPIOB->BRR |= (1 << 10);
        mode++;

      // Run mode
      case 2:
        sigProcessing();
        calcPID(KP, KD, DEFAULT_SPEED);
        break;

      // Stop mode
      case 3:
        if(sensorValue[7] < ACTIVATE_THRESHOLD)
        {
          mode = 1;
        }
        break;
    }
  }
}


