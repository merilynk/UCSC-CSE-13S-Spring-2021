// Merilyn Kuo
// CSE 13S Spring 2021
// encode.c

#include "code.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define OPTIONS "hi:o:v"

void tree_dump(Node *n, int outfile) {
    if (!(n->left && n->right)) {
	uint8_t tree_buf[2] = {'L', n->symbol };
	write_bytes(outfile, tree_buf, 2);
    }
    else {
	tree_dump(n->left, outfile);
	tree_dump(n->right, outfile);
	uint8_t tree_buf[1] = { 'I' };
	write_bytes(outfile, tree_buf, 1);
    }
    return;
}

int main(int argc, char **argv) {

    int infile = STDIN_FILENO;  // default input
    int outfile = STDOUT_FILENO;  // default output

    int opt = 0;
    bool verbose = false;  // true if printing compression stats
    while((opt = getopt(argc, argv, OPTIONS)) != -1) {

	switch (opt) {
	case 'h':
	    // print help msg
	    return 0;
	    break;
	case 'i':
	    infile = open(optarg, O_RDONLY);
	    if (infile < 0) {
		fprintf(stderr, "Error: cannot open infile\n");
	    }
	    break;
	case 'o':
	    outfile = open(optarg, O_WRONLY | O_CREAT);
	    if (outfile < 0) {
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

    uint64_t histogram[ALPHABET];  // histogram

    int b = 0;  // num of bytes read
    uint8_t buffer[BLOCK];

    //create histogram
    while ((b = read_bytes(infile, buffer, BLOCK)) > 0) {
	for (uint64_t i = 0; i < BLOCK; i += 1) {
	    histogram[buffer[i]] += 1;
	}
    }

    histogram[0] ++;
    histogram[ALPHABET - 1] ++;

    build_tree(histogram);  // construct huffman tree

    // construct table of codes
    Code code_table[ALPHABET];
    Node *root = NULL;
    build_codes(root, code_table);

    // construct header
    Header h;
    h.magic = MAGIC;
    struct stat statbuf;
    fstat(infile, &statbuf);  // get infile file permissions
    h.permissions = statbuf.st_mode;
    fchmod(outfile, statbuf.st_mode);  // setting file permissions of outfile
    // get number of unique symbols in histogram
    int unique_symbols = 0;
    for (uint64_t s = 0; s < ALPHABET; s += 1) {
	if (histogram[s] > 0) {
	    unique_symbols += 1;
	}
    }
    h.tree_size = (3 * unique_symbols) - 1;
    h.file_size = statbuf.st_size;

    write_bytes(outfile, (uint8_t *) &h, sizeof(Header));  // write header to outfile

    tree_dump(root, outfile);  // print tree out to outfile

    for (uint64_t c = 0; c < ALPHABET; c += 1) {
	write_code(outfile, &code_table[c]);
    }
    flush_codes(outfile);

    close(infile);
    close(outfile);

    // free memory
    delete_tree(&root);

    return 0;
}
