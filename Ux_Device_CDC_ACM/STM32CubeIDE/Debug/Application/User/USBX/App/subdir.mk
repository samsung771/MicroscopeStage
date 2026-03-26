################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/samdl/STM32CubeIDE/workspace_1.19.0/Ux_Device_CDC_ACM/USBX/App/app_usbx_device.c \
C:/Users/samdl/STM32CubeIDE/workspace_1.19.0/Ux_Device_CDC_ACM/USBX/App/ux_device_cdc_acm.c \
C:/Users/samdl/STM32CubeIDE/workspace_1.19.0/Ux_Device_CDC_ACM/USBX/App/ux_device_descriptors.c 

OBJS += \
./Application/User/USBX/App/app_usbx_device.o \
./Application/User/USBX/App/ux_device_cdc_acm.o \
./Application/User/USBX/App/ux_device_descriptors.o 

C_DEPS += \
./Application/User/USBX/App/app_usbx_device.d \
./Application/User/USBX/App/ux_device_cdc_acm.d \
./Application/User/USBX/App/ux_device_descriptors.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/USBX/App/app_usbx_device.o: C:/Users/samdl/STM32CubeIDE/workspace_1.19.0/Ux_Device_CDC_ACM/USBX/App/app_usbx_device.c Application/User/USBX/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32C071xx -c -I../../Core/Inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32C0xx_HAL_Driver/Inc -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32C0xx/Include -I../../Middlewares/ST/threadx/ports/cortex_m0/gnu/inc -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32C0xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/USBX/App/ux_device_cdc_acm.o: C:/Users/samdl/STM32CubeIDE/workspace_1.19.0/Ux_Device_CDC_ACM/USBX/App/ux_device_cdc_acm.c Application/User/USBX/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32C071xx -c -I../../Core/Inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32C0xx_HAL_Driver/Inc -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32C0xx/Include -I../../Middlewares/ST/threadx/ports/cortex_m0/gnu/inc -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32C0xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/USBX/App/ux_device_descriptors.o: C:/Users/samdl/STM32CubeIDE/workspace_1.19.0/Ux_Device_CDC_ACM/USBX/App/ux_device_descriptors.c Application/User/USBX/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32C071xx -c -I../../Core/Inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32C0xx_HAL_Driver/Inc -I../../Middlewares/ST/threadx/common/inc -I../../Drivers/CMSIS/Device/ST/STM32C0xx/Include -I../../Middlewares/ST/threadx/ports/cortex_m0/gnu/inc -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32C0xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-User-2f-USBX-2f-App

clean-Application-2f-User-2f-USBX-2f-App:
	-$(RM) ./Application/User/USBX/App/app_usbx_device.cyclo ./Application/User/USBX/App/app_usbx_device.d ./Application/User/USBX/App/app_usbx_device.o ./Application/User/USBX/App/app_usbx_device.su ./Application/User/USBX/App/ux_device_cdc_acm.cyclo ./Application/User/USBX/App/ux_device_cdc_acm.d ./Application/User/USBX/App/ux_device_cdc_acm.o ./Application/User/USBX/App/ux_device_cdc_acm.su ./Application/User/USBX/App/ux_device_descriptors.cyclo ./Application/User/USBX/App/ux_device_descriptors.d ./Application/User/USBX/App/ux_device_descriptors.o ./Application/User/USBX/App/ux_device_descriptors.su

.PHONY: clean-Application-2f-User-2f-USBX-2f-App

