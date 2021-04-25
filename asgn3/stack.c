// Stack
// Merilyn Kuo
// CSE 13S Spring 2021

#include "stack.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Code from Assignment 3 PDF
struct Stack {
    uint32_t top; // Index of next empty slot
    uint32_t capacity; // Max num of items in stack
    int64_t *items; // Array of items
};

// Code from Assignment 3 PDF

// Constructs a stack, Returns the stack, s.
//
// capacity: max # of items in the stack
//
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// Code from Assignment 3 PDF

// Destructs a stack. Returns nothing.
//
// **s: address of a pointer to the stack
//
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

// Code for these functions are referenced from Sahiti's Section.
// Function headers from Assignment 3 PDF

// Checks if the stack is empty. Returns a boolean.
//
// *s: stack
//
bool stack_empty(Stack *s) {
    return s->top == 0;
}

bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, int64_t x) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

bool stack_pop(Stack *s, int64_t *x) {
    if (s->top == 0) {
        return false;
    }
    *x = s->items[s->top];
    s->top -= 1;
    return true;
}

void stack_print(Stack *s) {
    printf("|");
    for (uint32_t i = 0; i < stack_size(s); i += 1) {
        printf(" %ld |", s->items[i]);
    }
    printf("\n");
    return;
}
