**TODO**

* use CMSIS *.c as a library
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
    * 
    