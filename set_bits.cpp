
#include <cstdint>

/**
 * @brief This function consumes 'size' least significant bits from 'value' parameter.
 * 
 * @param value 
 * @param size 
 * @return uint8_t 
 */
uint8_t get_ls_bits(uint64_t value, uint8_t size) 
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
uint8_t bit_mask(uint8_t ones, uint8_t zeros)
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
void set_bits(uint8_t* buffer, uint64_t offset, uint64_t bits, uint8_t size)
{
    // avoid to modify function parameter (MISRA 17.8)
    uint64_t o = offset;
    uint64_t b = bits;
    uint8_t s = size;

    // HEAD MANAGEMENT
    // if 'offset' is not byte aligned, then consumes enough bits to reach next byte boundary
    // (e.g. if 'offset == 34', then are needed to consume 'delta == 5' bits to reach next byte boundary)
    if (o%8 != 0) 
    {
        // number of padding zeros
        uint8_t padding = o%8;

        // number of bits needed to reach next byte boundary
        uint8_t delta = 8 - padding;

        // if there are not enough bits, then pad with 'delta-size' zeros
        if (s < delta)
        {
            // clear target bits of 'buffer'
            buffer[o/8] &= ~bit_mask(s, padding); 

            // copy bits to 'buffer'
            buffer[o/8] |= get_ls_bits(b, s) << padding;

            // consume least significant bits
            b >>= s;

            // no more bits to consume
            s = 0;

        // otherwise consume 'delta' bits
        } else {
            // clear target bits of 'buffer'
            buffer[o/8] &= ~bit_mask(delta, padding);

            // copy bits to buffer taking into account the need of padding zeros
            buffer[o/8] |= get_ls_bits(b, delta) << padding;

            // consume least significant bits
            b >>= delta;

            // adjust remaining bits size
            s -= delta;
        }

        // move to next byte boundary 
        o += delta;
    }


    // BODY MANAGEMENT
    // at this point 'offset' is byte aligned, then it is possible to consume whole bytes
    for (uint64_t k = 0; k < s/8; k++)
    {
        // copy a whole byte to 'buffer'
        buffer[o/8 + k] = get_ls_bits(b, 8);

        // consume least significant bits
        b >>= 8;
    }


    // TAIL MANAGEMENT
    // if 'bits' is not containing whole bytes, then copy remaining bits to buffer
    // (e.g. if 'size == 11' then is needed to copy remaining 'size%8 == 3' bits)
    if (s%8 != 0)
    {
        // clear target bits of 'buffer'
        buffer[o/8 + s/8] &= ~bit_mask(s%8, 0);

        // copy remaining 'size%8' bits to 'buffer'
        buffer[o/8 + s/8] |= get_ls_bits(b, s%8);
    }
}
