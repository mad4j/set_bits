#include <cstdint>

#include "util_bits.h"


uint64_t get_bits(uint8_t* buffer, uint32_t offset, uint8_t size)
{
    uint64_t value = 0;

    if ((offset%8) != 0)
    {
        value = buffer[offset%8] & ones(8-(offset%8));
        size -= -(offset%8);
    }

    for (uint64_t k=0; k<size/8; k++) {
        uint8_t bits = buffer[offset/8 - k -1];
        value <<= 8;
        value |= bits;
    }

    if ((size%8) != 0) {
        value <<= size%8;
        value |= buffer[offset/8 + size/8] & ones(size%8);
    }

    return value;
}
