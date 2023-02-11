################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/HAL2/Button_Handler.c 

OBJS += \
./Source/HAL2/Button_Handler.o 

C_DEPS += \
./Source/HAL2/Button_Handler.d 


# Each subdirectory must supply rules for building sources it contributes
Source/HAL2/%.o: ../Source/HAL2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\RTOS_2023\RTOS-car-indicator-proect\RTOS_2023\Source\portable\GCC\ATMega323" -I"D:\RTOS_2023\RTOS-car-indicator-proect\RTOS_2023\Source\include" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


