// Merilyn Kuo
// CSE 13S Spring 2021
// encode.c

#include "code.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"
#include "header.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define OPTIONS "hi:o:v"

int main(int argc, char **argv) {

    FILE *infile = stdin;  // default input
    FILE *outfile = stdout;  // default output

    int opt = 0;
    bool verbose = false;  // true if printing compression stats
    while((opt = getopt(argc, argv, OPTIONS)) != -1) {

	switch (opt) {
	case 'h':
	    // print help msg
	    return 0;
	    break;
	case 'i':
	    infile = fopen(optarg, "rb");
	    if (infile == NULL) {
		fprintf(stderr, "Error: cannot open infile\n");
	    }
	    break;
	case 'o':
	    outfile = fopen(optarg, "wb");
	    if (outfile == NULL) {
		fprintf(stderr, "Error cannot open outfile\n");
	    }
	    break;
	case 'v':
	    verbose = true;
	    break;
	default:
	    // print help
	    break;
	}
    }

    read_bytes()

    return 0;
}
