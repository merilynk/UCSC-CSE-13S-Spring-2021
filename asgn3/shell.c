// Shell Sort
// Merilyn Kuo
// CSE 13S Spring 2021

#include <stdint.h>
#include "shell.h"
#include "helper.h"
#include "gaps.h"

void shell_sort(uint32_t arr[], uint32_t size) {
    for (uint32_t gap = 0; gap < GAPS; gap += 1) {
	for (uint32_t i = gap, i < size, i += 1) {
	    uint32_t j = i;
	    uint32_t temp = arr[i];
	    while (j >= gap && temp < arr[j - gap]) {
		arr[j] = arr[j - gap];
		j -= gap;
	    }
	    arr[j] = temp;
	}
    }
}
