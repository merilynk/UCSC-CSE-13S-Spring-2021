// Merilyn Kuo
// CSE 13S Spring 2021
// encode.c

#include "code.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

    printf("NODE TESTING\n");
    Node *right = node_create('$', 4);
    Node *child1 = node_create('*', 1);
    Node *child2 = node_create('*', 2);
    Node *left = node_join(child1, child2);
    Node *parent = node_join(left, right);
    node_print(parent);

    printf("\nPQ TESTING\n");
    Node *node1 = node_create('&', 1);
    //Node *node2 = node_create('&', 2);

    PriorityQueue *node_pq = pq_create(5);
    printf("empty? %d\n", pq_empty(node_pq));
    printf("full? %d\n", pq_full(node_pq));
    printf("size: %d\n", pq_size(node_pq));

    enqueue(node_pq, right);
    printf("enqueued 1: \n");
    pq_print(node_pq);
    enqueue(node_pq, child1);
    enqueue(node_pq, child2);
    enqueue(node_pq, left);
    enqueue(node_pq, parent);

    printf("Priority Queue: \n");
    pq_print(node_pq);

    printf("empty? %d\n", pq_empty(node_pq));
    printf("full? %d\n", pq_full(node_pq));
    printf("size: %d\n", pq_size(node_pq));

    Node *popped = node_create('&', 1);
    dequeue(node_pq, &popped);
    printf("popped: ");
    node_print(popped);
    printf("\n\n");
    printf("PQ after pop:\n");
    pq_print(node_pq);
    printf("empty? %d\n", pq_empty(node_pq));
    printf("full? %d\n", pq_full(node_pq));
    printf("size: %d\n", pq_size(node_pq));

    printf("enqueued again:\n");
    enqueue(node_pq, node1);
    pq_print(node_pq);

    printf("dequeued again:\n");
    dequeue(node_pq, &popped);
    printf("popped: ");
    node_print(popped);
    printf("\n");
    pq_print(node_pq);

    node_delete(&left);
    node_delete(&right);
    node_delete(&parent);
    pq_delete(&node_pq);
}
