// Merilyn Kuo
// CSE 13S Spring 2021
// pq.c

#include "pq.h"
#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue {
    uint32_t head;  // index of the start of the queue
    uint32_t tail;  // index of end of queue
    uint32_t capacity;  // max queue size
    uint32_t size;  // size of queue
    Node **nodes;  // array of nodes
};

// Priority queue constructor
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (pq) {
        pq->head = 0;
        pq->tail = 0;
        pq->size = 0;
        pq->capacity = capacity;
        pq->nodes = (Node **) calloc(capacity, sizeof(Node *));
        if (!pq->nodes) {
            free(pq);
            pq = NULL;
        }
    }
    return pq;
}

// Priority queue deconstructor
void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->nodes) {
        free((*q)->nodes);
        free(*q);
        *q = NULL;
    }
    return;
}

// Returns true if queue is empty
bool pq_empty(PriorityQueue *q) {
    return q->size == 0;
}

// Returns true if queue is full
bool pq_full(PriorityQueue *q) {
    return q->size == q->capacity;
}

// Returns size of queue
uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

// Adds a node in the queue and sorts it into order
bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }
    uint32_t mark = q->tail;
    while (mark != q->head) {
        if (q->nodes[(mark + q->capacity - 1) % q->capacity]->frequency > n->frequency) {
            q->nodes[mark] = q->nodes[(mark + q->capacity - 1) % q->capacity];
            q->nodes[(mark + q->capacity - 1) % q->capacity] = n;
            mark = (n + q->capacity - 1) % q->capacity
        } else {
            break;
        }
    }
    q->nodes[mark] = n;
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;
    return true;
}

// Removes the node at the head of the queue
bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }
    *n = q->nodes[q->head];
    q->size -= 1;
    q->head += 1;
    if (q->head == q->capacity) {
        q->head = 0;
    }
    return true;
}

// Prints the priority queue.
void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0, j = q->head; i < q->size; i += 1, j = (1 + i) % q->capacity) {
        node_print(q->nodes[j]);
    }
}
