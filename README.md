**Contents**

* `gcc` Atmel CMSIS linker scripts
* `samc21_cmsis` [subtree](https://github.com/benjaminjnoack/samc21_cmsis)
* `CMakeLists.txt` build script
* `atmel_samc21_xplained_pro.cfg` OpenOCD config file

**TODO**

* validate application
    * timestamp
    * hostname
    * user
    * version (git tag)
    * commit hash
    * dirty/clean build
    * magic
        * bootloader "tech"
        * app "shot"
    * checksum
        * CRC
        * build ID SHA1 or MD5
    * build
        * build bootloader separately, uses this version info
        * build application, uses app's info to fill in these known values
        * bootloader checks app, (checks itself...?)
        * when the bootloader is a subtree,
        and you want the bootloader to have it's own revision information,
        then it would actually be easier if the bootloader were a submodule.
        But we're not going down that road again!
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

