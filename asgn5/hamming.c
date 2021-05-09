// Merilyn Kuo
// CSE 13S Spring 2021
// Hamming

#include "bm.h"
#include "bv.h"
#include "hamming.h"

#include <stdint.h>
#include <stdio.h>

int lookup[16] = { HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2, HAM_ERR, 1, 0, HAM_ERR };

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *M = bm_from_data(msg, 4);
    BitMatrix *product_matrix = bm_multiply(M, G);
    uint8_t code = bm_to_data(product_matrix);
    return code;
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    BitMatrix *c = bm_from_data(code, 8);
    //bm_print(c);
    BitMatrix *error = bm_multiply(c, Ht);
    //bm_print(error);
    uint8_t error_syndrome = bm_to_data(error);
    //printf("error syndrome: %u\n", error_syndrome);
    *msg = bm_to_data(c);
    if (error_syndrome == 0) {
	//printf("HAM_OK\n");
	return HAM_OK;
    }
    else if (lookup[error_syndrome] == HAM_ERR) {
	//printf("HAM_ERR\n");
	return HAM_ERR;
    }
    else {
	if (bm_get_bit(c, 0, lookup[error_syndrome]) == 1) {
	    bm_clr_bit(c, 0, lookup[error_syndrome]);
	}
	else {
	    bm_set_bit(c, 0, lookup[error_syndrome]);
	}
	//printf("HAM_CORRECT\n");
	//bm_print(c);
	//printf("%u\n", bm_to_data(c));
	*msg = bm_to_data(c);
	return HAM_CORRECT;
    }
}
