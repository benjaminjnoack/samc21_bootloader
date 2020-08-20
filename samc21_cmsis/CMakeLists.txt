cmake_minimum_required(VERSION 3.17)

include(${CMAKE_CURRENT_SOURCE_DIR}/toolchain-cortex-m0+.cmake)

project(samc21_cmsis_gcc C)

set(CMAKE_C_STANDARD 99)

include_directories(
        CMSIS/
        CMSIS/Core
        CMSIS/Core/Include
        CMSIS/samc21
        CMSIS/samc21/include
        CMSIS/samc21/include/component
        CMSIS/samc21/include/pio
        CMSIS/samc21/include/instance
        CMSIS/samc21/gcc
        CMSIS/samc21/gcc/gcc
)