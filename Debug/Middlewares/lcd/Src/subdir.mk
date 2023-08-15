################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lcd/Src/lcd.c 

OBJS += \
./Middlewares/lcd/Src/lcd.o 

C_DEPS += \
./Middlewares/lcd/Src/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lcd/Src/%.o Middlewares/lcd/Src/%.su Middlewares/lcd/Src/%.cyclo: ../Middlewares/lcd/Src/%.c Middlewares/lcd/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I"C:/Users/asus/STM32CubeIDE/workspace_1.12.0/STM32F103_simpleRTOS/Middlewares/lcd/Inc" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/asus/STM32CubeIDE/workspace_1.12.0/STM32F103_simpleRTOS/OS/kernel/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-lcd-2f-Src

clean-Middlewares-2f-lcd-2f-Src:
	-$(RM) ./Middlewares/lcd/Src/lcd.cyclo ./Middlewares/lcd/Src/lcd.d ./Middlewares/lcd/Src/lcd.o ./Middlewares/lcd/Src/lcd.su

.PHONY: clean-Middlewares-2f-lcd-2f-Src

