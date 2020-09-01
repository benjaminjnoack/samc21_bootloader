cmake_minimum_required(VERSION 3.16.3)

add_custom_command(OUTPUT crc_table
		COMMENT "building crc_table"
		COMMAND gcc -I${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/crc_table_generator.c -o crc_table)

add_custom_command(OUTPUT crc_table.h
		COMMENT "generating crc table header"
		COMMAND ${CMAKE_BINARY_DIR}/crc_table > ${CMAKE_BINARY_DIR}/crc_table.h
		DEPENDS crc_table
		)
