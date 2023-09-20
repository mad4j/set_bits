
#include <cstdint>

#include "utest.h"

/**
 * @brief This function consumes 'size' least significant bit from 'bits' value
 * 
 * @param value 
 * @param size 
 * @return uint8_t 
 */
uint8_t pop_lsb_bits(uint64_t& bits, uint8_t size) 
{
    // store 'size' least significant bits from 'value'
    uint8_t temp = (uint8_t)(bits & ((1 << size)-1)); 

    // consume 'size' least significant bits from 'value'
    bits >>= size;

    // return previosly stored LSB bits
    return temp;
}


/**
 * @brief This functions copies 'size' least significant bits of 'bits' to 'buffer' starting from 'offset' bit position.
 * 
 * @param buffer 
 * @param offset 
 * @param bits 
 * @param size 
 */
void set_bits(uint8_t* buffer, uint64_t offset, uint64_t bits, uint8_t size)
{

    // HEAD MANAGEMENT
    // if 'offset' is not byte aligned, then consumes enough bits to reach next byte boundary
    // (e.g. if 'offset == 34', then are needed to consume 'delta == 5' bits to reach next byte boundary)
    if (offset%8 != 0) 
    {
        // number of bits needed to reach next byte boundary
        uint8_t delta = 8 - (offset%8);

        // if there are not enough bits, then pad with 'delta-size' zeros
        if (size < delta)
        {
            // copy bits to 'buffer'
            buffer[offset/8] |= pop_lsb_bits(bits, size) << (delta-size);

            // no more bits to consume
            size = 0;

        // otherwise consume 'delta' bits
        } else {
            // copy bits to buffer
            buffer[offset/8] |= pop_lsb_bits(bits, delta);

            // adjust remaining bits size
            size -= delta;
        }

        // move to next byte boundary 
        offset += delta;
    }


    // BODY MANAGEMENT
    // at this point 'offset' is byte aligned, then it is possible to consume whole bytes
    for (uint64_t k = 0; k < size/8; k++)
    {
        // copy a whole byte to 'buffer'
        buffer[offset/8 + k] = pop_lsb_bits(bits, 8);
    }


    // TAIL MANAGEMENT
    // if 'bits' is not containing whole bytes, then copy remaining bits to buffer
    // (e.g. if 'size == 11' then is needed to copy remaining 'size%8 == 3' bits)
    if (size%8 != 0)
    {
        // copy remaining 'size%8' bits to 'buffer'
        buffer[offset/8 + size/8] |= pop_lsb_bits(bits, size%8);
    }

}


UTEST_MAIN();


UTEST(set_bits, both_aligned_8)
 {
    // 00000000 00000000 00000000 00000000 00000000
    uint8_t buffer[5] = { 0x00 };

    // 00000000 10101010 00000000 00000000 00000000
    set_bits(buffer, 8, 0xAA, 8);

    ASSERT_EQ(buffer[0], 0x00);
    ASSERT_EQ(buffer[1], 0xAA);
    ASSERT_EQ(buffer[2], 0x00);
    ASSERT_EQ(buffer[3], 0x00);
    ASSERT_EQ(buffer[4], 0x00);
 }

UTEST(set_bits, both_aligned_16)
 {
    // 00000000 00000000 00000000 00000000 00000000
    uint8_t buffer[5] = { 0x00 };
    
    // 00000000 10111011 10101010 00000000 00000000
    set_bits(buffer, 8, 0xAABB, 16);

    ASSERT_EQ(buffer[0], 0x00);
    ASSERT_EQ(buffer[1], 0xBB);
    ASSERT_EQ(buffer[2], 0xAA);
    ASSERT_EQ(buffer[3], 0x00);
    ASSERT_EQ(buffer[4], 0x00);
 }

 UTEST(set_bits, size_aligned_8)
 {
    // 00000000 00000000 00000000 00000000 00000000
    uint8_t buffer[5] = { 0x00 };

    // 00000000 01111111 00000001 00000000 00000000
    set_bits(buffer, 9, 0xFF, 16);

    ASSERT_EQ(buffer[0], 0x00);
    ASSERT_EQ(buffer[1], 0x7F);
    ASSERT_EQ(buffer[2], 0x01);
    ASSERT_EQ(buffer[3], 0x00);
    ASSERT_EQ(buffer[4], 0x00);
 }