################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/OS/kernel/Src/kernel.c \
../Core/OS/kernel/Src/task.c 

OBJS += \
./Core/OS/kernel/Src/kernel.o \
./Core/OS/kernel/Src/task.o 

C_DEPS += \
./Core/OS/kernel/Src/kernel.d \
./Core/OS/kernel/Src/task.d 


# Each subdirectory must supply rules for building sources it contributes
Core/OS/kernel/Src/%.o Core/OS/kernel/Src/%.su Core/OS/kernel/Src/%.cyclo: ../Core/OS/kernel/Src/%.c Core/OS/kernel/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/asus/STM32CubeIDE/workspace_1.12.0/STM32F103_simpleRTOS/Core/OS/kernel/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-OS-2f-kernel-2f-Src

clean-Core-2f-OS-2f-kernel-2f-Src:
	-$(RM) ./Core/OS/kernel/Src/kernel.cyclo ./Core/OS/kernel/Src/kernel.d ./Core/OS/kernel/Src/kernel.o ./Core/OS/kernel/Src/kernel.su ./Core/OS/kernel/Src/task.cyclo ./Core/OS/kernel/Src/task.d ./Core/OS/kernel/Src/task.o ./Core/OS/kernel/Src/task.su

.PHONY: clean-Core-2f-OS-2f-kernel-2f-Src

