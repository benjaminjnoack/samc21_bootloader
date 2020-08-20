**Contents**

* CMSIS headers
* reference linker scripts

**TODO**

* `startup_<device>.c`
    * same code used by bootloader, app, and updater
    * symbols are not application specific and will be defined in linker script
* `system_<device>.c`
    * is there any common initialization (clocks?)