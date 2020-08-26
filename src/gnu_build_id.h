/**
 * https://interrupt.memfault.com/blog/gnu-build-id-for-firmware
 */
#ifndef SAMC21_BOOTLOADER_GNU_BUILD_ID_H
#define SAMC21_BOOTLOADER_GNU_BUILD_ID_H

#include "stdint.h"

struct ElfNoteSection {
	uint32_t namesz;
	uint32_t descsz;
	uint32_t type;
	uint8_t data[];
};

/**
 * provided by bootloader.ld
 */
extern const struct ElfNoteSection __gnu_build_id__;

#endif //SAMC21_BOOTLOADER_GNU_BUILD_ID_H
