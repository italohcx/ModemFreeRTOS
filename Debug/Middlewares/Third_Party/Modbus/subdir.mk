################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/Modbus/modbus.c \
../Middlewares/Third_Party/Modbus/modbus_map.c 

OBJS += \
./Middlewares/Third_Party/Modbus/modbus.o \
./Middlewares/Third_Party/Modbus/modbus_map.o 

C_DEPS += \
./Middlewares/Third_Party/Modbus/modbus.d \
./Middlewares/Third_Party/Modbus/modbus_map.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/Modbus/%.o Middlewares/Third_Party/Modbus/%.su Middlewares/Third_Party/Modbus/%.cyclo: ../Middlewares/Third_Party/Modbus/%.c Middlewares/Third_Party/Modbus/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/BSP/Components/dp83848 -I"/home/italo/STM32CubeIDE/workspace_1.14.0_2/STM32F4_BOARD/Middlewares/Third_Party/LittleFs" -I"/home/italo/STM32CubeIDE/workspace_1.14.0_2/STM32F4_BOARD/Middlewares/Third_Party/w25Qxx" -I"/home/italo/STM32CubeIDE/workspace_1.14.0_2/STM32F4_BOARD/Middlewares/Third_Party/Modbus" -I"/home/italo/STM32CubeIDE/workspace_1.14.0_2/STM32F4_BOARD/Middlewares/Third_Party/ssd1306" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-Modbus

clean-Middlewares-2f-Third_Party-2f-Modbus:
	-$(RM) ./Middlewares/Third_Party/Modbus/modbus.cyclo ./Middlewares/Third_Party/Modbus/modbus.d ./Middlewares/Third_Party/Modbus/modbus.o ./Middlewares/Third_Party/Modbus/modbus.su ./Middlewares/Third_Party/Modbus/modbus_map.cyclo ./Middlewares/Third_Party/Modbus/modbus_map.d ./Middlewares/Third_Party/Modbus/modbus_map.o ./Middlewares/Third_Party/Modbus/modbus_map.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-Modbus

