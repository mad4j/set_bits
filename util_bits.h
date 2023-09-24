#ifndef UTILBITS_H
#define UTILBITS_H

#include <cstdint>

uint8_t ones(uint8_t n);
uint64_t consume_lsb(uint64_t& value, uint8_t size);
void append_lsb(uint64_t& value, uint64_t bits, uint8_t size);

#endif //UTILBITS_H