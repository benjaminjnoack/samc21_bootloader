#ifndef SAMC21_BOOTLOADER_IMAGE_H
#define SAMC21_BOOTLOADER_IMAGE_H

#include "stdint.h"
#include "stdbool.h"

/**
 * TODO document contents
 * magic 64 bit
 * null terminated user
 * null terminated host
 * null terminated 64 bit git sha1
 */
struct __attribute__((packed)) image_hdr  {
	uint32_t checksum;
	uint32_t timestamp;
	uint8_t user_size;
	uint8_t host_size;
	uint32_t commit_sha1;
	bool clean_build;
	uint8_t major_version;
	uint8_t minor_version;
	uint8_t patch_version;
	uint8_t data[];
};

#endif //SAMC21_BOOTLOADER_IMAGE_H