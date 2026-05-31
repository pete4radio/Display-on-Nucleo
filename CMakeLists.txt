cmake_minimum_required(VERSION 3.22)

project(Display_Migration C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ── MCU flags (shared by compiler and linker) ──────────────────────────────
set(MCU_FLAGS -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard)

# ── Application source files ───────────────────────────────────────────────
set(CORE_SOURCES
    Core/Src/main.c
    Core/Src/adc.c
    Core/Src/can.c
    Core/Src/comp.c
    Core/Src/gpio.c
    Core/Src/i2c.c
    Core/Src/lcd_touch.c
    Core/Src/printf.c
    Core/Src/sai.c
    Core/Src/sdmmc.c
    Core/Src/spi.c
    Core/Src/stm32l4xx_hal_msp.c
    Core/Src/stm32l4xx_it.c
    Core/Src/syscalls.c
    Core/Src/sysmem.c
    Core/Src/system_stm32l4xx.c
    Core/Src/tim.c
    Core/Src/usart.c
    Core/Src/usb_otg.c
    Core/Src/Adafruit_GFX.cpp
    Core/Src/Adafruit_ILI9341_Parallel.cpp
    Core/Src/mock_ili9341_demo.cpp
    Core/Startup/startup_stm32l4r5zitxp.s
)

# HAL Driver sources — stable ST-provided library, glob is appropriate
file(GLOB HAL_SOURCES Drivers/STM32L4xx_HAL_Driver/Src/*.c)

# ── Executable target ──────────────────────────────────────────────────────
add_executable(${PROJECT_NAME}.elf ${CORE_SOURCES} ${HAL_SOURCES})

target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
    STM32L4R5xx
    USE_HAL_DRIVER
    $<$<CONFIG:Debug>:DEBUG>
    $<$<COMPILE_LANGUAGE:CXX>:ARDUINO=10800>
)

target_include_directories(${PROJECT_NAME}.elf PRIVATE
    Core/Inc
    Drivers/STM32L4xx_HAL_Driver/Inc
    Drivers/STM32L4xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32L4xx/Include
    Drivers/CMSIS/Include
    Adafruit_GFX_Library
)

target_compile_options(${PROJECT_NAME}.elf PRIVATE
    ${MCU_FLAGS}
    -Wall
    -ffunction-sections
    -fdata-sections
    $<$<CONFIG:Debug>:-Og -g3>
    $<$<CONFIG:Release>:-O2>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions -fno-rtti>
)

target_link_options(${PROJECT_NAME}.elf PRIVATE
    ${MCU_FLAGS}
    -T${CMAKE_CURRENT_SOURCE_DIR}/STM32L4R5ZITXP_FLASH.ld
    --specs=nano.specs
    --specs=nosys.specs
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map
    -Wl,--start-group -lc -lm -Wl,--end-group
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
    COMMENT "Binary size:"
)
