// Merilyn Kuo
// CSE 13S Spring 2021
// decode.c

#include "huffman.h"
#include "io.h"
#include "node.h"
#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

int main(int argc, char **argv) {

    FILE *infile = stdin;  // default input
    FILE *outfile = stdout;  // default output

    int opt = 0;
    bool verbose = false;  // true if printing decompression stats
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


    return 0;
}
