// Merilyn Kuo
// CSE 13S Spring 2021
// node.c

#include "node.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    if (n) {
        n->symbol = symbol;
        n->frequency = frequency;
    }
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free(*n);
        *n = NULL;
    }
    return;
}

Node *node_join(Node *left, Node *right) {
    Node *parent = node_create('$', left->frequency + right->frequency);
    parent->left = left;
    parent->right = right;
    return parent;
}

void node_print(Node *n) {
    printf("Symbol: %u", n->symbol);
    printf(" Frequency: %lu\n", n->frequency);
    if (n->left) {
        printf("Left child: ");
        node_print(n->left);
    }
    if (n->right) {
        printf("Right child: ");
        node_print(n->right);
    }
    return;
}
