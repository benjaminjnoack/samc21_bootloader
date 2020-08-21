#include "sam.h"
#include "memory_map.h"

#define LED_PIN PORT_PA15

int main(void)
{
    SystemInit();
    uint32_t *app_code = (uint32_t *) __app_rom_start__;
    uint32_t app_sp = app_code[0];

    REG_PORT_DIR0 |= LED_PIN;//set the direction to output
    REG_PORT_OUT0 |= LED_PIN;//set the pin high (LED off)

    while (1) 
    {
	    for (uint32_t i = 0; i < 100000; i++)
		    ;

    	REG_PORT_OUTTGL0 |= LED_PIN;
    }
}

