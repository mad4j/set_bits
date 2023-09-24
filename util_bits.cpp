#include <cstdint>

uint64_t ones(uint8_t n) 
{
    return (1<<n)-1;
}


uint64_t consume_lsb(uint64_t& value, uint8_t size)
{
    // store 'size' least significant bits
    uint64_t bits = value & ones(size);

    // consume 'sizep least significant bits
    value >>= size;

    // return stored bits
    return bits;
}


void append_lsb(uint64_t& value, uint64_t bits, uint8_t size) 
{
    // clear bits outside 'size' range
    bits &= ~ones(size);
    
    // create room for new bits
    value <<= size;

    // add new bits
    value |= bits;
}

