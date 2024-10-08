################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/AdapterSSD1306.c \
../Core/Src/FileSystemAPI.c \
../Core/Src/cfg_files.c \
../Core/Src/datetime.c \
../Core/Src/freertos.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/lfs_w25qflash.c \
../Core/Src/logger.c \
../Core/Src/main.c \
../Core/Src/modbus_client.c \
../Core/Src/modbus_server.c \
../Core/Src/rtc.c \
../Core/Src/sntp_client.c \
../Core/Src/spi.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_hal_timebase_tim.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/AdapterSSD1306.o \
./Core/Src/FileSystemAPI.o \
./Core/Src/cfg_files.o \
./Core/Src/datetime.o \
./Core/Src/freertos.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/lfs_w25qflash.o \
./Core/Src/logger.o \
./Core/Src/main.o \
./Core/Src/modbus_client.o \
./Core/Src/modbus_server.o \
./Core/Src/rtc.o \
./Core/Src/sntp_client.o \
./Core/Src/spi.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_hal_timebase_tim.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/AdapterSSD1306.d \
./Core/Src/FileSystemAPI.d \
./Core/Src/cfg_files.d \
./Core/Src/datetime.d \
./Core/Src/freertos.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/lfs_w25qflash.d \
./Core/Src/logger.d \
./Core/Src/main.d \
./Core/Src/modbus_client.d \
./Core/Src/modbus_server.d \
./Core/Src/rtc.d \
./Core/Src/sntp_client.d \
./Core/Src/spi.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_hal_timebase_tim.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DLOG_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I"/home/italo/STM32CubeIDE/workspace_1.14.0_2/STM32F4_BOARD/Middlewares/Third_Party/LittleFs" -I"/home/italo/STM32CubeIDE/workspace_1.14.0_2/STM32F4_BOARD/Middlewares/Third_Party/w25Qxx" -I"/home/italo/STM32CubeIDE/workspace_1.14.0_2/STM32F4_BOARD/Middlewares/Third_Party/Modbus" -I"/home/italo/STM32CubeIDE/workspace_1.14.0_2/STM32F4_BOARD/Middlewares/Third_Party/ssd1306" -I"/home/italo/STM32CubeIDE/workspace_1.14.0_2/STM32F4_BOARD/Drivers/BSP/Components/dp83848" -I../Drivers/BSP/Components/dp83848 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/AdapterSSD1306.cyclo ./Core/Src/AdapterSSD1306.d ./Core/Src/AdapterSSD1306.o ./Core/Src/AdapterSSD1306.su ./Core/Src/FileSystemAPI.cyclo ./Core/Src/FileSystemAPI.d ./Core/Src/FileSystemAPI.o ./Core/Src/FileSystemAPI.su ./Core/Src/cfg_files.cyclo ./Core/Src/cfg_files.d ./Core/Src/cfg_files.o ./Core/Src/cfg_files.su ./Core/Src/datetime.cyclo ./Core/Src/datetime.d ./Core/Src/datetime.o ./Core/Src/datetime.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/lfs_w25qflash.cyclo ./Core/Src/lfs_w25qflash.d ./Core/Src/lfs_w25qflash.o ./Core/Src/lfs_w25qflash.su ./Core/Src/logger.cyclo ./Core/Src/logger.d ./Core/Src/logger.o ./Core/Src/logger.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/modbus_client.cyclo ./Core/Src/modbus_client.d ./Core/Src/modbus_client.o ./Core/Src/modbus_client.su ./Core/Src/modbus_server.cyclo ./Core/Src/modbus_server.d ./Core/Src/modbus_server.o ./Core/Src/modbus_server.su ./Core/Src/rtc.cyclo ./Core/Src/rtc.d ./Core/Src/rtc.o ./Core/Src/rtc.su ./Core/Src/sntp_client.cyclo ./Core/Src/sntp_client.d ./Core/Src/sntp_client.o ./Core/Src/sntp_client.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_hal_timebase_tim.cyclo ./Core/Src/stm32f4xx_hal_timebase_tim.d ./Core/Src/stm32f4xx_hal_timebase_tim.o ./Core/Src/stm32f4xx_hal_timebase_tim.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

