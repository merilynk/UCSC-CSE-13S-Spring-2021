// Helper functions and variables for program.
// Merilyn Kuo
// CSE 13S Spring 2021

#include <stdint.h>
#include "helper.h"

void swap(uint32_t *x, uint32_t *y) {
    int temp = *x;
    *x =*y;
    *y = temp;
}

uint32_t partition(uint32_t arr[], uint32_t lo, uint32_t hi) {
    uint32_t pivot = arr[lo + ((hi - lo) / 2)];
    uint32_t i = lo - 1;
    uint32_t j = hi + 1;
    do {
	i += 1;
	while (arr[i] < pivot) {
	    i += 1;
	}
	j -= 1;
	while (arr[j] > pivot) {
	    j -= 1;
	}
	if (i < j) {
	    swap(&arr[i], &arr[j]);
	}
    } while (i < j);
    return j;
}
