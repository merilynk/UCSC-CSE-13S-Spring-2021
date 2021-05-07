// Merilyn Kuo
// CSE 13S Spring 2021
// Bit Vector ADT

#include "bv.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// Code provided in Assignment PDF
struct BitVector {
    uint32_t length; // length in bits
    uint8_t *vector; // array of bytes
};

// Code referenced from Sahiti's section.

BitVector *
    bv_create(uint32_t length) {
    BitVector *v = (BitVector *) calloc(1, sizeof(BitVector));
    if (v) {
        v->length = length;
        uint8_t items = 0;
        if (length % 8 == 0) {
            items = length / 8;
        } else {
            items = length / 8 + 1;
        }
	v->vector = (uint8_t *) calloc(items, sizeof(uint8_t));
    }
    return v;
}

void bv_delete(BitVector **v) {
    if (*v && (*v)->vector) {
        free((*v)->vector);
        free(*v);
        *v = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *v) {
    return v->length;
}

void bv_set_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] |= (1 << (i % 8));
    return;
}

void bv_clr_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] &= ~(1 << (i % 8));
    return;
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    return (v->vector[i / 8] &= (1 << (i % 8))) >> (i % 8);
}

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    bit ^= bv_get_bit(v, i);
    return;
}

void bv_print(BitVector *v) {
    printf("Length: %u bits\n", v->length);
    for (uint32_t i = 0; i < v->length; i++) {
        printf(" %u", bv_get_bit(v, i));
    }
    printf("\n");
}
