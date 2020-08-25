**Contents**

* `gcc` Atmel CMSIS linker scripts
* `samc21_cmsis` [subtree](https://github.com/benjaminjnoack/samc21_cmsis)
* `CMakeLists.txt` build script
* `atmel_samc21_xplained_pro.cfg` OpenOCD config file


**TODO**

* validate application
    * the `magic` should a four letter (32 bit) word, like "TECH" or "SHOT" ...could be two words...
* announce version
    * read from memory
        * `gcc` build id
    * communicate over network
* firmware update
    * should there be an old version of the app "baked in" to the bootloader for re-flashing upon image validation failure?
    * download image over network (error handling checksums)
    * flash image (image checksum)
    