#include <cstdint>
#include "sam.h"
#include "memory_map.h"
#include "gnu_build_id.h"

#define LED_PIN PORT_PA14

/**
* https://static.docs.arm.com/ihi0042/g/aapcs32.pdf
* section 6.1.1 Core registers
* "The first four registers r0-r3 (a1-a4) are used to pass argument values into a subroutine..."
*/
__attribute__((naked)) void boot_app(uint32_t sp, uint32_t pc);

int main(void)
{
    SystemInit();

    REG_PORT_DIR0 |= LED_PIN;//set the direction to output
    REG_PORT_OUT0 |= LED_PIN;//set the pin high (LED off)

    uint32_t i;
    uint32_t sz = __gnu_build_id__.namesz;
    uint8_t data = 0;

    /**
     * There are FAR easier ways to iterate through this data.
     * However, we aren't actually using the data,
     * and this prevents the compiler from optimizing it away
     */
    for (i = 0; i < sz; i++) {
        data = __gnu_build_id__.data[i];
        if (data == '\0') {
            break;
        }
    }

    sz = __gnu_build_id__.namesz + __gnu_build_id__.descsz;
    for (i++; i < sz; i++) {
        data = __gnu_build_id__.data[i];
        if (data == '\0') {
            break;
        }
    }


    /**
     * __app_rom_start__ is declared in memory_map.h
     * which, in turn, is defined in memory_map.ld
    uint32_t *app_start = &__app_rom_start__;
    uint32_t sp = app_start[0];
    uint32_t pc = app_start[1];
    boot_app(sp, pc);
     */


    while (1)
    {
        for (i = 0; i < 100000; i++)
            ;

        REG_PORT_OUTTGL0 |= LED_PIN;
    }
}

void boot_app(uint32_t sp, uint32_t pc)
{
    __asm("msr msp, r0\n"
          "bx r1");
}
