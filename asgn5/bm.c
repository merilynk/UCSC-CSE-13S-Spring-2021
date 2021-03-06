// Merilyn Kuo
// CSE 13S Spring 2021
// Bit Matrix ADT

#include "bm.h"

#include "bv.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Stuct definition from Assignment PDF.
struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

// Code referenced from Sahiti's section.

// Create and allocate memory for the bit matrix.
BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    if (m) {
        m->rows = rows;
        m->cols = cols;
        m->vector = bv_create(rows * cols);
        if (!m->vector) {
            free(m);
            m = NULL;
        }
    }
    return m;
}

// Delete bit matrix by freeing allocated memory and nulling pointers.
void bm_delete(BitMatrix **m) {
    if (*m && (*m)->vector) {
        bv_delete(&(*m)->vector);
        free((*m)->vector);
        free(*m);
        *m = NULL;
    }
}

// Get rows in bit matrix.
uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

// Get columns in bit matrix.
uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

// Set a bit in bit matrix at specified position.
void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, r * (m->cols) + c);
}

// Clear a bit in the bit matrix at specified position.
void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * (m->cols) + c);
}

// Get the bit at the specified position.
uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, r * (m->cols) + c);
}

// Convert data into a bit matrix.
BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *m = bm_create(1, length);
    for (uint32_t i = 0; i < length; i++) {
        if (byte & (1 << i)) {
            bm_set_bit(m, 0, i);
        } else {
            bm_clr_bit(m, 0, i);
        }
    }
    return m;
}

// Convert bit matrix into data.
uint8_t bm_to_data(BitMatrix *m) {
    uint8_t data = 0;
    for (uint32_t i = 0; i < 8; i++) {
        data |= (bm_get_bit(m, 0, i) << i);
    }
    return data;
}

// Multiply two bit matrices.
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    BitMatrix *C = bm_create(A->rows, B->cols);
    uint8_t value = 0;
    for (uint32_t i = 0; i < A->rows; i++) {
        for (uint32_t j = 0; j < B->cols; j++) {
            value = 0;
            for (uint32_t k = 0; k < A->cols; k++) {
                value ^= (bm_get_bit(A, i, k) & bm_get_bit(B, k, j));
                if (value == 1) {
                    bm_set_bit(C, i, j);
                } else {
                    bm_clr_bit(C, i, j);
                }
            }
        }
    }
    return C;
}

// Print bit matrix.
void bm_print(BitMatrix *m) {
    bv_print(m->vector);
}
