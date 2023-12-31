#include <cstdint>

#include "util_bits.h"


/**
 * @brief This functions copies 'size' least significant bits of 'bits' to 'buffer' starting from 'offset' bit position.
 * 
 * Example:
 * 
 * // 00000000 00000000 00000000 00000000 00000000
 * uint8_t buffer[5] = { 0x00 };
 *   
 * // 00000000 10111011 10101010 00000000 00000000
 * set_bits(buffer, 8, 0xAABB, 16);
 * 
 * @param buffer 
 * @param offset 
 * @param bits 
 * @param size 
 */
void set_bits(uint8_t* buffer, uint32_t offset, uint64_t bits, uint8_t size)
{
    // HEAD MANAGEMENT
    // if 'offset' is not byte aligned, then consumes enough bits to reach next byte boundary
    // (e.g. if 'offset == 34', then are needed to consume 'delta == 5' bits to reach next byte boundary)
    if ((offset%8) != 0) 
    {
        // numer of padding zeros
        uint8_t padding = (uint8_t)(offset%8);

        // number of bits needed to reach next byte boundary
        uint8_t delta = 8 - padding;

        // if there are not enough bits, then pad with 'delta-size' zeros
        if (size < delta)
        {
            // clear target bits of 'buffer'
            buffer[offset/8] &= ~ones(padding); 

            // copy and consume bits to 'buffer' taking into account the need of padding zeros
            buffer[offset/8] |= consume_lsb(bits, size) << padding;

            // no more bits to consume
            size = 0;

        // otherwise consume 'delta' bits
        } else {
            // clear target bits of 'buffer'
            buffer[offset/8] &= ones(padding);

            // copy and consume bits to 'buffer' taking into account the need of padding zeros
            buffer[offset/8] |= consume_lsb(bits, delta) << padding;

            // adjust remaining bits size
            size -= delta;
        }

        // move to next byte boundary 
        offset += delta;
    }


    // BODY MANAGEMENT
    // at this point 'offset' is byte aligned, then it is possible to consume whole bytes
    for (uint64_t k = 0; k < (size/8); k++) 
    {
        // copy and consume a whole byte to 'buffer'
        buffer[offset/8 + k] = consume_lsb(bits, 8);
    }


    // TAIL MANAGEMENT
    // if 'bits' is not containing whole bytes, then copy remaining bits to buffer
    // (e.g. if 'size == 11' then is needed to copy remaining 'size%8 == 3' bits)
    if (size%8 != 0)
    {
        // clear target bits of 'buffer'
        buffer[offset/8 + size/8] &= ~ones(size%8);

        // copy and consume remaining 'size%8' bits to 'buffer'
        buffer[offset/8 + size/8] |= consume_lsb(bits, size%8);
    }
}
