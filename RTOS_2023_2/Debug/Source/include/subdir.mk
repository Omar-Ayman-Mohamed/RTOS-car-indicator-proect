################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/include/Btn_Handler.c \
../Source/include/DIO.c \
../Source/include/LED.c \
../Source/include/PWM.c 

OBJS += \
./Source/include/Btn_Handler.o \
./Source/include/DIO.o \
./Source/include/LED.o \
./Source/include/PWM.o 

C_DEPS += \
./Source/include/Btn_Handler.d \
./Source/include/DIO.d \
./Source/include/LED.d \
./Source/include/PWM.d 


# Each subdirectory must supply rules for building sources it contributes
Source/include/%.o: ../Source/include/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\wario\Downloads\RTOS_2023\Source\portable\GCC\ATMega323" -I"C:\Users\wario\Downloads\RTOS_2023\Source\include" -I"C:\Users\wario\Downloads\RTOS_2023\Source\include\HAL" -I"C:\Users\wario\Downloads\RTOS_2023\Source\include\MCAL" -I"C:\Users\wario\Downloads\RTOS_2023\Source" -I"C:\Users\wario\Downloads\RTOS_2023\Source\include" -I"C:\Users\wario\Downloads\RTOS_2023\Source\include\HAL" -I"C:\Users\wario\Downloads\RTOS_2023\Source\include\MCAL" -I"C:\Users\wario\Downloads\RTOS_2023\Source\include" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


