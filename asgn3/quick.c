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

static uint32_t partition(uint32_t arr[], int64_t lo, int64_t hi) {
    uint32_t pivot = arr[lo + ((hi - lo) / 2)];
    int64_t i = lo - 1;
    int64_t j = hi + 1;
    while (i < j) {
        do {
            i += 1;
        } while (less_than(arr[i], pivot));
        do {
            j -= 1;
        } while (less_than(pivot, arr[j]));
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    return j;
}

void quick_sort_stack(uint32_t arr[], uint32_t size) {
    moves = 0;
    compares = 0;
    int64_t lo = 0;
    int64_t hi = (int64_t) size - 1;
    Stack *stack = stack_create(size);
    stack_push(stack, lo);
    stack_push(stack, hi);
    while (stack_size(stack) != 0) {
	stack_pop(stack, &lo);
        stack_pop(stack, &hi);
        //stack_pop(stack, &lo);
        uint32_t p = partition(arr, lo, hi);
        if (lo < p) {
            stack_push(stack, lo);
            stack_push(stack, p);
        }
        if (hi > p + 1) {
            stack_push(stack, p + 1);
            stack_push(stack, hi);
        }
    }
    return;
}

void quick_sort_queue(uint32_t arr[], uint32_t size) {
    moves = 0;
    compares = 0;
    int64_t lo = 0;
    int64_t hi = size - 1;
    Queue *queue = queue_create(size);
    enqueue(queue, lo);
    enqueue(queue, hi);
    while (queue_size(queue) != 0) {
        dequeue(queue, &lo);
        dequeue(queue, &hi);
        uint32_t p = partition(arr, lo, hi);
        if (lo < p) {
            enqueue(queue, lo);
            enqueue(queue, p);
        }
        if (hi > p + 1) {
            enqueue(queue, p + 1);
            enqueue(queue, hi);
        }
    }
}
