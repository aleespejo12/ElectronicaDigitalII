################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Ejerciciodeclase.c \
../src/HelloWorldLPC1769.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c 

C_DEPS += \
./src/Ejerciciodeclase.d \
./src/HelloWorldLPC1769.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d 

OBJS += \
./src/Ejerciciodeclase.o \
./src/HelloWorldLPC1769.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"/Users/ale/Documents/MCUXpressoIDE_11.10.0_3148/workspace/HelloWorldLPC1769/inc" -I"/Users/ale/Documents/MCUXpressoIDE_11.10.0_3148/workspace/CMSISv2p00_LPC17xx/inc" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Ejerciciodeclase.d ./src/Ejerciciodeclase.o ./src/HelloWorldLPC1769.d ./src/HelloWorldLPC1769.o ./src/cr_startup_lpc175x_6x.d ./src/cr_startup_lpc175x_6x.o ./src/crp.d ./src/crp.o

.PHONY: clean-src

