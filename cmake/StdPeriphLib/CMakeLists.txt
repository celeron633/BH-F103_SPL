cmake_minimum_required(VERSION 3.22)

project(StdPeriphLib)
add_library(StdPeriphLib INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(StdPeriphLib INTERFACE 
    STM32F10X_HD
    USE_STDPERIPH_DRIVER
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(StdPeriphLib INTERFACE
    ../../Boot
    ../../FwLib
    ../../User
)

target_sources(StdPeriphLib INTERFACE
    ../../Boot/startup_stm32f10x_hd.s
    ../../Boot/system_stm32f10x.c
    ../../FwLib/core_cm3.c
    ../../FwLib/misc.c
    ../../FwLib/stm32f10x_adc.c
    ../../FwLib/stm32f10x_bkp.c
    ../../FwLib/stm32f10x_can.c
    ../../FwLib/stm32f10x_cec.c
    ../../FwLib/stm32f10x_crc.c
    ../../FwLib/stm32f10x_dac.c
    ../../FwLib/stm32f10x_dbgmcu.c
    ../../FwLib/stm32f10x_dma.c
    ../../FwLib/stm32f10x_exti.c
    ../../FwLib/stm32f10x_flash.c
    ../../FwLib/stm32f10x_fsmc.c
    ../../FwLib/stm32f10x_gpio.c
    ../../FwLib/stm32f10x_i2c.c
    ../../FwLib/stm32f10x_iwdg.c
    ../../FwLib/stm32f10x_pwr.c
    ../../FwLib/stm32f10x_rcc.c
    ../../FwLib/stm32f10x_rtc.c
    ../../FwLib/stm32f10x_sdio.c
    ../../FwLib/stm32f10x_spi.c
    ../../FwLib/stm32f10x_tim.c
    ../../FwLib/stm32f10x_usart.c
    ../../FwLib/stm32f10x_wwdg.c
    ../../User/bsp_led.c
    ../../User/main.c
    ../../User/stm32f10x_it.c
)

target_link_directories(StdPeriphLib INTERFACE
)

target_link_libraries(StdPeriphLib INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


