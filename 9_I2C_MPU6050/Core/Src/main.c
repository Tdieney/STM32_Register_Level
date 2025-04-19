/*
 * rcc.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Nguyen Tran Van Thinh
 */

#include "main.h"

#define MPU6050_I2C_ADDR  (0x68 << 1)
#define LCD1602_I2C_ADDR  (0x4E)

float x_mpu,y_mpu,z_mpu;
int count;

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
  // I2C configuration
  i2c_I2C1_GPIO_config();
  i2c_I2C1_config();

  // Test slave address
  if(i2c_I2C1_isSlaveAddressExist(MPU6050_I2C_ADDR, 10))
  {
    printf("I2C Device with address 0x%02X is detected successfully\n", MPU6050_I2C_ADDR);
    gpio_LED_write(1);
  }
  else
  {
    printf("Failed to detect I2C device with address 0x%02X\n", MPU6050_I2C_ADDR);
    gpio_LED_write(0);
  }

//  // Check for I2C address
//  for(uint8_t i = 0; i <= 255; i++)
//  {
//    if(i2c_I2C1_isSlaveAddressExist(i, 10))
//    {
//      printf("I2C Device with address 0x%02X is detected successfully\n", MPU6050_I2C_ADDR);
//      gpio_LED_write(1);
//      break;
//    }
//  }
  // Read Who Am I register
  uint8_t data;
  I2C_Read(117, &data, 1);
  printf("WHO_AM_I REGISTER VALUE: 0x%02X\n", data);

  // Read accelerometer x, y, z values
  MPU_ConfigTypeDef myConfig;
  myConfig.Accel_Full_Scale = AFS_SEL_4g;
  myConfig.ClockSource = Internal_8MHz;
  myConfig.CONFIG_DLPF = DLPF_184A_188G_Hz;
  myConfig.Sleep_Mode_Bit = 0;
  myConfig.Gyro_Full_Scale = FS_SEL_500;
  MPU6050_Config(&myConfig);
  ScaledData_Def myAccel;

  while(1)
  {
    MPU6050_Get_Accel_Scale(&myAccel);
    printf("Accel: X = %.2f, Y = %.2f, Z = %.2f\n", myAccel.x, myAccel.y, myAccel.z);
    printf("----------------------------------------\n\n");
    rcc_msDelay(500);
  }
}
