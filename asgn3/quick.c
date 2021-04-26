// Quicksort
// Merilyn Kuo
// CSE 13S Spring

#include "quick.h"

#include "helper.h"
#include "queue.h"
#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Code based on python pseudocode from Assignment PDF

// Partitions an array based on a pivot. Returns the index of pivot.
//
// arr[] : array to partition
// lo    : index of the leftmost  element in array
// hi    : index of rightmost  element in array
static uint32_t partition(uint32_t arr[], int64_t lo, int64_t hi) {

    uint32_t pivot = arr[lo + ((hi - lo) / 2)];
    int64_t i = lo - 1;
    int64_t j = hi + 1;

    while (i < j) {

        do {
            i += 1;
        } while (less_than(arr[i], pivot)); // check for all elements less than pivot

        do {
            j -= 1;
        } while (less_than(pivot, arr[j])); // check for all elements greater than pivot

        if (i < j) {
            swap(&arr[i], &arr[j]); // swap
        }
    }
    return j;
}

// Sorts an array using quick sort and stacks. Returns void.
//
// arr[] : array to sort
// size  : size of the array
void quick_sort_stack(uint32_t arr[], uint32_t size) {

    moves = 0;
    compares = 0;
    int64_t lo = 0;
    int64_t hi = (int64_t) size - 1;

    Stack *stack = stack_create(size); // create empty stack
    max_size = stack_size(stack);
    stack_push(stack, lo);
    stack_push(stack, hi);

    while (stack_size(stack) != 0) {

        stack_pop(stack, &lo);
        stack_pop(stack, &hi);

        uint32_t p = partition(arr, lo, hi);

        if (lo < p) {
            stack_push(stack, lo);
            stack_push(stack, p);
        }

        if (hi > p + 1) {
            stack_push(stack, p + 1);
            stack_push(stack, hi);
        }

        if (stack_size(stack) > max_size) {
            max_size = stack_size(stack); // getting max stack size
        }
    }
    stack_delete(&stack); // delete stack after use to prevent memory leaks
    return;
}

// Quicksort using queue. Returns void
//
// arr[] : array to sort
// size  : size of array
void quick_sort_queue(uint32_t arr[], uint32_t size) {

    moves = 0;
    compares = 0;
    int64_t lo = 0;
    int64_t hi = size - 1;

    Queue *queue = queue_create(size); // create empty queue with size of array
    max_size = queue_size(queue);

    enqueue(queue, lo);
    enqueue(queue, hi);

    while (queue_size(queue) != 0) {

        dequeue(queue, &lo);
        dequeue(queue, &hi);

        uint32_t p = partition(arr, lo, hi); // partition array

        if (lo < p) {
            enqueue(queue, lo); // pop
            enqueue(queue, p);
        }

        if (hi > p + 1) {
            enqueue(queue, p + 1); // push
            enqueue(queue, hi);
        }

        if (max_size < queue_size(queue)) {
            max_size = queue_size(queue); // getting max queue size
        }
    }
    queue_delete(&queue); // deleting queue after use
}
