// Shell Sort
// Merilyn Kuo
// CSE 13S Spring 2021

#include "shell.h"

#include "gaps.h"
#include "helper.h"

#include <stdint.h>
#include <stdio.h>

void shell_sort(uint32_t arr[], uint32_t size) {
    moves = 0;
    compares = 0;
    for (uint32_t gap = 0; gap < GAPS; gap += 1) {
        for (uint32_t i = gap; i < size; i += 1) {
            uint32_t j = i;
            uint32_t temp = arr[i];
	    moves += 1;
	    while (j >= gap && less_than(temp, arr[j - gap])) {
                arr[j] = arr[j - gap];
                moves += 1;
                j -= gap;
            }
	    arr[j] = temp;
	    moves += 1;
        }
    }
    return;
}
