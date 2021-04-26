#ifndef __HELPER_H__
#define __HELPER_H__

#include <stdbool.h>
#include <stdint.h>

// Swaps two integers.
void swap(uint32_t *x, uint32_t *y);

bool less_than(uint32_t x, uint32_t y);

int compares;

int moves;

uint32_t max_size;

#endif
