################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AStar.cpp \
../Main.cpp \
../Node.cpp \
../Player.cpp \
../Position.cpp \
../Wall.cpp 

OBJS += \
./AStar.o \
./Main.o \
./Node.o \
./Player.o \
./Position.o \
./Wall.o 

CPP_DEPS += \
./AStar.d \
./Main.d \
./Node.d \
./Player.d \
./Position.d \
./Wall.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


