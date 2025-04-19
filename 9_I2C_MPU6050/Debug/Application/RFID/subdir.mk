################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/RFID/rc522.c 

OBJS += \
./Application/RFID/rc522.o 

C_DEPS += \
./Application/RFID/rc522.d 


# Each subdirectory must supply rules for building sources it contributes
Application/RFID/rc522.o: ../Application/RFID/rc522.c Application/RFID/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/9_I2C_MPU6050/Core/Inc" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/9_I2C_MPU6050/Peripherals/Inc" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/9_I2C_MPU6050/CMSIS/Include" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/9_I2C_MPU6050/Application/RFID" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/9_I2C_MPU6050/Application/MPU6050" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/RFID/rc522.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

