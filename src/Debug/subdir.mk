################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../E.cpp \
../Log.cpp \
../MultExpression.cpp \
../Pi.cpp \
../Radical.cpp \
../SmartInteger.cpp \
../SumExpression.cpp \
../main.cpp 

OBJS += \
./E.o \
./Log.o \
./MultExpression.o \
./Pi.o \
./Radical.o \
./SmartInteger.o \
./SumExpression.o \
./main.o 

CPP_DEPS += \
./E.d \
./Log.d \
./MultExpression.d \
./Pi.d \
./Radical.d \
./SmartInteger.d \
./SumExpression.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


