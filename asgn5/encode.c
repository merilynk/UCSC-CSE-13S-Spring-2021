// Merilyn Kuo
// CSE 13S Spring 2021
// Encode

#include "bm.h"
#include "bv.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    //BitVector *bv = bv_create(17);

    //bv_print(bv);

    //printf("Length Function returns: %u\n", bv_length(bv));
    //bv_set_bit(bv, 6);
    //bv_set_bit(bv, 15);
    //bv_set_bit(bv, 2);
    //bv_set_bit(bv, 9);
    //bv_print(bv);

    //bv_clr_bit(bv, 2);
    //bv_print(bv);

    //bv_xor_bit(bv, 2, 1);
    //bv_print(bv);

    //bv_xor_bit(bv, 15, 1);
    //bv_print(bv);


    BitMatrix *bm = bm_create(4, 4);
    printf("rows: %u\n", bm_rows(bm));
    printf("columns: %u\n", bm_cols(bm));

    bm_set_bit(bm, 0, 0);
    bm_set_bit(bm, 0, 1);
    bm_set_bit(bm, 1, 0);
    bm_print(bm);

    bm_clr_bit(bm, 1, 0);
    bm_print(bm);

    uint8_t x = bm_get_bit(bm, 0, 0);
    printf("get bit: %u\n", x);

    printf("data from bm: %u\n", bm_to_data(bm));
    printf("bm from data: \n");
    bm_print(bm_from_data(5, 4));

    BitMatrix *mult = bm_multiply(bm_from_data(5, 4), bm);

    bm_print(mult);

    bm_delete(&bm);
    //bv_delete(&bv);
}
