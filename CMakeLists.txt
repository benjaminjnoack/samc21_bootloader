cmake_minimum_required(VERSION 3.17)

project(samc21_bootloader)

set(CMAKE_CXX_STANDARD 17)

add_executable(samc21_bootloader)

target_sources(${PROJECT_NAME} PUBLIC
        src/main.cpp)