// Merilyn Kuo
// CSE 13S Spring 2021
// Encode

#include "bm.h"
#include "bv.h"
#include "hamming.h"
#include "helper.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {

    BitMatrix *G = create_generator_matrix();
    bm_print(G);

    BitMatrix *Ht = create_H_transpose_matrix();
    bm_print(Ht);

}
