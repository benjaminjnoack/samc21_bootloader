#include <cstdint>
#include "sam.h"
#include "memory_map.h"

#define LED_PIN PORT_PA14

void boot_app(uint32_t pc, uint32_t sp);

int main(void)
{
    SystemInit();

    uint32_t *app_code = (uint32_t *) __app_rom_start__;
    uint32_t app_sp = app_code[0];
    uint32_t app_start = app_code[1];

    boot_app(app_sp, app_start);

    REG_PORT_DIR0 |= LED_PIN;//set the direction to output
    REG_PORT_OUT0 |= LED_PIN;//set the pin high (LED off)

    while (1)
    {
        for (uint32_t i = 0; i < 100000; i++)
            ;

        REG_PORT_OUTTGL0 |= LED_PIN;
    }
}

void boot_app(uint32_t pc, uint32_t sp)
{
    /**
     * https://static.docs.arm.com/ihi0042/g/aapcs32.pdf
     * section 6.1.1 Core registers
     * "The first four registers r0-r3 (a1-a4) are used to pass argument values into a subroutine..."
     * TODO would be nice to "use" the variables in C as to avoid the unused-variable warning
     */
    __asm("msr msp, r1\n"
          "bx r0");
}
