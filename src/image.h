#ifndef SAMC21_BOOTLOADER_IMAGE_H
#define SAMC21_BOOTLOADER_IMAGE_H

#include "stdint.h"
#include "stdbool.h"

#define IMAGE_CHECKSUM_DEFAULT 0x12345678
#define IMAGE_MAGIC_LENGTH 8

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
