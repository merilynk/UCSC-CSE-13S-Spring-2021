// Bubble Sort
// Merilyn Kuo
// CSE 13S Spring 2021

#include "bubble.h"
#include "helper.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

void bubble_sort(uint32_t arr[], uint32_t size) {
    bool swapped = true;
    do {
        swapped = false;
        for (uint32_t i = 1; i < size; i += 1) {
            if (arr[i] < arr[i - 1]) {
                swap(&arr[i], &arr[i - 1]);
                swapped = true;
            }
        }
        size -= 1;
    } while (swapped);
    return;
}
