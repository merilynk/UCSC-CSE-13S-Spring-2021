// Merilyn Kuo
// CSE 13S Spring 2021
// Bit Vector ADT

#include "bv.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Code provided in Assignment PDF
struct BitVector {
    uint32_t length; // length in bits
    uint8_t *vector; // array of bytes
};

// Create and allocate memory for bit vector.
BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) calloc(1, sizeof(BitVector));
    if (v) {
        v->length = length;
        uint32_t items = 0;

        // Rounding length
        if (v->length % 8 == 0) {
            items = v->length / 8;
        } else {
            items = v->length / 8 + 1;
        }

        v->vector = (uint8_t *) calloc(items, sizeof(uint8_t));
        if (!v->vector) {
            free(v);
            v = NULL;
        }
    }
    return v;
}

// Delete vector by freeing memory and nulling pointers
void bv_delete(BitVector **v) {
    if (*v && (*v)->vector) {
        free((*v)->vector);
        free(*v);
        *v = NULL;
    }
    return;
}

// Returns length of bit vector
uint32_t bv_length(BitVector *v) {
    return v->length;
}

// Sets a bit in the bit vector at index, i.
void bv_set_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] |= (1 << (i % 8));
    return;
}

// Clears a bit in the bit vector at index, i.
void bv_clr_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] &= ~(1 << (i % 8));
    return;
}

// Gets the bit at index, i.
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    return (v->vector[i / 8] >> (i % 8)) & 1;
}

// XORs a bit at index, i with another bit.
void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    if (bit == bv_get_bit(v, i)) {
        bv_clr_bit(v, i);
    } else {
        bv_set_bit(v, i);
    }
    return;
}

// Print bit vector.
void bv_print(BitVector *v) {
    printf("Length: %u bits\n", v->length);
    for (uint32_t i = 0; i < v->length; i++) {
        printf(" %u", bv_get_bit(v, i));
    }
    printf("\n");
}
