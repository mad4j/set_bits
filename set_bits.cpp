#include <cstdint>

/**
 * @brief This function consumes 'size' least significant bits from 'value' parameter.
 * 
 * @param value 
 * @param size 
 * @return uint8_t 
 */
static uint8_t get_ls_bits(uint64_t value, uint8_t size) 
{
    // return 'size' least significant bits from 'value'
    return (uint8_t)(value & ((1 << size)-1));
}


/**
 * @brief 
 * 
 * @param ones 
 * @param zeros 
 * @return uint8_t 
 */
static uint8_t bit_mask(uint8_t ones, uint8_t zeros)
{
    return ((1 << ones)-1) << zeros;
}


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
            buffer[offset/8] &= ~bit_mask(size, padding); 

            // copy bits to 'buffer'
            buffer[offset/8] |= get_ls_bits(bits, size) << padding;

            // consume least significant bits
            bits >>= size;

            // no more bits to consume
            size = 0;

        // otherwise consume 'delta' bits
        } else {
            // clear target bits of 'buffer'
            buffer[offset/8] &= ~bit_mask(delta, padding);

            // copy bits to buffer taking into account the need of padding zeros
            buffer[offset/8] |= get_ls_bits(bits, delta) << padding;

            // consume least significant bits
            bits >>= delta;

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
        // copy a whole byte to 'buffer'
        buffer[offset/8 + k] = get_ls_bits(bits, 8);

        // consume least significant bits
        bits >>= 8;
    }


    // TAIL MANAGEMENT
    // if 'bits' is not containing whole bytes, then copy remaining bits to buffer
    // (e.g. if 'size == 11' then is needed to copy remaining 'size%8 == 3' bits)
    if (size%8 != 0)
    {
        // clear target bits of 'buffer'
        buffer[offset/8 + size/8] &= ~bit_mask(size%8, 0);

        // copy remaining 'size%8' bits to 'buffer'
        buffer[offset/8 + size/8] |= get_ls_bits(bits, size%8);
    }
}
