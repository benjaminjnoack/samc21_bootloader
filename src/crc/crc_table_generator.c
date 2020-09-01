#include <stdint.h>
#include <stdio.h>

#define CRC_TABLE_SIZE 0x100

uint32_t crc32_for_byte(uint32_t r);

int main()
{
	printf("#include <stdint.h>\n\n");

	printf("#define CRC_TABLE_SIZE 0x%X\n\n", CRC_TABLE_SIZE);
	printf("static uint32_t crc_table[%d] = {\n", CRC_TABLE_SIZE);

	for (uint32_t i = 0; i < CRC_TABLE_SIZE - 1; i++) {
		printf("0x%X,\t//0x%02X\n", crc32_for_byte(i), i);
	}

	printf("0x%X\t//0x%02X\n", crc32_for_byte(CRC_TABLE_SIZE - 1), CRC_TABLE_SIZE - 1);
	printf("};");

	return 0;
}

uint32_t crc32_for_byte(uint32_t r)
{
	for(int j = 0; j < 8; ++j) {
		r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
	}

	return r ^ (uint32_t)0xFF000000L;
}

