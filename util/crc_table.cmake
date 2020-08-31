cmake_minimum_required(3.16.3)

add_executable(crc_table)

target_sources(
        ${CMAKE_CURRENT_LIST_DIR}/generator.c
)
