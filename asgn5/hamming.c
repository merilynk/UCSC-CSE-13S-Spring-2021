// Merilyn Kuo
// CSE 13S Spring 2021
// Hamming

#include "hamming.h"

#include "bm.h"
#include "bv.h"
#include "helper.h"

#include <stdint.h>
#include <stdio.h>

// lookup table
int lookup[16] = { HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2, HAM_ERR,
    1, 0, HAM_ERR };

// Data encoding function
// G: generator matrix
// msg: data to encode
// Returns encoded data.
uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *M = bm_from_data(msg, 4); // turn data into matrix

    BitMatrix *product_matrix = bm_multiply(M, G); // matrix * Generator

    uint8_t code = bm_to_data(product_matrix); // turn back into data

    // free memory
    bm_delete(&M);
    bm_delete(&product_matrix);

    return code;
}

// Data decoding function
// Ht: H transpose matrix
// code: data to decode
// *msg: pointer to decoded data
// Returns HAM_STATUS from lookup table.
HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    BitMatrix *c = bm_from_data(code, 8); // get bm from code
    BitMatrix *error = bm_multiply(c, Ht); // c * Ht
    uint8_t error_syndrome = bm_to_data(error);

    *msg = bm_to_data(c); // pass decoded data back through pointer

    if (error_syndrome == 0) {
        // free memory
        bm_delete(&c);
        bm_delete(&error);

        return HAM_OK;

    } else if (lookup[error_syndrome] == HAM_ERR) {
        uncorrected_errors += 1; // statistics

        // free memory
        bm_delete(&c);
        bm_delete(&error);
        return HAM_ERR;

    } else {

        // lookup table
        if (bm_get_bit(c, 0, lookup[error_syndrome]) == 1) {
            bm_clr_bit(c, 0, lookup[error_syndrome]);
        } else {
            bm_set_bit(c, 0, lookup[error_syndrome]);
        }

        *msg = bm_to_data(c);

        corrected_errors += 1; // statistics

        // free memory
        bm_delete(&c);
        bm_delete(&error);

        return HAM_CORRECT;
    }
}
