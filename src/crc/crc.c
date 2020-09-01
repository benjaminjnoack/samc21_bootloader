#include "crc.h"
#include "crc_table.h"

/**
 * http://home.thep.lu.se/~bjorn/crc/
 */

void crc32(const void *data, uint32_t n_bytes, uint32_t* crc)
{
	for(uint32_t i = 0; i < n_bytes; ++i) {
		*crc = crc_table[(uint8_t)*crc ^ ((uint8_t*)data)[i]] ^ *crc >> 8;
	}
}
