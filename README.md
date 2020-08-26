# Installation

## CMSIS

* [CMSIS SVD](https://arm-software.github.io/CMSIS_5/SVD/html/index.html)
* [Microchip Packs](http://packs.download.atmel.com/)
* [CMSIS Core Device Templates](https://arm-software.github.io/CMSIS_5/Core/html/templates_pg.html)

# Hardware

* Microchip [SAMC21 Xplained Pro](https://www.microchip.com/DevelopmentTools/ProductDetails/ATSAMD21-XPRO) development board
    * [SAMC Data Sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/SAMC20_C21_Family_Data_Sheet_DS60001479D.pdf)
    * [User Guide](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42460-SAM-C21-Xplained-Pro_User-Guide.pdf)
* Segger [J-Link](https://www.segger.com/products/debug-probes/j-link/) probe, (tested with J-Link EDU and J-Link mini)

# Installation

## GCC

Download and extract the latest [arm-gcc](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) toolchain.
Add the compiler installation's `bin` directory to your `$PATH`.
CLion's shell requires the `bin` dir be appended to the PATH in `/etc/environment`.

## Segger

### J-Link

Download and install the latest [J-Link Software and Documentation Pack](https://www.segger.com/downloads/jlink)

_NOTE: the executables installed in /usr/bin are actually symlinks to /opt/SEGGER. The docs are in there too_

### Ozone

_NOTE: Ozone is used because the peripheral viewer in CLion appears buggy. Specifically, it will not show the PORT registers, which are essential for blink!_

Download and install [Segger Ozone](https://www.segger.com/downloads/jlink#Ozone) for your platform.

# Setup

## CLion Toolchain

Add a CLion [toolchain](https://www.jetbrains.com/help/clion/toolchains.html).
Set the **C Compiler**, **C++ Compiler**, and **GDB** from the `bin` dir of the downloaded `arm-gcc` toolchain.
If the `bin` directory of the `arm-gcc` toolchain is in your `$PATH`, then you can just specify `arm-none-eabi-gcc`, etc...,
instead of the absolute path.

## CLion Run/Debug

### EDGB Debugger

Add a new [OpenOCD Download & Run](https://www.jetbrains.com/help/clion/openocd-support.html) Run/Debug configuration.

* **Board configuration file** `atmel_samc21_xplained_pro.cfg`

### J-Link Debugger

Add a new [Embedded GDB Server](https://www.jetbrains.com/help/clion/embedded-gdb-server.html) Run/Debug configuration.

* **'target remote' args** `localhost:2331`
* **GDB Server** `JLinkGDBServer`
* **GDB Server args** `-device ATSAMC21J18A -endian little -if SWD -speed 2000`

**Contents**

* `gcc` Atmel CMSIS linker scripts
* `samc21_cmsis` [subtree](https://github.com/benjaminjnoack/samc21_cmsis)
* `CMakeLists.txt` build script
* `atmel_samc21_xplained_pro.cfg` OpenOCD config file

**TODO**

* validate application
    * version (git tag)
        * 1.0.0
    * checksum
        * CRC
        * build ID SHA1 or MD5
            * all bins and hexs would inherit
            * elf would need to be stripped of all NOLOAD sections
                * "When objcopy generates a raw binary file, it will essentially produce
                   a memory dump of the contents of the input object file. All symbols and relocation infor-
                   mation will be discarded."
            * still not sure it would line up with bin sent over CAN
            * where to put it
                * store the build ID in the first word - doesn't work for bootloader
                * anywhere else means bootloader would have to ignore that location...I think
        * `cksum` the bin
            * store the checksum in the first word
                * doesn't work for bootloader
                * worry about how to support updating the bootloader when that becomes a requirement
            * anywhere else means bootloader would have to ignore that location...I think
            AND you would have to write a custom CRC on the build machine that would ignore that location
            otherwise it would run a checksum of an image...containing itself!
* "hard" break into bootloader to avoid loops
* detect boot loops
    * wait for new software
    * shared memory region to increment/clear counter
    * alternatively, check a reset condition register if available?
* announce version
    * read from memory
    * communicate over network
* firmware update
    * should there be an old version of the app "baked in" to the bootloader for re-flashing upon image validation failure?
    * download image over network (error handling checksums)
    * flash image (image checksum)

