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

int recursive_calls = 0; // counter for recursive calls
bool verbose = false; // verbose printing: true means enabled

// Recursive DFS Algorithm to find the shortest Hamiltonian path.
//
// G: graph
// v: vertex
// curr: current path of travel
// shortest: shortest path
// cities: array of city names
// outfile: file to print outputs to
//
// Returns nothing.
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {

    if (path_length(curr) >= path_length(shortest) && path_length(shortest) != 0) {
        return; // current path length greater so don't continue recursing
    }

    recursive_calls += 1;
    static uint32_t popped = 0; // for popped values
    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);

    // Checking for Hamiltonian path.
    if (graph_has_edge(G, v, START_VERTEX) && (path_vertices(curr) == graph_vertices(G))) {

        path_push_vertex(curr, START_VERTEX, G); // Add starting vertex to end of path

        // Checking for shortest path.
        if ((path_length(curr) < path_length(shortest)) || path_length(shortest) == 0) {

            path_copy(shortest, curr); // new shortest path

            if (verbose) {
                fprintf(outfile, "Path Length: %d\n", path_length(curr));
                fprintf(outfile, "Path: ");
                path_print(curr, outfile, cities);
            }
        }

        path_pop_vertex(curr, &popped, G);
    }

    // checking for other vertices connected to current vertex
    for (uint32_t w = 0; w < graph_vertices(G); w += 1) {
        if (graph_has_edge(G, v, w) && !graph_visited(G, w)) {
            dfs(G, w, curr, shortest, cities, outfile);
        }
    }

    graph_mark_unvisited(G, v);
    path_pop_vertex(curr, &popped, G);
    return;
}

// Prints help message.
// Returns nothing.
void print_help(void) {

    printf("SYNOPSIS\n"
           "  Traveling Salesman Problem using DFS.\n\n"
           "USAGE\n"
           "  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n"
           "OPTIONS\n"
           "  -u             Use undirected graph.\n"
           "  -v             Enable verbose printing.\n"
           "  -h             Program usage and help.\n"
           "  -i infile      Input containing graph (default: stdin)\n"
           "  -o outfile     Output of computed path (default: stdout)\n");
    return;
}

int main(int argc, char **argv) {

    int opt = 0;
    recursive_calls = 0;

    FILE *input_file = stdin; // default input
    FILE *output_file = stdout; // default output

    bool undirected_graph = false;

    // Parsing command line options.
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {
        case 'h':
            print_help();
            return 0;
            break;
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
                fprintf(stderr, "Error: failed to open outfile.\n");
            }
            break;
        default: print_help(); break;
        }
    }

    uint32_t num_cities;

    // Get number of vertices in graph.
    fscanf(input_file, "%u", &num_cities);
    if (num_cities > VERTICES) {
        // invalid number of vertices
        fprintf(stderr, "Error: malformed number of vertices.\n");
        return 0;
    }
    if (num_cities <= 1) {
        // no vertices
        fprintf(stderr, "There is no where to go.\n");
        return 0;
    }

    // Get names of cities.
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
    }

    Graph *G = graph_create(num_cities, undirected_graph);

    // Get edges of the graph and add to graph.
    uint32_t i, j, k;
    int scanned = 0;
    while ((scanned = fscanf(input_file, "%u %u %u", &i, &j, &k)) != EOF) {
        if (scanned != 3) {
            // incorrect format
            fprintf(stderr, "Error: malformed edge.\n");
            return 0;
        }
        graph_add_edge(G, i, j, k);
    }

    // Create 2 empty paths.
    Path *travel_path = path_create(); // path of travel
    Path *shortest_path = path_create(); // shortest path

    // depth first search recursive algorithm
    dfs(G, START_VERTEX, travel_path, shortest_path, cities_list, output_file);

    // print out shortest path and # recursive calls
    fprintf(output_file, "Path Length: %d\n", path_length(shortest_path));
    fprintf(output_file, "Path: ");
    path_print(shortest_path, output_file, cities_list);
    fprintf(output_file, "Total recursive calls: %d\n", recursive_calls);

    // free any allocated memory
    graph_delete(&G);
    path_delete(&travel_path);
    path_delete(&shortest_path);
    for (uint32_t c = 0; c < num_cities; c += 1) {
        free(cities_list[c]);
        cities_list[c] = NULL;
    }
    free(*cities_list);
    *cities_list = NULL;

    // close files
    if (input_file && output_file) {
        fclose(input_file);
        fclose(output_file);
    }

    return 0;
}
