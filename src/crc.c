#include "crc.h"

/**
 * http://home.thep.lu.se/~bjorn/crc/
 */

static uint32_t table[0x1000];

uint32_t crc32_for_byte(uint32_t r);

void crc_table_init() {
	for(uint32_t i = 0; i < 0x100; ++i) {
		table[i] = crc32_for_byte(i);
	}
}

uint32_t crc32_for_byte(uint32_t r)
{
	for(int j = 0; j < 8; ++j) {
		r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
	}

	return r ^ (uint32_t)0xFF000000L;
}

void crc32(const void *data, uint32_t n_bytes, uint32_t* crc)
{
	for(uint32_t i = 0; i < n_bytes; ++i) {
		*crc = table[(uint8_t)*crc ^ ((uint8_t*)data)[i]] ^ *crc >> 8;
	}
}

