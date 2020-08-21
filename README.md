**Contents**

* `ATSAMC21J18A.svd` CMSIS register definition XML
* `Core` ARM Cortex M0+ headers
* `samc21` Atmel CMSIS headers, `startup_<device>.c`, `system_<device>.c`, and linker scripts
* `samc21_cmsis.cmake` CMake object library file
* `toolchain-cortex-m0+.cmake` CMake toolchain file

**TODO**

* `target_include_directories`
* `startup_<device>.c`
    * same code used by bootloader, app, and updater
    * symbols are not application specific and will be defined in linker script
* `system_<device>.c`
    * is there any common initialization (clocks?)
