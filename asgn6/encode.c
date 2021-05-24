// Merilyn Kuo
// CSE 13S Spring 2021
// encode.c

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

// Writes out a dump of the tree to the outfile.
void tree_dump(Node *n, int outfile) {
    if (!(n->left && n->right)) {
        uint8_t tree_buf[2] = { 'L', n->symbol };
        write_bytes(outfile, tree_buf, 2);
    } else {
        tree_dump(n->left, outfile);
        tree_dump(n->right, outfile);
        uint8_t tree_buf[1] = { 'I' };
        write_bytes(outfile, tree_buf, 1);
    }
    return;
}

// Prints help message.
void print_help(void) {
    printf("SYNOPSIS\n"
           "A Huffman encoder.\n\n"
           "USAGE\n"
           "./encode [-h] [-i infile] [-o outfile]\n\n"
           "OPTIONS\n"
           "  -h            Program usage and help.\n"
           "  -v            Print compression statistics.\n"
           "  -i infile     Input data to compress.\n"
           "  -o outfile    Output of compressed data.\n");
    return;
}

int main(int argc, char **argv) {

    int infile = STDIN_FILENO; // default input
    int outfile = STDOUT_FILENO; // default output

    int opt = 0;
    bool verbose = false; // true if printing compression stats

    // parse command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {
        case 'h': print_help(); return 0;
        case 'i':
            infile = open(optarg, O_RDONLY); // open file to read
            if (infile < 0) {
                fprintf(stderr, "Error: cannot open infile\n");
            }
            break;
        case 'o':
            outfile = open(optarg, O_WRONLY | O_CREAT); // open/create file to write to
            if (outfile < 0) {
                fprintf(stderr, "Error cannot open outfile\n");
            }
            break;
        case 'v': verbose = true; break;
        default: print_help(); return 0;
        }
    }

    uint64_t histogram[ALPHABET] = { 0 }; // histogram

    int b = 0; // num of bytes read
    uint8_t buffer[BLOCK] = { 0 };

    //create histogram
    while ((b = read_bytes(infile, buffer, BLOCK)) > 0) {
        for (uint64_t i = 0; i < BLOCK; i += 1) {
            histogram[buffer[i]] += 1;
        }
    }

    histogram[0]++;
    histogram[ALPHABET - 1]++;

    Node *root;
    root = build_tree(histogram); // construct huffman tree

    // construct table of codes
    Code code_table[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        code_table[i] = code_init();
    }
    build_codes(root, code_table);

    // construct header
    Header h;
    h.magic = MAGIC;
    struct stat statbuf;
    fstat(infile, &statbuf); // get infile file permissions
    h.permissions = statbuf.st_mode;
    fchmod(outfile, statbuf.st_mode); // setting file permissions of outfile
    // get number of unique symbols in histogram
    int unique_symbols = 0;
    for (uint64_t s = 0; s < ALPHABET; s += 1) {
        if (histogram[s] > 0) {
            unique_symbols += 1;
        }
    }
    h.tree_size = (3 * unique_symbols) - 1;
    h.file_size = statbuf.st_size;

    write_bytes(outfile, (uint8_t *) &h, sizeof(h)); // write header to outfile

    tree_dump(root, outfile); // print tree out to outfile

    b = 0;
    lseek(infile, 0, SEEK_SET); // offset file to beginning
    uint8_t c_buf[BLOCK];

    // read from beginning of infile and write out code for each byte
    while ((b = read_bytes(infile, c_buf, BLOCK)) > 0) {
        for (int symbol = 0; symbol < b; symbol += 1) {
            write_code(outfile, &code_table[c_buf[symbol]]);
        }
    }
    flush_codes(outfile); // write out remaining bytes

    if (verbose) { // print stats
        fprintf(stderr,
            "Uncompressed file size:  bytes\nCompressed file size:  bytes\nSpace saving:  %%\n");
    }

    // close files
    close(infile);
    close(outfile);

    // free memory
    delete_tree(&root);

    return 0;
}
