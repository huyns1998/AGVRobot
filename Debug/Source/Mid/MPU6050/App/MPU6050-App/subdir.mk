################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Mid/MPU6050/App/MPU6050-App/MPU6050-App.cpp \
../Source/Mid/MPU6050/App/MPU6050-App/MPU6050-Calibration.cpp 

OBJS += \
./Source/Mid/MPU6050/App/MPU6050-App/MPU6050-App.o \
./Source/Mid/MPU6050/App/MPU6050-App/MPU6050-Calibration.o 

CPP_DEPS += \
./Source/Mid/MPU6050/App/MPU6050-App/MPU6050-App.d \
./Source/Mid/MPU6050/App/MPU6050-App/MPU6050-Calibration.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Mid/MPU6050/App/MPU6050-App/%.o: ../Source/Mid/MPU6050/App/MPU6050-App/%.cpp Source/Mid/MPU6050/App/MPU6050-App/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"C:/Users/hi/Desktop/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/App/MPU6050-App" -I"C:/Users/hi/Desktop/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/Mid/MPU6050" -I"C:/Users/hi/Desktop/Github/STM32/JGB37-520-v4/Source/Mid/MPU6050/Driver/I2CDev" -I../Core/Inc -I"C:/Users/hi/Desktop/Github/STM32/JGB37-520-v4/Source/Driver" -I"C:/Users/hi/Desktop/Github/STM32/JGB37-520-v4/Source/Mid" -I"C:/Users/hi/Desktop/Github/STM32/JGB37-520-v4/Source/Utillities" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

