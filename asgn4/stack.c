// Stack ADT
// Merilyn Kuo
// CSE 13S Spring 2021

#include "stack.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Code based on my Assignment 3 Code.

// Structure definition of a stack.
struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

// Creates a stack by allocating memory and initializing struct members.
// capacity: max number of items stack can have
// Returns the created stack.
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) { // memory allocation successful
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) { // memiory allocation not successful
            free(s);
            s = NULL;
        }
    }
    return s;
}

// Deletes the stack by free any allocated memory and setting pointers to null.
// s: stack to delete
// Returns nothing,
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

// Checks if stack is empty.
// s: stack
// Returns true or false.
bool stack_empty(Stack *s) {
    return s->top == 0;
}

// Checks if stack is full.
// s: stack
// Returns true or false.
bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

// Gets the size of the stack.
// s: stack
// Returns the size.
uint32_t stack_size(Stack *s) {
    return s->top;
}

// Pushes an item to the stack.
// s: stack
// x: item
// Returns true if successful, false if stack was full.
bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

// Looks at the item at the top of the stack and passes it though a pointer.
// s: stack
// x: item at the top of the stack
// Returns true if successful, false if stack was empty.
bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    *x = s->items[s->top - 1];
    return true;
}

// Pops an item from the stack and passes the popped item through a pointer.
// s: stack
// x: popped item
// Returns true if successful, false if stack was empty.
bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

// Makes a copy of a stack.
// dst: copy of the stack
// src: stack to make a copy of
// Returns nothing.
void stack_copy(Stack *dst, Stack *src) {
    uint32_t popped = 0;
    for (uint32_t i = 0; i < dst->capacity; i += 1) {
        stack_pop(dst, &popped); // remove any items already in the stack copy
    }
    for (uint32_t i = 0; i < src->capacity; i += 1) {
        stack_push(dst, src->items[i]); // copy items
    }
    dst->top = src->top;
    return;
}

// Code from Assignment 4 PDF
// Prints the stack.
// s: stack
// outfile: where to print to
// cities: array of city names
// Returns nothing.
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
    return;
}
