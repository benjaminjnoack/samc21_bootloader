#include <cstdint>
#include "sam.h"
#include "memory_map.h"
#include "gnu_build_id.h"
#include "crc.h"
#include "image.h"

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
	REG_PORT_DIRSET0 |= LED_PIN;//set the pin high (LED on)

	uint32_t i;
	uint32_t sz = __gnu_build_id__.namesz;
	uint32_t crc = 0;
	uint32_t remainder;
	uint8_t data = 0;
	uint32_t *app_start;
	uint32_t sp;
	uint32_t pc;

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
	 * The image is stored at the bottom of app rom
	 */
	struct image_hdr *image_hdr = (struct image_hdr *) &__app_rom_start__;

	/**
	 * some basic sanity checks
	 */
	if (image_hdr->checksum == IMAGE_DUMMY_CHECKSUM) {
		goto forever;
	}

	crc_table_init();

	/**
	 * image_size is the next word after the checksum
	 */
	crc32((uint8_t *) &image_hdr->image_size, image_hdr->image_size, &crc);
	if (crc != image_hdr->checksum) {
		goto forever;
	}

	/**
	 * begin iterating through the data array by setting size to the sum,
	 * including null terminators, of all the data fields
	 */
	sz = (image_hdr->host_size + 1) + (image_hdr->user_size + 1) + (IMAGE_MAGIC_LENGTH + 1);

	/**
	 * iterate through the data
	 * its all ASCII text so there shouldn't be any 0xFFs
	 */
	for (i = 0; i < sz; i++) {
		data = image_hdr->data[i];
		if (data == 0xFF) {
			break;
		}
	}

	/**
	 * add the size of the struct
	 * the data array is just one byte as calculated by sizeof
	 */
	sz += sizeof(struct image_hdr);

	/**
	 * sz is a number of bytes
	 * bump it up to the nearest 32 bit boundary
	 */
	remainder = sz % sizeof(uint32_t);
	if (remainder) {
		sz += remainder;
	}

	/**
	 * divide down to the number of uint32
	 * because C will use pointer arithmetic
	 */
	sz /= sizeof(uint32_t);

	app_start = (uint32_t *) &__app_rom_start__ + sz;

	sp = app_start[0];
	pc = app_start[1];
	boot_app(sp, pc);

forever:
	while (1) {
		for (i = 0; i < 100000; i++);

		REG_PORT_OUTTGL0 |= LED_PIN;
	}
}

void boot_app(uint32_t sp, uint32_t pc)
{
	__asm("msr msp, r0\n"
		  "bx r1");
}
