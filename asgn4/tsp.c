// Traveling Salesman Problem
// Merilyn Kuo
// CSE 13S Spring 2021

#include "graph.h"
#include "path.h"
#include "stack.h"
#include "string.h"
#include "vertices.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "hvui:o:"
#define BUFFER  1024

int recursive_calls = 0;
bool verbose = false;

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    static uint32_t popped = 0;
    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);
    if (graph_has_edge(G, v, START_VERTEX) && (path_vertices(curr) == graph_vertices(G))) {
        path_push_vertex(curr, START_VERTEX, G);
        if ((path_length(curr) < path_length(shortest)) || path_length(shortest) == 0) {
            path_copy(shortest, curr);
            if (verbose) {
                printf("Path Length: %d\n", path_length(curr));
                path_print(curr, outfile, cities);
            }
        }
        //if (verbose) {
        //path_print(curr, outfile, cities);
        //printf("Path Length: %d\n", path_length(curr));
        //}
        path_pop_vertex(curr, &popped, G);
    }
    if (path_length(curr) > path_length(shortest) && path_length(shortest) != 0) {
        return;
    }
    recursive_calls += 1;
    //graph_mark_visited(G, v);
    //path_push_vertex(curr, v, G);
    for (uint32_t w = 0; w < graph_vertices(G); w += 1) {
        if (graph_has_edge(G, v, w) && !graph_visited(G, w)) {
            dfs(G, w, curr, shortest, cities, outfile);
        }
    }
    graph_mark_unvisited(G, v);
    path_pop_vertex(curr, &popped, G);
    return;
}

int main(int argc, char **argv) {

    int opt = 0;

    FILE *input_file = stdin;
    FILE *output_file = stdout;

    bool undirected_graph = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {
        case 'h': printf("usage\n"); break;
        case 'v': verbose = true; break;
        case 'u': undirected_graph = true; break;
        case 'i':
            input_file = fopen(optarg, "r");
            if (input_file == NULL) {
                fprintf(stderr, "Error: failed to open infile.\n");
            }
            break;
        case 'o':
            output_file = fopen(optarg, "w");
            if (input_file == NULL) {
                fprintf(stderr, "Error: failed to open infile.\n");
            }
            break;
        default: printf("usagei\n"); break;
        }
    }

    uint32_t num_cities;

    fscanf(input_file, "%d", &num_cities);
    //printf("num of vertices: %d\n", num_cities);
    if (num_cities > VERTICES) {
        fprintf(stderr, "too many vertices\n");
    }

    char *cities_list[num_cities];
    char city_name[BUFFER];
    fgets(city_name, BUFFER, input_file);
    for (uint32_t c = 0; c < num_cities; c += 1) {
        fgets(city_name, BUFFER, input_file);
        int length = strlen(city_name);
        if (city_name[length - 1] == '\n') {
            city_name[length - 1] = '\0';
        }
        cities_list[c] = strdup(city_name);
        //printf("%s\n", cities_list[c]);
    }

    Graph *G = graph_create(num_cities, undirected_graph);

    uint32_t i, j, k;
    int scanned = 0;
    while ((scanned = fscanf(input_file, "%d %d %d", &i, &j, &k)) != EOF) {
        if (scanned != 3) {
            fprintf(stderr, "Error: malformed edge.\n");
            break;
        }
        graph_add_edge(G, i, j, k);
    }

    Path *travel_path = path_create();
    Path *shortest_path = path_create();

    dfs(G, START_VERTEX, travel_path, shortest_path, cities_list, output_file);

    if (verbose) {
        printf("Path Length: %d\n", path_length(shortest_path));
    }
    path_print(shortest_path, output_file, cities_list);
    printf("Total recursive calls: %d\n", recursive_calls);

    graph_delete(&G);
    path_delete(&travel_path);
    path_delete(&shortest_path);
}
