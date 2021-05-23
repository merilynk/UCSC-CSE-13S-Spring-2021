// Merilyn Kuo
// CSE 13S Spring 2021
// decode.c

#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

int main(int argc, char **argv) {

    int infile = STDIN_FILENO; // default input
    int outfile = STDOUT_FILENO; // default output

    int opt = 0;
    bool verbose = false; // true if printing decompression stats
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

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
        case 'v': verbose = true; break;
        default:
            // print help
            break;
        }
    }

    // Read in the Header
    Header h;
    read_bytes(infile, (uint8_t *) &h, sizeof(Header));

    // verify magic number
    if (h.magic != MAGIC) {
	fprintf(stderr, "Invalid magic number.\n");
	return 0;
    }

    fchmod(outfile, h.permissions);  // setting file permissions of outfile

    uint8_t dumped_tree[tree_size];  // array to store dumped tree from infile
    read_bytes(infile, dumped_tree, tree_size);  // reading in dumped tree

    Node *root;
    root = rebuild_tree(tree_size, dumped_tree);  // reconstruct huffman tree

    // walk down tree
    uint8_t bit;
    while (read_bit(infile, bit)) {
	if (bit == 0) {


    return 0;
}
