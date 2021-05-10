// Merilyn Kuo
// CSE 13S Spring 2021
// Encode

#include "bm.h"
#include "bv.h"
#include "hamming.h"
#include "helper.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:"

// Prints help message.
void print_help(void) {
    printf("SYNOPSIS\n"
           "A Hamming(8, 4) systematic code generator.\n\n"
           "USAGE\n"
           "./encode [-h] [-i infile] [-o outfile]\n\n"
           "OPTIONS\n"
           "  -h            Program usage and help.\n"
           "  -i infile     Input data to encode.\n"
           "  -o outfile    Output of encoded data.\n");
    return;
}

int main(int argc, char **argv) {

    FILE *input_file = stdin; // default input
    FILE *output_file = stdout; // default output
    struct stat statbuf; // code from example in assignment pdf

    // Parsing command line options
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {
        case 'h':
            print_help();
            return 0;
            break;
        case 'i':
            input_file = fopen(optarg, "rb"); // open file to read from
            if (input_file == NULL) {
                fprintf(stderr, "Error: failed to open infile\n");
            } else {
                // get file permissions
                fstat(fileno(input_file), &statbuf); // code from example in assignment pdf
            }
            break;
        case 'o':
            output_file = fopen(optarg, "wb"); // open file to write to
            if (output_file == NULL) {
                fprintf(stderr, "Error: failed to open outfile\n");
            } else {
                // set file permissions
                fchmod(fileno(output_file), statbuf.st_mode); // code form example in assignment pdf
            }
            break;
        default: print_help(); break;
        }
    }

    BitMatrix *G = create_generator_matrix(); // create generator matrix

    // getting input
    int c = 0;
    while ((c = fgetc(input_file)) != EOF) {
        uint8_t msg1 = lower_nibble(c); // get lower nibble of byte
        uint8_t msg2 = upper_nibble(c); // get upper nibble of byte
        uint8_t code1 = ham_encode(G, msg1); // encode
        uint8_t code2 = ham_encode(G, msg2);
        fputc(code1, output_file); // print to output
        fputc(code2, output_file);
    }

    // close files
    if (input_file && output_file) {
        fclose(input_file);
        fclose(output_file);
    }

    // free memory allocated
    bm_delete(&G);

    return 0;
}
