cmake_minimum_required(VERSION 3.17)

include(${CMAKE_CURRENT_LIST_DIR}/toolchain-cortex-m0+.cmake)

project(samc21_cmsis_gcc C)

set(CMAKE_C_STANDARD 99)

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${CMAKE_CURRENT_LIST_DIR}/Core
		${CMAKE_CURRENT_LIST_DIR}/Core/Include
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/include/component
		${CMAKE_CURRENT_LIST_DIR}/include/pio
		${CMAKE_CURRENT_LIST_DIR}/include/instance
)

add_library(samc21_cmsis OBJECT
		${CMAKE_CURRENT_LIST_DIR}/gcc/system_samc21.c
		${CMAKE_CURRENT_LIST_DIR}/gcc/startup_samc21.c
		)
