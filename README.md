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
    * build
        * build bootloader separately, uses this version info
        * build application, uses app's info to fill in these known values
        * bootloader checks app
        * bootloader should only be able to check it's own revision
        when updating the bootloader is supported
        * start with a PRE_BUILD shell script that outputs the filled in template
        * maybe JUST the checksum need be added to the image after the fact???
        
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

