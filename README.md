**Contents**

* `gcc` Atmel CMSIS linker scripts
* `samc21_cmsis` [subtree](https://github.com/benjaminjnoack/samc21_cmsis)
* `CMakeLists.txt` build script
* `atmel_samc21_xplained_pro.cfg` OpenOCD config file


**TODO**

* boot application
    * change the LED used
    * pad the binary as a post build step
    * conditionally pad binary and jump only when a subsidiary project (otherwise just blink)
    * perhaps Ozone will be able to debug it when provided with the concatenated binary?
        * both will have debug info...
        * use `nm` to generate a symbol listing
* validate application
    * the `magic` should a four letter (32 bit) word, like "TECH" or "SHOT" ...could be two words...
* announce version
    * read from memory
    * communicate over network
* firmware update
    * download image over network (error handling checksums)
    * flash image (image checksum)
    
