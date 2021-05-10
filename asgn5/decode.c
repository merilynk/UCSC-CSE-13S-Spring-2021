// Merilyn Kuo
// CSE 13S Spring 2021
// Decode

#include "bm.h"
#include "bv.h"
#include "hamming.h"
#include "helper.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

// Prints help message.
void print_help(void) {
    printf("SYNOPSIS\n"
           "A Hamming(8, 4) systematic code decoder.\n\n"
           "USAGE\n"
           "./decode [-h] [-v] [-i infile] [-o outfile]\n\n"
           "OPTIONS\n"
           "  -h            Program usage and help.\n"
           "  -v            Print statistics of decoding to stderr.\n"
           "  -i infile     Input data to decode.\n"
           "  -o outfile    Output of decoded data.\n");
    return;
}

int main(int argc, char **argv) {

    // initialize statistic collection variables
    total_bytes_processed = 0;
    uncorrected_errors = 0;
    corrected_errors = 0;

    FILE *input_file = stdin; // default input
    FILE *output_file = stdout; // default output
    struct stat statbuf; // code from example in assignment pdf

    bool verbose = false; // true if verbose printing is enabled

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
        case 'v': verbose = true; break;
        default: print_help(); break;
        }
    }

    BitMatrix *Ht = create_H_transpose_matrix(); // create H transpose matrix

    // getting input
    int c = 0;
    uint8_t msg1 = 0;
    uint8_t msg2 = 0;

    while ((c = fgetc(input_file)) != EOF) {
        total_bytes_processed += 1;
        uint8_t code1 = lower_nibble(c); // get lower nibble of byte
        uint8_t code2 = upper_nibble(c); // get upper nibble of byte
        ham_decode(Ht, code1, &msg1); // decode
        ham_decode(Ht, code2, &msg2);
        fputc(pack_byte(msg2, msg1), output_file); // print to output
    }

    if (verbose) {
        fprintf(stderr, "Total bytes processed: %d\n", total_bytes_processed);
        fprintf(stderr, "Uncorrected errors: %d\n", uncorrected_errors);
        fprintf(stderr, "Corrected errors: %d\n", corrected_errors);
        fprintf(stderr, "Error rate: %f\n", (double) uncorrected_errors / total_bytes_processed);
    }

    // close files
    if (input_file && output_file) {
        fclose(input_file);
        fclose(output_file);
    }

    // free memory allocated
    bm_delete(&Ht);

    return 0;
}
