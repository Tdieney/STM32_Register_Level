################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/main.c \
../Core/Src/printf_redirect.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/main.o \
./Core/Src/printf_redirect.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/main.d \
./Core/Src/printf_redirect.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/main.o: ../Core/Src/main.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/5_TIM_HCSR04/Core/Inc" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/5_TIM_HCSR04/Peripherals/Inc" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/5_TIM_HCSR04/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/printf_redirect.o: ../Core/Src/printf_redirect.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/5_TIM_HCSR04/Core/Inc" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/5_TIM_HCSR04/Peripherals/Inc" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/5_TIM_HCSR04/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/printf_redirect.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/system_stm32f1xx.o: ../Core/Src/system_stm32f1xx.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/5_TIM_HCSR04/Core/Inc" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/5_TIM_HCSR04/Peripherals/Inc" -I"E:/Downloads/TAI LIEU HCMUTE/VXLNC/STM32/SelfTaught/STM32 Getting Started - 2 Level/STM32F1_CubeIDE_RegCode/5_TIM_HCSR04/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32f1xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

