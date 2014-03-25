################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Descriptors/ColorLayout.cpp \
../Descriptors/ColorQuant.cpp \
../Descriptors/ColorSpace.cpp \
../Descriptors/ColorStructure.cpp \
../Descriptors/ContourShape.cpp \
../Descriptors/DominantColor.cpp \
../Descriptors/EdgeHist.cpp \
../Descriptors/FaceRecognition.cpp \
../Descriptors/HomoTexture.cpp \
../Descriptors/RegionShape.cpp \
../Descriptors/ScalableColor.cpp 

OBJS += \
./Descriptors/ColorLayout.o \
./Descriptors/ColorQuant.o \
./Descriptors/ColorSpace.o \
./Descriptors/ColorStructure.o \
./Descriptors/ContourShape.o \
./Descriptors/DominantColor.o \
./Descriptors/EdgeHist.o \
./Descriptors/FaceRecognition.o \
./Descriptors/HomoTexture.o \
./Descriptors/RegionShape.o \
./Descriptors/ScalableColor.o 

CPP_DEPS += \
./Descriptors/ColorLayout.d \
./Descriptors/ColorQuant.d \
./Descriptors/ColorSpace.d \
./Descriptors/ColorStructure.d \
./Descriptors/ContourShape.d \
./Descriptors/DominantColor.d \
./Descriptors/EdgeHist.d \
./Descriptors/FaceRecognition.d \
./Descriptors/HomoTexture.d \
./Descriptors/RegionShape.d \
./Descriptors/ScalableColor.d 


# Each subdirectory must supply rules for building sources it contributes
Descriptors/%.o: ../Descriptors/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/include/python2.7 -I"/home/algomorph/Factory/pycvmpeg7" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


