#ifndef __HELPER_H__
#define __HELPER_H__

#include <stdint.h>

// Swaps two integers.
void swap(uint32_t *x, uint32_t *y);

// Defines a pivot and places elements less than the pivot to the left side and the elements
// greater than or equal to the pivot to the right side of the array.
uint32_t partition(uint32_t arr[], uint32_t lo, uint32_t hi);



#endif
