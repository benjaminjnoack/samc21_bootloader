# Contents

* `Core` [ARM CMSIS 5.4.0](http://packs.download.atmel.com/)
* `gcc` linker scripts
* `samc21` [Atmel SAMC21 CMSIS Pack 1.2.176](http://packs.download.atmel.com/)
    * `gcc` [CMSIS Core Device Templates](https://arm-software.github.io/CMSIS_5/Core/html/templates_pg.html)
    * `include` device headers files
* `src` source code
    * `crc.*` CRC-32 functions
    * `gnu_build_id.h` GNU Build ID struct
    * `main.cpp` application code
    * `memory_map.h` `extern` declarations for accessing linker defined variables
* `ATSAMC21J18A.svd` [CMSIS SVD](https://arm-software.github.io/CMSIS_5/SVD/html/index.html) (taken from CMSIS pack)
* `CMakeLists.txt` build script
* `image.sh` shell script for creating application image header

**TODO**

* crc
    * hard coded lookup table
    * return crc instead of pass pointer
* "hard" break into boot loader
    * power on while button is pressed
* detect boot loops
    * shared memory
    * reset reason register?
* firmware update
    * download over CAN network
    * flash image

# Hardware

* Microchip [SAMC21 Xplained Pro](https://www.microchip.com/DevelopmentTools/ProductDetails/ATSAMD21-XPRO) development board
    * [SAMC Data Sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/SAMC20_C21_Family_Data_Sheet_DS60001479D.pdf)
    * [User Guide](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42460-SAM-C21-Xplained-Pro_User-Guide.pdf)
* Segger [J-Link](https://www.segger.com/products/debug-probes/j-link/) probe, (tested with J-Link SAM-ICE, J-Link EDU, and J-Link mini)

# Software

## GCC

Download and extract the latest [arm-gcc](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) toolchain.
Add the compiler installation's `bin` directory to your `$PATH`.
CLion's shell requires the `bin` dir be appended to the PATH in `/etc/environment`.

## Segger

### J-Link

Download and install the latest [J-Link Software and Documentation Pack](https://www.segger.com/downloads/jlink)

_NOTE: the executables installed in /usr/bin are actually symlinks to /opt/SEGGER. The docs are in there too_

### Ozone

Download and install [Segger Ozone](https://www.segger.com/downloads/jlink#Ozone) for your platform.

_NOTE: Ozone is used because the peripheral viewer in CLion appears buggy. Specifically, it will not show the PORT registers, which are essential for blink!_

# Setup

## Linux Dependencies

`sudo apt install build-essential xxd libarchive-zip-perl`

## CLion

### Toolchain

### Run/Debug Configuration

#### EDGB Debugger

Add a new [OpenOCD Download & Run](https://www.jetbrains.com/help/clion/openocd-support.html) Run/Debug configuration.

* **Board configuration file** `atmel_samc21_xplained_pro.cfg`

#### J-Link Debugger

Add a new [Embedded GDB Server](https://www.jetbrains.com/help/clion/embedded-gdb-server.html) Run/Debug configuration.

* **'target remote' args** `localhost:2331`
* **GDB Server** `JLinkGDBServer`
* **GDB Server args** `-device ATSAMC21J18A -endian little -if SWD -speed 2000`

