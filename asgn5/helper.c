// Merilyn Kuo
// CSE 13S Spring 2021
// Helper

#include "helper.h"

#include "bm.h"

#include <stdint.h>

// Creates and sets values of generator matrix
BitMatrix *create_generator_matrix(void) {
    BitMatrix *Generator = bm_create(4, 8);
    bm_set_bit(Generator, 0, 0);
    bm_set_bit(Generator, 0, 5);
    bm_set_bit(Generator, 0, 6);
    bm_set_bit(Generator, 0, 7);
    bm_set_bit(Generator, 1, 1);
    bm_set_bit(Generator, 1, 4);
    bm_set_bit(Generator, 1, 6);
    bm_set_bit(Generator, 1, 7);
    bm_set_bit(Generator, 2, 2);
    bm_set_bit(Generator, 2, 4);
    bm_set_bit(Generator, 2, 5);
    bm_set_bit(Generator, 2, 7);
    bm_set_bit(Generator, 3, 3);
    bm_set_bit(Generator, 3, 4);
    bm_set_bit(Generator, 3, 5);
    bm_set_bit(Generator, 3, 6);
    return Generator;
}

// Creates and sets values of H transpose matrix
BitMatrix *create_H_transpose_matrix(void) {
    BitMatrix *H_transpose = bm_create(8, 4);
    bm_set_bit(H_transpose, 0, 1);
    bm_set_bit(H_transpose, 0, 2);
    bm_set_bit(H_transpose, 0, 3);
    bm_set_bit(H_transpose, 1, 0);
    bm_set_bit(H_transpose, 1, 2);
    bm_set_bit(H_transpose, 1, 3);
    bm_set_bit(H_transpose, 2, 0);
    bm_set_bit(H_transpose, 2, 1);
    bm_set_bit(H_transpose, 2, 3);
    bm_set_bit(H_transpose, 3, 0);
    bm_set_bit(H_transpose, 3, 1);
    bm_set_bit(H_transpose, 3, 2);
    bm_set_bit(H_transpose, 4, 0);
    bm_set_bit(H_transpose, 5, 1);
    bm_set_bit(H_transpose, 6, 2);
    bm_set_bit(H_transpose, 7, 3);
    return H_transpose;
}

// Get lower nibble of byte
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

// Get upper nibble of byte
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

// Reconstruct byte from nibbles
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}
