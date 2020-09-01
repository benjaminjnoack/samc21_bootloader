cmake_minimum_required(VERSION 3.16.3)

include(${CMAKE_CURRENT_LIST_DIR}/samc21/samc21.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/src/crc/crc_table.cmake)
project(samc21_bootloader)
set(CMAKE_VERBOSE_MAKEFILE true)
add_executable(${PROJECT_NAME})

add_definitions(-D__SAMC21J18A__)

include_directories(
		${CMAKE_BINARY_DIR}
		${CMAKE_CURRENT_LIST_DIR}/src
)

target_sources(${PROJECT_NAME} PUBLIC
		image.c
		image.h
		crc_table.h
		src/crc/crc.c
		src/crc/crc.h
		${CMAKE_CURRENT_LIST_DIR}/src/gnu_build_id.h
		${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/memory_map.h
		$<TARGET_OBJECTS:samc21_cmsis>
		)

# setting CMAKE_EXE_LINKER_FLAGS will be combined with blink's linker options (conflicting linker scripts)
target_link_options(${PROJECT_NAME} PRIVATE LINKER:-lm,-gc-sections,--print-memory-usage,--build-id=md5)
target_link_options(${PROJECT_NAME} PRIVATE LINKER:-L ${CMAKE_CURRENT_LIST_DIR}/gcc)
target_link_options(${PROJECT_NAME} PRIVATE LINKER:-T ${CMAKE_CURRENT_LIST_DIR}/gcc/bootloader.ld)
target_link_options(${PROJECT_NAME} PRIVATE LINKER:-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map)

set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")

add_custom_command(OUTPUT image.c image.h
		COMMENT "generating image header"
		COMMAND ${CMAKE_CURRENT_LIST_DIR}/image.sh ${CMAKE_BINARY_DIR}
		)

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#		COMMENT "output assembly"
#		COMMAND ${OBJDUMP} -d ${PROJECT_NAME}.elf > ${PROJECT_NAME}.s
#		COMMAND ${OBJDUMP} -D --dwarf=follow-links ${PROJECT_NAME}.elf > ${PROJECT_NAME}.S
#		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#		BYPRODUCTS ${PROJECT_NAME}.s ${PROJECT_NAME}.S
#		)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMENT "output ${PROJECT_NAME} bins"
		COMMAND ${OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
		COMMAND ${OBJCOPY} -O binary --pad-to=0x4000 --gap-fill=0xFF ${PROJECT_NAME}.elf ${PROJECT_NAME}.padded.bin
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		BYPRODUCTS ${PROJECT_NAME}.bin ${PROJECT_NAME}.padded.bin
		)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMENT "output ${PROJECT_NAME} lss"
		COMMAND ${NM} -S --demangle --numeric-sort ${PROJECT_NAME}.elf > ${PROJECT_NAME}.lss
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		BYPRODUCTS ${PROJECT_NAME}.lss
		)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMENT "Build ID"
		DEPENDS ${PROJECT_NAME}.elf
		COMMAND ${READELF} -n ${PROJECT_NAME}.elf | grep \"Build ID:\" | cut -d \\: -f 2 | sed 's/ //'
		)


# TODO for reference
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMENT "output ${PROJECT_NAME} hex"
#        COMMAND ${OBJCOPY} -O ihex -R .eeprom -R .fuse -R .lock -R .signature ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#        BYPRODUCTS "${PROJECT_NAME}.hex"
#        )

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMENT "output ${PROJECT_NAME} S-records"
#        COMMAND ${OBJCOPY} -O srec ${PROJECT_NAME}.elf ${PROJECT_NAME}.srec
#        COMMAND ${OBJCOPY} -O srec --pad-to=0x4000 --gap-fill=0xFF ${PROJECT_NAME}.elf ${PROJECT_NAME}.padded.srec
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#        BYPRODUCTS ${PROJECT_NAME}.srec ${PROJECT_NAME}.padded.srec
#        )
