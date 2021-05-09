#ifndef _HELPER_H_
#define _HELPER_H_

#include "bm.h"
#include <stdint.h>

// Creates generator matrix.
BitMatrix *create_generator_matrix(void);

// Creates H transpose matrix.
BitMatrix *create_H_transpose_matrix(void);

// Code from Assignment PDF

// Returns the lower nibble of val
uint8_t lower_nibble(uint8_t val);

// Returns the upper nibble of val
uint8_t upper_nibble(uint8_t val);

// Packs two nibbles into a byte
uint8_t pack_byte(uint8_t upper, uint8_t lower);

#endif
