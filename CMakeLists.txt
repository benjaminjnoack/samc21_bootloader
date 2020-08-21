cmake_minimum_required(VERSION 3.17)

include(${CMAKE_CURRENT_SOURCE_DIR}/samc21_cmsis/samc21_cmsis.cmake)

project(samc21_bootloader)
set(CMAKE_VERBOSE_MAKEFILE true)
add_executable(${PROJECT_NAME})

add_definitions(-D__SAMC21J18A__)

target_sources(${PROJECT_NAME} PUBLIC
        src/main.cpp
        $<TARGET_OBJECTS:samc21_cmsis>
        )

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-lm,-gc-sections,--print-memory-usage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-T ${CMAKE_CURRENT_SOURCE_DIR}/gcc/bootloader.ld -L ${CMAKE_CURRENT_SOURCE_DIR}/gcc")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.Map")

set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMENT "output bin"
        COMMAND ${OBJCOPY} -O binary "${PROJECT_NAME}.elf" "${PROJECT_NAME}.bin"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMENT "output hex"
        COMMAND ${OBJCOPY} -O ihex -R .eeprom -R .fuse -R .lock -R .signature "${PROJECT_NAME}.elf" "${PROJECT_NAME}.hex"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMENT "output lss"
        COMMAND ${NM} --demangle --numeric-sort "${PROJECT_NAME}.elf" > "${PROJECT_NAME}.lss"
        )
