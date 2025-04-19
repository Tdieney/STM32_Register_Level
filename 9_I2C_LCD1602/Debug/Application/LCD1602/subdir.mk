################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/LCD1602/LCD_HD44780.c 

OBJS += \
./Application/LCD1602/LCD_HD44780.o 

C_DEPS += \
./Application/LCD1602/LCD_HD44780.d 


# Each subdirectory must supply rules for building sources it contributes
Application/LCD1602/LCD_HD44780.o: ../Application/LCD1602/LCD_HD44780.c Application/LCD1602/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/9_I2C_LCD1602/Core/Inc" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/9_I2C_LCD1602/Peripherals/Inc" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/9_I2C_LCD1602/CMSIS/Include" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/9_I2C_LCD1602/Application/RFID" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/9_I2C_LCD1602/Application/LCD1602" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/LCD1602/LCD_HD44780.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

