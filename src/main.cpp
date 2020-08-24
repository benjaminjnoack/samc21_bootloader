#include <cstdint>
#include "sam.h"
#include "memory_map.h"

#define LED_PIN PORT_PA14

/**
 * https://static.docs.arm.com/ihi0042/g/aapcs32.pdf
 * section 6.1.1 Core registers
 * "The first four registers r0-r3 (a1-a4) are used to pass argument values into a subroutine..."
 * TODO __attribute__((noinline,noreturn))
 */
void boot_app(uint32_t sp, uint32_t pc);

int main(void)
{
    SystemInit();

    REG_PORT_DIR0 |= LED_PIN;//set the direction to output
    REG_PORT_OUT0 |= LED_PIN;//set the pin high (LED off)

    uint32_t *app_code = (uint32_t *) __app_rom_start__;
    uint32_t app_sp = app_code[0];
    uint32_t app_pc = app_code[1];

    boot_app(app_pc, app_sp);

    while (1)
    {
        for (uint32_t i = 0; i < 100000; i++)
            ;

        REG_PORT_OUTTGL0 |= LED_PIN;
    }
}

/*
 * TODO would be nice to "use" the variables in C as to avoid the unused-variable warning
 */
void boot_app(uint32_t sp, uint32_t pc)
{
    __asm("mov r0, #0x20002478\n"
          "mov r1, #0x0000415d\n"
          "msr msp, r0\n"
          "bx r1");
}
