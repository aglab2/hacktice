#include "types.h"

#define uint8_t u8
#define uint32_t u32

void mlz4_compress(const uint8_t* in, const uint32_t inSize, uint8_t* out, uint32_t* outSize);
void mlz4_decompress(const uint8_t* in, uint8_t* out);
