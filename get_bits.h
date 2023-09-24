#ifndef GETBITS_H
#define GETBITS_H

#include <cstdint>

/*
    Stream of bits in LSB-first order
    b0 b1 b2 b3 b4 b5 b6 b7 b8 b9 b10 b11 b12 b13 b14 b15 b16 ...

    Memory layout of LSB-first stream
    M[0] b7  b6  b5  b4  b3  b2  b1  b0
    M[1] b15 b14 b13 b12 b11 b10 b9  b8
    M[2] ...
*/

// Get bit aligned values from buffer
uint64_t get_bits(uint8_t* buffer, uint32_t offset, uint8_t size);

#endif //GETBITS_H
