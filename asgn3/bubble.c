// Bubble Sort
// Merilyn Kuo
// CSE 13S Spring 2021

#include "bubble.h"

#include "helper.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Code based on python pseudocode in Assignment 3 PDF.

// Sorts an array of numbers. Returns void.
//
// arr[] : array to be sorted
// size  : size of array
//
void bubble_sort(uint32_t arr[], uint32_t size) {

    moves = 0;
    compares = 0;
    n = 0;
    bool swapped = true;

    while (swapped) {

        n += 1;
        swapped = false;

        for (uint32_t i = 1; i < size; i += 1) {

            if (less_than(arr[i], arr[i - 1])) { // if arr[i] < arr[i - 1]
                swap(&arr[i], &arr[i - 1]);
                swapped = true;
            }

            n += 1;
        }

        size -= 1;
    }

    return;
}
