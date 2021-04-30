// Path ADT
// Merilyn Kuo
// CSE 13S Spring 2021

#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Code for structure definition from Assignment PDF
struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->length = 0;
        p->vertices = stack_create(VERTICES);
        if (!p->vertices) {
            free(p->vertices);
            free(p);
            p = NULL;
        }
    }
    return p;
}

void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        stack_delete(&((*p)->vertices));
        free(*p);
        *p = NULL;
    }
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t x;
    bool pushed = stack_push(p->vertices, v);
    bool peeked = stack_peek(p->vertices, &x);
    if (pushed && peeked) {
        (p->length) += graph_edge_weight(G, x, v);
        return true;
    } else {
        return false;
    }
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t x;
    bool popped = stack_pop(p->vertices, v);
    bool peeked = stack_peek(p->vertices, &x);
    if (popped && peeked) {
        (p->length) -= graph_edge_weight(G, x, *v);
        return true;
    } else {
        return false;
    }
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
    return;
}
