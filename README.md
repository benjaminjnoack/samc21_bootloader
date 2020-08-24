**Contents**

* `gcc` Atmel CMSIS linker scripts
* `samc21_cmsis` [subtree](https://github.com/benjaminjnoack/samc21_cmsis)
* `CMakeLists.txt` build script
* `atmel_samc21_xplained_pro.cfg` OpenOCD config file


**TODO**

* development builds
I want to be able to build the boot loader by itself.
That means no additional padding on the binary.
and no jump instruction (to what would be garbage without the app).
Instead, it will just hit a forever loop blinking the LED.
Maybe go to a routine which handles the case when there is no valid application installed (because there isn't)
It should be driven on whether or not the bootloader is the main project being built, or if it is a subsidiary.

* linker scripts
    * the bootloader should be the one which determines where things go
    * apps will need to reference the bootloader's provided `app.ld`
* validate application
* boot application
* announce version
    * read from memory
    * communicate over network
* firmware update
    * download image over network (error handling checksums)
    * flash image (image checksum)
    
