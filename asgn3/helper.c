// Helper functions and variables for program.
// Merilyn Kuo
// CSE 13S Spring 2021

#include "helper.h"

#include <stdint.h>

void swap(uint32_t *x, uint32_t *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
