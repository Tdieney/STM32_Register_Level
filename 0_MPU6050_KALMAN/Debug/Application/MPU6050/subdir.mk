################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/MPU6050/mpu6050.c 

OBJS += \
./Application/MPU6050/mpu6050.o 

C_DEPS += \
./Application/MPU6050/mpu6050.d 


# Each subdirectory must supply rules for building sources it contributes
Application/MPU6050/mpu6050.o: ../Application/MPU6050/mpu6050.c Application/MPU6050/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/0_MPU6050_KALMAN/Application/MPU6050" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/MPU6050/mpu6050.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

