################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CSInternalRoutines.cpp \
../Convert.cpp \
../Feature.cpp \
../Frame.cpp \
../PyFrame.cpp \
../PythonPort.cpp 

OBJS += \
./CSInternalRoutines.o \
./Convert.o \
./Feature.o \
./Frame.o \
./PyFrame.o \
./PythonPort.o 

CPP_DEPS += \
./CSInternalRoutines.d \
./Convert.d \
./Feature.d \
./Frame.d \
./PyFrame.d \
./PythonPort.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/include/python2.7 -I"/home/algomorph/Factory/pycvmpeg7" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


