// Merilyn Kuo
// CSE 13S Spring 2021
// Bloom Filter

#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Code from assignment pdf
struct BloomFilter {
    uint64_t primary[2];  // salt
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;  // bit vector representing bloom filter
};

// Code from assignment pdf.
// Construts a bloom filter given a size parameter.
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

// Destructs the bloom filter passed in.
void bf_delete(BloomFilter **bf) {
    if (*bf && (*bf)->filter) {
        bv_delete(&((*bf)->filter));
        free(*bf);
        *bf = NULL;
    }
    return;
}

// Returns the length of the bloom filter.
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

// Inserts a word into the bloom filter.
void bf_insert(BloomFilter *bf, char *oldspeak) {
    // compute indices from hash
    uint32_t index1 = hash(bf->primary, oldspeak) % bf_size(bf);
    uint32_t index2 = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint32_t index3 = hash(bf->tertiary, oldspeak) % bf_size(bf);
    // set bit at indices
    bv_set_bit(bf->filter, index1);
    bv_set_bit(bf->filter, index2);
    bv_set_bit(bf->filter, index3);
}

// Checks if a word is in the bloom filter.
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t index1 = hash(bf->primary, oldspeak) % bf_size(bf);
    uint32_t index2 = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint32_t index3 = hash(bf->tertiary, oldspeak) % bf_size(bf);
    return (bv_get_bit(bf->filter, index1) == 1) && (bv_get_bit(bf->filter, index2) == 1)
           && (bv_get_bit(bf->filter, index3) == 1);
}

// Returns the number of set bits in the bloom filter.
uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (bv_get_bit(bf->filter, i) == 1) {
            count++;
        }
    }
    return count;
}

// Prints the bloom filter.
void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
