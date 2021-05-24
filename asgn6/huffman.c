// Merilyn Kuo
// CSE 13S Spring 2021
// hamming.c

#include "huffman.h"

#include "defines.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Constructs a huffman tree given a histogram of symbols.
Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *pq = pq_create(ALPHABET);
    Node *parent;

    // creating priority queue of nodes
    for (uint64_t symbol = 0; symbol < ALPHABET; symbol++) {
        if (hist[symbol] > 0) {
            Node *n = node_create(symbol, hist[symbol]);
            enqueue(pq, n);
        }
    }

    // constructing tree with priority queue
    while (pq_size(pq) >= 2) {
        Node *left_child;
        Node *right_child;
        dequeue(pq, &left_child);
        dequeue(pq, &right_child);
        parent = node_join(left_child, right_child);
        enqueue(pq, parent);
    }
    Node *root;
    dequeue(pq, &root);
    pq_delete(&pq);
    return root;
}

// Recursive post order traversal of tree to create code table.
void post_order_traversal(Node *n, Code table[static ALPHABET], Code c) {
    if (!(n->left && n->right)) {
        table[n->symbol] = c;  // node is a leaf
    } else {
        code_push_bit(&c, 0);
        post_order_traversal(n->left, table, c);
        uint8_t popped;
        code_pop_bit(&c, &popped);
        code_push_bit(&c, 1);
        post_order_traversal(n->right, table, c);
        code_pop_bit(&c, &popped);
    }
    return;
}

// Constructs the code table.
void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    post_order_traversal(root, table, c);
    return;
}

// Reconstructs the Huffman tree given a tree dump.
Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]) {
    Stack *nodes_stack = stack_create(nbytes);
    Node *parent;

    for (uint8_t i = 0; i < nbytes; i++) {
        if (tree_dump[i] == 'L') {  // leaf node
            Node *leaf = node_create(tree_dump[i + 1], 0);
            stack_push(nodes_stack, leaf);
            i++;
        } else if (tree_dump[i] == 'I') {  // interior node
            Node *left;
            Node *right;
            stack_pop(nodes_stack, &right);
            stack_pop(nodes_stack, &left);
            parent = node_join(left, right);
            stack_push(nodes_stack, parent);
        }
    }
    Node *root;
    stack_pop(nodes_stack, &root);
    stack_delete(&nodes_stack);
    return root;
}

// Frees all allocated memory for the tree nodes.
void delete_tree(Node **root) {
    if (*root == NULL) {
        return;
    } else {
        if ((*root)->left != NULL) {
            delete_tree(&(*root)->left);
        }
        if ((*root)->right != NULL) {
            delete_tree(&(*root)->right);
        }
        node_delete(root);
    }
}
