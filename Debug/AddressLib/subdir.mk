################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AddressLib/address.c \
../AddressLib/inter.c \
../AddressLib/intra.c \
../AddressLib/nhood.c \
../AddressLib/vopio.c 

OBJS += \
./AddressLib/address.o \
./AddressLib/inter.o \
./AddressLib/intra.o \
./AddressLib/nhood.o \
./AddressLib/vopio.o 

C_DEPS += \
./AddressLib/address.d \
./AddressLib/inter.d \
./AddressLib/intra.d \
./AddressLib/nhood.d \
./AddressLib/vopio.d 


# Each subdirectory must supply rules for building sources it contributes
AddressLib/%.o: ../AddressLib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/python2.7 -I"/home/algomorph/Factory/pycvmpeg7" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


