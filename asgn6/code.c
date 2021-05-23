// Merilyn Kuo
// CSE 13S Spring 2021
// code.c

#include "code.h"

#include "defines.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Code code_init(void) {
    static Code c;
    c.top = 0;
    memset(c.bits, 0, sizeof(c.bits));
    return c;
}

uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    return c->top == 0;
}

bool code_full(Code *c) {
    return c->top == MAX_CODE_SIZE;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    c->bits[c->top] = bit;
    c->top += 1;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    c->top -= 1;
    *bit = c->bits[c->top];
    return true;
}

void code_print(Code *c) {
    printf("Top: %u\n", c->top);
    for (uint8_t i = 0; i < c->top; i++) {
        printf("  %u: %u", i, c->bits[i]);
    }
    printf("\n");
}
