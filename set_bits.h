#ifndef SETBITS_H
#define SETBITS_H


/*
    Stream of bits in LSB-first order
    b0 b1 b2 b3 b4 b5 b6 b7 b8 b9 b10 b11 b12 b13 b14 b15 b16 ...

    Memory layout of LSB-first stream
    M[0] b7  b6  b5  b4  b3  b2  b1  b0
    M[1] b15 b14 b13 b12 b11 b10 b9  b8
    M[2] ...
*/

// Set buffer with bit aligned values and LSB-first order
void set_bits(uint8_t* buffer, uint32_t offset, uint64_t bits, uint8_t size);

#endif //SETBITS_H