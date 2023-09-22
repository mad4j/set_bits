#include "utest/utest.h"
#include "set_bits.h"

UTEST_MAIN();


UTEST(set_bits, value_FF_offset_8_size_8)
 {
    // 00000000 00000000 00000000 00000000 00000000
    uint8_t buffer[5] = { 0x00 };

    // 00000000 11111111 00000000 00000000 00000000
    set_bits(buffer, 8, 0xFF, 8);

    ASSERT_EQ(buffer[0], 0x00);
    ASSERT_EQ(buffer[1], 0xFF);
    ASSERT_EQ(buffer[2], 0x00);
    ASSERT_EQ(buffer[3], 0x00);
    ASSERT_EQ(buffer[4], 0x00);
 }

 UTEST(set_bits, value_FF_offset_9_size_8)
 {
    // 00000000 00000000 00000000 00000000 00000000
    uint8_t buffer[5] = { 0x00 };

    // 00000000 11111110 00000001 00000000 00000000
    set_bits(buffer, 9, 0b11111111, 8);

    ASSERT_EQ(buffer[0], 0b00000000);
    ASSERT_EQ(buffer[1], 0b11111110);
    ASSERT_EQ(buffer[2], 0b00000001);
    ASSERT_EQ(buffer[3], 0b00000000);
    ASSERT_EQ(buffer[4], 0b00000000);
 }

  UTEST(set_bits, value_FF_offset_10_size_8)
 {
    // 00000000 00000000 00000000 00000000 00000000
    uint8_t buffer[5] = { 0x00 };

    // 00000000 11111100 00000011 00000000 00000000
    set_bits(buffer, 10, 0b11111111, 8);

    ASSERT_EQ(buffer[0], 0b00000000);
    ASSERT_EQ(buffer[1], 0b11111100);
    ASSERT_EQ(buffer[2], 0b00000011);
    ASSERT_EQ(buffer[3], 0b00000000);
    ASSERT_EQ(buffer[4], 0b00000000);
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
    ASSERT_EQ(buffer[1], 0xFE);
    ASSERT_EQ(buffer[2], 0x01);
    ASSERT_EQ(buffer[3], 0x00);
    ASSERT_EQ(buffer[4], 0x00);
 }


 UTEST(set_bits, size_aligned_2)
 {
    // 00000000 00000000 00000000 00000000 00000000
    uint8_t buffer[5] = { 0x00 };

    // 00000000 00000110 00000000 00000000 00000000
    set_bits(buffer, 9, 0x03, 2);

    ASSERT_EQ(buffer[0], 0x00);
    ASSERT_EQ(buffer[1], 0x06);
    ASSERT_EQ(buffer[2], 0x00);
    ASSERT_EQ(buffer[3], 0x00);
    ASSERT_EQ(buffer[4], 0x00);
 }
