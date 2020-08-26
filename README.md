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

