// Graph ADT
// Merilyn Kuo
// CSE 13S Spring 2021

#include "graph.h"

#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Code from assignment pdf
struct Graph {
    uint32_t vertices; // Number of vertices in the graph
    bool undirected; // True if graph is undirected
    bool visited[VERTICES]; // Array of vertices that have been visited
    uint32_t matrix[VERTICES][VERTICES]; // Adjacency matrix representing graph
};

// Creates a graph by allocating memory  and initializing the graph members.
// vertices: number of vertices that the graph will have
// undirected: boolean value of whether the graph is undirected or not
// Returns the created graph.
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(sizeof(Graph));

    if (G) {
        G->vertices = vertices;
        G->undirected = undirected;

        for (uint32_t v = 0; v < VERTICES; v += 1) {
            G->visited[v] = false;
        }

        //G->matrix = (uint32_t *) calloc(vertices, sizeof(uint32_t));

        //if (!G->matrix) {
        //free(G);
        //G = NULL;
        //}
    }
    return G;
}

// Frees any allocated memory for the graph.
// G: graph to free
// Returns nothing.
void graph_delete(Graph **G) {
    if (*G) {
        //free((*G)->matrix);
        free(*G);
        *G = NULL;
    }
    return;
}

// Returns the number of vertices in the graph.
// G: graph to find the # of vertices of
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

// Adds an edge to the graph and the edge weight.
// G: graph to add to
// i, j: verticies of the edge
// k: weight of the edge
// Returns true/false based on success of adding the edge
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if ((i < G->vertices) && (j < G->vertices)) { // if vertices within bounds
        G->matrix[i][j] = k;
        if (G->undirected) {
            G->matrix[j][i] = k;
        }
        return true;
    } else {
        return false;
    }
}

// Returns true if the edge exists at the specified vertex.
// G: graph to check from
// i, j: vertices of the edge
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if ((i < G->vertices) && (j < G->vertices)) {
        if (G->matrix[i][j] > 0) {
            return true;
        }
    }
    return false;
}

// Returns the weight ad the specified edge or 0 if the edge DNE or is out of bounds.
// G: graph to get edge weight from
// i, j: vertices if the edge
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if ((i < G->vertices) && (j < G->vertices)) {
        return G->matrix[i][j];
    } else {
        return 0;
    }
}

// Returns true if the vertex has been visited and false if not.
// G: graph to check from
// v: vertex to check
bool graph_visited(Graph *G, uint32_t v) {
    return G->visited[v];
}

// Markes a vertex as visited if it is within bounds.
// G: graph the vertex is in
// v: vertex
// Returns nothing.
void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < VERTICES) {
        G->visited[v] = true;
    }
    return;
}

// Marks a vertex as unvisited if it is within bounds,
// G: graph the vertex is in
// v: vertex
// Returns nothing.
void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v < VERTICES) {
        G->visited[v] = false;
    }
    return;
}

// Prints the graph's members.
// G: graph to print
// Returns nothing
void graph_print(Graph *G) {
    printf("Vertices: %d\n", G->vertices);
    if (G->undirected) {
        printf("Undirected\n");
    }
    for (uint32_t i = 0; i < VERTICES; i += 1) {
        for (uint32_t j = 0; j < VERTICES; j += 1) {
            printf(" %d", G->matrix[i][j]);
        }
        printf("\n");
    }
    return;
}
