// Merilyn Kuo
// CSE 13S Spring 2021
// hamming.c

#include "huffman.h"
#include "node.h"
#include "pq.h"
#include "stack.h"
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *pq = pq_create(ALPHABET);
    Node *parent;
    for (uint64_t symbol = 0; symbol < ALPHABET; symbol ++) {
	if (hist[symbol] > 0) {
	    Node *n = node_create('$', hist[symbol]);
	    enqueue(pq, n);
	}
    }
    while (pq_size(pq) >= 2) {
	Node *left_child;
	Node *right_child;
	dequeue(pq, &left_child);
	dequeue(pq, &right_child);
	parent = node_join(left_child, right_child);  // do i need a pointer here
	enqueue(pq, parent);
    }
    return parent;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();



