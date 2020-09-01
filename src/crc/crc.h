#ifndef SAMC21_BLINK_CRC_H
#define SAMC21_BLINK_CRC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

void crc32(const void *data, uint32_t n_bytes, uint32_t* crc);

#ifdef __cplusplus
}
#endif

#endif //SAMC21_BLINK_CRC_H
