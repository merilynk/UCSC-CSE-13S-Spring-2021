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
    uint32_t head;
    uint32_t tail;
    uint32_t capacity;
    uint32_t size;
    Node **nodes;
};

#define next(q, n) ((n + 1) % q->capacity)
#define prev(q, n) ((n + q->capacity - 1) % q->capacity)

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

void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->nodes) {
        free((*q)->nodes);
        free(*q);
        *q = NULL;
    }
    return;
}

bool pq_empty(PriorityQueue *q) {
    return q->size == 0;
}

bool pq_full(PriorityQueue *q) {
    return q->size == q->capacity;
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }
    uint32_t mark = q->tail;
#ifdef __DEBUG__
    printf("enquing, head: %d, tail: %d\n", q->head, q->tail);
#endif
    while (mark != q->head) {
        if (q->nodes[(mark + q->capacity - 1) % q->capacity]->frequency > n->frequency) {
            q->nodes[mark] = q->nodes[(mark + q->capacity - 1) % q->capacity];
            q->nodes[(mark + q->capacity - 1) % q->capacity] = n;
            mark = prev(q, mark);
        } else {
#ifdef __DEBUG__
            printf("location was found before head: %d\n", (mark + q->capacity - 1) % q->capacity);
            node_print(q->nodes[(mark + q->capacity - 1) % q->capacity]);
#endif
            break;
        }
    }
#ifdef __DEBUG__
    printf("mark is :%d\n", mark);
#endif
    q->nodes[mark] = n;
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;
    return true;
}

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

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0, j = q->head; i < q->size; i += 1, j = (1 + i) % q->capacity) {
        node_print(q->nodes[j]);
    }
}
