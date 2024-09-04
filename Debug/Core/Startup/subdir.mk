################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f407vetx.s 

OBJS += \
./Core/Startup/startup_stm32f407vetx.o 

S_DEPS += \
./Core/Startup/startup_stm32f407vetx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"/home/italo/STM32CubeIDE/workspace_1.14.0_2/STM32F4_BOARD/Middlewares/Third_Party/LittleFs" -I"/home/italo/STM32CubeIDE/workspace_1.14.0_2/STM32F4_BOARD/Middlewares/Third_Party/w25Qxx" -I"/home/italo/STM32CubeIDE/workspace_1.14.0_2/STM32F4_BOARD/Middlewares/Third_Party/Modbus" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f407vetx.d ./Core/Startup/startup_stm32f407vetx.o

.PHONY: clean-Core-2f-Startup

