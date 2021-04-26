#ifndef __HELPER_H__
#define __HELPER_H__

#include <stdbool.h>
#include <stdint.h>

// Swaps two integers.
void swap(uint32_t *x, uint32_t *y);

// Compares two integers. Returns true if x < y, false elsewise.
bool less_than(uint32_t x, uint32_t y);

// Global variables for statistics:

// Keep track of # array elements that are compared in a sort.
int compares;

// Keeps track of # moves (when an array element is moved) in a sort/
int moves;

// To store the max stack or queue size.
uint32_t max_size;

// For time complexity
int n;

#endif
