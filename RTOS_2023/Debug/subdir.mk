################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO.c \
../INT.c \
../TIMER.c \
../main.c 

OBJS += \
./DIO.o \
./INT.o \
./TIMER.o \
./main.o 

C_DEPS += \
./DIO.d \
./INT.d \
./TIMER.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\Bio-Medical materials\Faculty of Engneering\Forth year\Advanced Embedded\project\New____\RTOS-car-indicator-proect\RTOS_2023\Source\portable\GCC\ATMega323" -I"E:\Bio-Medical materials\Faculty of Engneering\Forth year\Advanced Embedded\project\New____\RTOS-car-indicator-proect\RTOS_2023\Source\include" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

