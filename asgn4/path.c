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

// Creates path by allocating memeory and initalizing structure members.
// Returns the created path.
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

// Deletes the path by freeing any memeory allocated and setting pointers to null.
// p: path to delete
// Returns nothing.
void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        stack_delete(&((*p)->vertices));
        free(*p);
        *p = NULL;
    }
}

// Adds a vertex to the path as well as the length.
// p: path
// v: vertex to add
// G: graph
// Returns true if successful.
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t x;
    bool peeked = stack_peek(p->vertices, &x);
    bool pushed = stack_push(p->vertices, v);
    if (peeked && pushed) {
        (p->length) += graph_edge_weight(G, x, v);
        return true;
    } else {
        return false;
    }
}

// Removes a vertex from the path and decreseas path length by edge weight.
// p: path
// v: popped vertex
// G: graph
// Returns true if successful.
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

// Returns the number of vertices in the path, p.
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

// Returns the length of the path, p.
uint32_t path_length(Path *p) {
    return p->length;
}

// Makes a copy of the path.
// dst: copied path
// src: path to copy
// Returns nothing.
void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
    return;
}

// Prints the path.
// p: path to print
// outfile: where to print to
// cities: array of city names
void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
    return;
}
