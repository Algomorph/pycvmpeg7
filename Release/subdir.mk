################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Convert.cpp \
../Feature.cpp \
../Frame.cpp \
../PythonPort.cpp 

OBJS += \
./Convert.o \
./Feature.o \
./Frame.o \
./PythonPort.o 

CPP_DEPS += \
./Convert.d \
./Feature.d \
./Frame.d \
./PythonPort.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I"/home/algomorph/Garage/MPEG7FexLib_src_OpenCV22" -I/usr/include/python2.7 -O3 -Wall -c -fmessage-length=0 -std=c++0x -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


