cmake_minimum_required(VERSION 3.17)

include(${CMAKE_CURRENT_LIST_DIR}/toolchain-cortex-m0+.cmake)

project(samc21_cmsis_gcc C)

set(CMAKE_C_STANDARD 99)

include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/
        ${CMAKE_CURRENT_LIST_DIR}/Core
        ${CMAKE_CURRENT_LIST_DIR}/Core/Include
        ${CMAKE_CURRENT_LIST_DIR}/samc21
        ${CMAKE_CURRENT_LIST_DIR}/samc21/include
        ${CMAKE_CURRENT_LIST_DIR}/samc21/include/component
        ${CMAKE_CURRENT_LIST_DIR}/samc21/include/pio
        ${CMAKE_CURRENT_LIST_DIR}/samc21/include/instance
        ${CMAKE_CURRENT_LIST_DIR}/samc21/gcc
        ${CMAKE_CURRENT_LIST_DIR}/samc21/gcc/gcc
)
