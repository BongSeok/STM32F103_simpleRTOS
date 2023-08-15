################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../OS/kernel/Src/event.c \
../OS/kernel/Src/kernel.c \
../OS/kernel/Src/msg.c \
../OS/kernel/Src/task.c 

OBJS += \
./OS/kernel/Src/event.o \
./OS/kernel/Src/kernel.o \
./OS/kernel/Src/msg.o \
./OS/kernel/Src/task.o 

C_DEPS += \
./OS/kernel/Src/event.d \
./OS/kernel/Src/kernel.d \
./OS/kernel/Src/msg.d \
./OS/kernel/Src/task.d 


# Each subdirectory must supply rules for building sources it contributes
OS/kernel/Src/%.o OS/kernel/Src/%.su OS/kernel/Src/%.cyclo: ../OS/kernel/Src/%.c OS/kernel/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/asus/STM32CubeIDE/workspace_1.12.0/STM32F103_simpleRTOS/OS/kernel/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-OS-2f-kernel-2f-Src

clean-OS-2f-kernel-2f-Src:
	-$(RM) ./OS/kernel/Src/event.cyclo ./OS/kernel/Src/event.d ./OS/kernel/Src/event.o ./OS/kernel/Src/event.su ./OS/kernel/Src/kernel.cyclo ./OS/kernel/Src/kernel.d ./OS/kernel/Src/kernel.o ./OS/kernel/Src/kernel.su ./OS/kernel/Src/msg.cyclo ./OS/kernel/Src/msg.d ./OS/kernel/Src/msg.o ./OS/kernel/Src/msg.su ./OS/kernel/Src/task.cyclo ./OS/kernel/Src/task.d ./OS/kernel/Src/task.o ./OS/kernel/Src/task.su

.PHONY: clean-OS-2f-kernel-2f-Src

