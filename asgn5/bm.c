// Merilyn Kuo
// CSE 13S Spring 2021
// Bit Matrix ADT


#include "bv.h"
#include "bm.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

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

void bm_delete(BitMatrix **m) {
    if (*m && (*m)->vector) {
	free((*m)->vector);
	free(*m);
	*m = NULL;
    }
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, r * (m->cols) + c);
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * (m->cols) + c);
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, r * (m->cols) + c);
}

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *m = bm_create(1, length);
    for (uint32_t i = 0; i < length; i ++) {
	if (byte & (1 << i)) {
	    bm_set_bit(m, 0, i);
	}
	else {
	    bm_clr_bit(m, 0, i);
	}
    }
    return m;
}

uint8_t bm_to_data(BitMatrix *m) {
    uint8_t data = 0;
    for (uint32_t i = 0; i < 8; i ++) {
	data |= (bm_get_bit(m, 0, i) << i);
    }
    return data;
}

BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    BitMatrix *C = bm_create(A->rows, B->cols);
    uint8_t value = 0;
    for (uint32_t i = 0; i < A->rows; i ++) {
	for (uint32_t j = 0; j < B->cols; j ++) {
	    value = 0;
	    for (uint32_t k = 0; k < A->cols; k ++) {
		value ^= (bm_get_bit(A, i, k) & bm_get_bit(B, k, j));
		if (value == 1) {
		    bm_set_bit(C, i, j);
		}
		else {
		    bm_clr_bit(C, i, j);
		}
	    }
	}
    }
    return C;
}

void bm_print(BitMatrix *m) {
    bv_print(m->vector);
}
