// Merilyn Kuo
// CSE 13S Spring 2021
// encode.c

#define __DEBUG__

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
#ifdef __DEBUG__
	fprintf(stderr, "%c%c", 'L', n->symbol);
#endif
    }
    else {
	tree_dump(n->left, outfile);
	tree_dump(n->right, outfile);
	uint8_t tree_buf[1] = { 'I' };
	write_bytes(outfile, tree_buf, 1);
#ifdef __DEBUG__
	fprintf(stderr, "%c", 'I');
#endif
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

    uint64_t histogram[ALPHABET] = {0};  // histogram

    int b = 0;  // num of bytes read
    uint8_t buffer[BLOCK] = {0};
#ifdef __DEBUG__
    fprintf(stderr, "loading...");
#endif
    //create histogram
    while ((b = read_bytes(infile, buffer, BLOCK)) > 0) {
	for (uint64_t i = 0; i < BLOCK; i += 1) {
	    histogram[buffer[i]] += 1;
	}
    }
#ifdef __DEBUG__
    fprintf(stderr,"done\n");
#endif

    histogram[0] ++;
    histogram[ALPHABET - 1] ++;


#ifdef __DEBUG__
    fprintf(stderr, "building tree...");
#endif
    Node *root;
    root = build_tree(histogram);  // construct huffman tree

#ifdef __DEBUG__
    fprintf(stderr, "done\n");
#endif

    // construct table of codes
#ifdef __DEBUG__
    fprintf(stderr, "creating code tables...");
#endif
    Code code_table[ALPHABET];
    for(int i = 0; i < ALPHABET; i++){
	code_table[i] = code_init();
    }
    build_codes(root, code_table);

#ifdef __DEBUG__
    fprintf(stderr, "done.\n");
#endif


#ifdef __DEBUG__
    fprintf(stderr, "writing header...");
#endif
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

    write_bytes(outfile, (uint8_t *) &h, sizeof(h));  // write header to outfile

#ifdef __DEBUG__
    fprintf(stderr, "size of header = %lu size of file: %lu..", sizeof(h), h.file_size);
    fprintf(stderr, "done\n");
#endif


#ifdef __DEBUG__
    fprintf(stderr, "writing tree...");
#endif
    tree_dump(root, outfile);  // print tree out to outfile

#ifdef __DEBUG__
    fprintf(stderr, "done\n");
#endif

#ifdef __DEBUG__
    fprintf(stderr, "writing compressed file...");
#endif
    b = 0;
    lseek(infile, 0, SEEK_SET);
    uint8_t c_buf[BLOCK];
#ifdef __DEBUG__
    //fprintf(stderr, "bytes read: %u", (b = read_bytes(infile, c_buf, BLOCK)));
#endif
    while ((b = read_bytes(infile, c_buf, BLOCK)) > 0) {
#ifdef __DEBUG__
	fprintf(stderr, "bytes: %u ", b);
	fprintf(stderr, "reading from infile ");
#endif
	for (int symbol = 0; symbol < b; symbol += 1) {
	    write_code(outfile, &code_table[c_buf[symbol]]);
#ifdef __DEBUG__
	    fprintf(stderr, ".");
	    fprintf(stderr, "%d: %d", symbol, c_buf[symbol]);
	    code_print(&code_table[c_buf[symbol]]);
#endif
	}
    }
    flush_codes(outfile);
#ifdef __DEBUG__
    fprintf(stderr, "done.\n");
    fprintf(stderr, "finalizing...");
#endif
    close(infile);
    close(outfile);

#ifdef __DEBUG__
    fprintf(stderr, "done\n");
#endif
    // free memory
    delete_tree(&root);

    return 0;
}
