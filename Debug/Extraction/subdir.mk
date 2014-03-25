################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Extraction/ColorLayoutExtraction.cpp \
../Extraction/ColorSpaceExtraction.cpp \
../Extraction/ColorStructureExtraction.cpp \
../Extraction/ContourShapeExtraction.cpp \
../Extraction/DominantColorExtraction.cpp \
../Extraction/EdgeHistExtraction.cpp \
../Extraction/FaceRecognitionExtraction.cpp \
../Extraction/GoFGoPColorExtraction.cpp \
../Extraction/HomoTextureExtraction.cpp \
../Extraction/RegionShapeExtraction.cpp \
../Extraction/ScalableColorExtraction.cpp \
../Extraction/homo_texture_extractor.cpp 

C_SRCS += \
../Extraction/imgutil.c 

OBJS += \
./Extraction/ColorLayoutExtraction.o \
./Extraction/ColorSpaceExtraction.o \
./Extraction/ColorStructureExtraction.o \
./Extraction/ContourShapeExtraction.o \
./Extraction/DominantColorExtraction.o \
./Extraction/EdgeHistExtraction.o \
./Extraction/FaceRecognitionExtraction.o \
./Extraction/GoFGoPColorExtraction.o \
./Extraction/HomoTextureExtraction.o \
./Extraction/RegionShapeExtraction.o \
./Extraction/ScalableColorExtraction.o \
./Extraction/homo_texture_extractor.o \
./Extraction/imgutil.o 

C_DEPS += \
./Extraction/imgutil.d 

CPP_DEPS += \
./Extraction/ColorLayoutExtraction.d \
./Extraction/ColorSpaceExtraction.d \
./Extraction/ColorStructureExtraction.d \
./Extraction/ContourShapeExtraction.d \
./Extraction/DominantColorExtraction.d \
./Extraction/EdgeHistExtraction.d \
./Extraction/FaceRecognitionExtraction.d \
./Extraction/GoFGoPColorExtraction.d \
./Extraction/HomoTextureExtraction.d \
./Extraction/RegionShapeExtraction.d \
./Extraction/ScalableColorExtraction.d \
./Extraction/homo_texture_extractor.d 


# Each subdirectory must supply rules for building sources it contributes
Extraction/%.o: ../Extraction/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/include/python2.7 -I"/home/algomorph/Factory/pycvmpeg7" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Extraction/%.o: ../Extraction/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/python2.7 -I"/home/algomorph/Factory/pycvmpeg7" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


