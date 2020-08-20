cmake_minimum_required(VERSION 3.17)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(OBJCOPY arm-none-eabi-objcopy)
set(NM arm-none-eabi-nm)

set(COMMON_FLAGS "-mcpu=cortex-m0plus -mthumb -mthumb-interwork -ffunction-sections -fdata-sections -fno-common -specs=\"nosys.specs\"")

set(CMAKE_C_FLAGS_INIT ${COMMON_FLAGS})
set(CMAKE_C_FLAGS_RELEASE "-Os")
set(CMAKE_C_FLAGS_DEBUG "-Og -g -gdwarf-3 -gstrict-dwarf")

set(CMAKE_CXX_FLAGS_INIT ${COMMON_FLAGS})
set(CMAKE_CXX_FLAGS_RELEASE "-Os")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g -gdwarf-3 -gstrict-dwarf")
