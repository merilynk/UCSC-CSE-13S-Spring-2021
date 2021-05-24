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

// Walks the tree to write out the symbols.
void tree_walk(int infile, int outfile, Node *n, uint64_t file_size) {
    uint8_t bit;
    uint64_t symbols_written = 0;
    while (symbols_written != file_size) {
        read_bit(infile, &bit);
        if (!(n->left && n->right)) {
            uint8_t buf[1] = { n->symbol };
            write_bytes(outfile, buf, 1);
        } else {
            if (bit == 0) {
                tree_walk(infile, outfile, n->left, file_size);
            } else if (bit == 1) {
                tree_walk(infile, outfile, n->right, file_size);
            }
        }
    }
}

// Prints help message.
void print_help(void) {
    printf("SYNOPSIS\n"
           "A Huffman decoder.\n\n"
           "USAGE\n"
           "./encode [-h] [-v] [-i infile] [-o outfile]\n\n"
           "OPTIONS\n"
           "  -h            Program usage and help.\n"
           "  -v            Print decompression statistics.\n"
           "  -i infile     Input data to decompress.\n"
           "  -o outfile    Output of decompressed data.\n");
    return;
}

int main(int argc, char **argv) {

    int infile = STDIN_FILENO; // default input
    int outfile = STDOUT_FILENO; // default output

    int opt = 0;
    bool verbose = false; // true if printing decompression stats

    // parse command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {
        case 'h': print_help(); return 0;
        case 'i':
            infile = open(optarg, O_RDONLY); // open file for reading
            if (infile < 0) {
                fprintf(stderr, "Error: cannot open infile\n");
            }
            break;
        case 'o':
            outfile = open(
                optarg, O_WRONLY | O_CREAT); // open file for writing, create if not existing yet
            if (outfile < 0) {
                fprintf(stderr, "Error cannot open outfile\n");
            }
            break;
        case 'v': verbose = true; break;
        default: print_help(); return 0;
        }
    }

    // Read in the Header
    Header h;
    read_bytes(infile, (uint8_t *) &h, sizeof(h));

    // verify magic number
    if (h.magic != MAGIC) {
        fprintf(stderr, "Invalid magic number.\n");
        return 0;
    }

    fchmod(outfile, h.permissions); // setting file permissions of outfile

    uint8_t dumped_tree[h.tree_size]; // array to store dumped tree from infile
    read_bytes(infile, dumped_tree, h.tree_size); // reading in dumped tree

    Node *root;
    root = rebuild_tree(h.tree_size, dumped_tree); // reconstruct huffman tree

    // walk down tree to write out symbols
    tree_walk(infile, outfile, root, h.file_size);

    // print stats
    if (verbose) {
        fprintf(stderr,
            "Compressed file size:  bytes\nDecompressed file size:  bytes\nSpace saving:  %%\n");
    }

    // close files
    close(infile);
    close(outfile);

    // free memory
    delete_tree(&root);

    return 0;
}
