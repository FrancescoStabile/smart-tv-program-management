################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SmartTVProject.c \
../src/funzioni_costanti.c 

C_DEPS += \
./src/SmartTVProject.d \
./src/funzioni_costanti.d 

OBJS += \
./src/SmartTVProject.o \
./src/funzioni_costanti.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/SmartTVProject.d ./src/SmartTVProject.o ./src/funzioni_costanti.d ./src/funzioni_costanti.o

.PHONY: clean-src

