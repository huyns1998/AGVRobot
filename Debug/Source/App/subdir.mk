################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/App/main.c 

CPP_SRCS += \
../Source/App/maincpp.cpp 

C_DEPS += \
./Source/App/main.d 

OBJS += \
./Source/App/main.o \
./Source/App/maincpp.o 

CPP_DEPS += \
./Source/App/maincpp.d 


# Each subdirectory must supply rules for building sources it contributes
Source/App/%.o Source/App/%.su: ../Source/App/%.c Source/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/App/MPU6050-App" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/Mid/MPU6050" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/Driver/I2CDev" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/Mid/MPU6050" -I../Core/Inc -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Driver" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Utillities" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Source/App/%.o Source/App/%.su: ../Source/App/%.cpp Source/App/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/App/MPU6050-App" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/Mid/MPU6050" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/Driver/I2CDev" -I../Core/Inc -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Driver" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Utillities" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source-2f-App

clean-Source-2f-App:
	-$(RM) ./Source/App/main.d ./Source/App/main.o ./Source/App/main.su ./Source/App/maincpp.d ./Source/App/maincpp.o ./Source/App/maincpp.su

.PHONY: clean-Source-2f-App

