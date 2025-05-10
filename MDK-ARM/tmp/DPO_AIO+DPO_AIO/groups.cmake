# groups.cmake

# group Application/MDK-ARM
add_library(Group_Application_MDK-ARM OBJECT
  "${SOLUTION_ROOT}/startup_stm32g474xx.s"
)
target_include_directories(Group_Application_MDK-ARM PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Application_MDK-ARM PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Application_MDK-ARM_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Application_MDK-ARM_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Application_MDK-ARM PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Application_MDK-ARM PUBLIC
  Group_Application_MDK-ARM_ABSTRACTIONS
)
set(COMPILE_DEFINITIONS
  __MICROLIB
  STM32G474xx
  _RTE_
)
cbuild_set_defines(AS_ARM COMPILE_DEFINITIONS)
set_source_files_properties("${SOLUTION_ROOT}/startup_stm32g474xx.s" PROPERTIES
  COMPILE_FLAGS "${COMPILE_DEFINITIONS}"
)
set_source_files_properties("${SOLUTION_ROOT}/startup_stm32g474xx.s" PROPERTIES
  COMPILE_OPTIONS "-masm=auto"
)

# group Application/User/Core
add_library(Group_Application_User_Core OBJECT
  "${SOLUTION_ROOT}/../Core/Src/aht20.c"
  "${SOLUTION_ROOT}/../Core/Src/fonts.c"
  "${SOLUTION_ROOT}/../Core/Src/ft6336.c"
  "${SOLUTION_ROOT}/../Core/Src/mpu6050.c"
  "${SOLUTION_ROOT}/../Core/Src/MyLib.c"
  "${SOLUTION_ROOT}/../Core/Src/st7789.c"
  "${SOLUTION_ROOT}/../Core/Src/TLC5952.c"
  "${SOLUTION_ROOT}/../Core/Src/Views.c"
  "${SOLUTION_ROOT}/../Core/Src/ws2812.c"
  "${SOLUTION_ROOT}/../Core/Src/main.c"
  "${SOLUTION_ROOT}/../Core/Src/stm32g4xx_it.c"
  "${SOLUTION_ROOT}/../Core/Src/stm32g4xx_hal_msp.c"
)
target_include_directories(Group_Application_User_Core PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Application_User_Core PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Application_User_Core_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Application_User_Core_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Application_User_Core PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Application_User_Core PUBLIC
  Group_Application_User_Core_ABSTRACTIONS
)

# group Application/User/USB_Device/Target
add_library(Group_Application_User_USB_Device_Target OBJECT
  "${SOLUTION_ROOT}/../USB_Device/Target/usbd_conf.c"
)
target_include_directories(Group_Application_User_USB_Device_Target PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Application_User_USB_Device_Target PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Application_User_USB_Device_Target_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Application_User_USB_Device_Target_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Application_User_USB_Device_Target PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Application_User_USB_Device_Target PUBLIC
  Group_Application_User_USB_Device_Target_ABSTRACTIONS
)

# group Application/User/USB_Device/App
add_library(Group_Application_User_USB_Device_App OBJECT
  "${SOLUTION_ROOT}/../USB_Device/App/usb_device.c"
  "${SOLUTION_ROOT}/../USB_Device/App/usbd_desc.c"
  "${SOLUTION_ROOT}/../USB_Device/App/usbd_cdc_if.c"
)
target_include_directories(Group_Application_User_USB_Device_App PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Application_User_USB_Device_App PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Application_User_USB_Device_App_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Application_User_USB_Device_App_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Application_User_USB_Device_App PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Application_User_USB_Device_App PUBLIC
  Group_Application_User_USB_Device_App_ABSTRACTIONS
)

# group Drivers/STM32G4xx_HAL_Driver
add_library(Group_Drivers_STM32G4xx_HAL_Driver OBJECT
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pcd.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pcd_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_usb.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ramfunc.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_exti.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_comp.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dac.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dac_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_i2c.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_i2c_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_opamp.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_opamp_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_spi.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_spi_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart.c"
  "${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart_ex.c"
)
target_include_directories(Group_Drivers_STM32G4xx_HAL_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Drivers_STM32G4xx_HAL_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Drivers_STM32G4xx_HAL_Driver_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Drivers_STM32G4xx_HAL_Driver_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Drivers_STM32G4xx_HAL_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Drivers_STM32G4xx_HAL_Driver PUBLIC
  Group_Drivers_STM32G4xx_HAL_Driver_ABSTRACTIONS
)
set_source_files_properties("${SOLUTION_ROOT}/../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_comp.c" PROPERTIES
  COMPILE_OPTIONS ""
)

# group Drivers/CMSIS
add_library(Group_Drivers_CMSIS OBJECT
  "${SOLUTION_ROOT}/../Core/Src/system_stm32g4xx.c"
)
target_include_directories(Group_Drivers_CMSIS PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Drivers_CMSIS PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Drivers_CMSIS_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Drivers_CMSIS_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Drivers_CMSIS PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Drivers_CMSIS PUBLIC
  Group_Drivers_CMSIS_ABSTRACTIONS
)

# group Middlewares/USB_Device_Library
add_library(Group_Middlewares_USB_Device_Library OBJECT
  "${SOLUTION_ROOT}/../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c"
  "${SOLUTION_ROOT}/../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c"
  "${SOLUTION_ROOT}/../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c"
  "${SOLUTION_ROOT}/../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c"
)
target_include_directories(Group_Middlewares_USB_Device_Library PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Middlewares_USB_Device_Library PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Middlewares_USB_Device_Library_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Middlewares_USB_Device_Library_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Middlewares_USB_Device_Library PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Middlewares_USB_Device_Library PUBLIC
  Group_Middlewares_USB_Device_Library_ABSTRACTIONS
)
