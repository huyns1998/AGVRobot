################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/Utillities/kalman.c \
../Source/Utillities/queue.c 

C_DEPS += \
./Source/Utillities/kalman.d \
./Source/Utillities/queue.d 

OBJS += \
./Source/Utillities/kalman.o \
./Source/Utillities/queue.o 


# Each subdirectory must supply rules for building sources it contributes
Source/Utillities/%.o Source/Utillities/%.su: ../Source/Utillities/%.c Source/Utillities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/App/MPU6050-App" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/Mid/MPU6050" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/Driver/I2CDev" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/Mid/MPU6050" -I../Core/Inc -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Driver" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Utillities" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source-2f-Utillities

clean-Source-2f-Utillities:
	-$(RM) ./Source/Utillities/kalman.d ./Source/Utillities/kalman.o ./Source/Utillities/kalman.su ./Source/Utillities/queue.d ./Source/Utillities/queue.o ./Source/Utillities/queue.su

.PHONY: clean-Source-2f-Utillities

