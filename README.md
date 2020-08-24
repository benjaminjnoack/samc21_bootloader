**Contents**

* `gcc` Atmel CMSIS linker scripts
* `samc21_cmsis` [subtree](https://github.com/benjaminjnoack/samc21_cmsis)
* `CMakeLists.txt` build script
* `atmel_samc21_xplained_pro.cfg` OpenOCD config file


**TODO**

* boot application
    * run the boot application handler on a button press?
* validate application
    * the `magic` should a four letter (32 bit) word, like "TECH" or "SHOT" ...could be two words...
* announce version
    * read from memory
    * communicate over network
* firmware update
    * download image over network (error handling checksums)
    * flash image (image checksum)
    
