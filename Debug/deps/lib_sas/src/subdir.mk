################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../deps/lib_sas/src/lib_sas.c 

OBJS += \
./deps/lib_sas/src/lib_sas.o 

C_DEPS += \
./deps/lib_sas/src/lib_sas.d 


# Each subdirectory must supply rules for building sources it contributes
deps/lib_sas/src/lib_sas.o: ../deps/lib_sas/src/lib_sas.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L412xx -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../app/inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../deps/lib_sas/inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"deps/lib_sas/src/lib_sas.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

