################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Mid/MPU6050/Mid/MPU6050/MPU6050.cpp 

OBJS += \
./Source/Mid/MPU6050/Mid/MPU6050/MPU6050.o 

CPP_DEPS += \
./Source/Mid/MPU6050/Mid/MPU6050/MPU6050.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Mid/MPU6050/Mid/MPU6050/%.o Source/Mid/MPU6050/Mid/MPU6050/%.su: ../Source/Mid/MPU6050/Mid/MPU6050/%.cpp Source/Mid/MPU6050/Mid/MPU6050/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/App/MPU6050-App" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/Mid/MPU6050" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/Driver/I2CDev" -I../Core/Inc -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Driver" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Mid" -I"D:/Drive C/Github/STM32/JGB37-520-v4/Source/Utillities" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source-2f-Mid-2f-MPU6050-2f-Mid-2f-MPU6050

clean-Source-2f-Mid-2f-MPU6050-2f-Mid-2f-MPU6050:
	-$(RM) ./Source/Mid/MPU6050/Mid/MPU6050/MPU6050.d ./Source/Mid/MPU6050/Mid/MPU6050/MPU6050.o ./Source/Mid/MPU6050/Mid/MPU6050/MPU6050.su

.PHONY: clean-Source-2f-Mid-2f-MPU6050-2f-Mid-2f-MPU6050

