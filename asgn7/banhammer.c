// Merilyn Kuo
// CSE 13S Spring 2021
// Banhammer

#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <assert.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define WORD    "([a-zA-Z0-9_]+(('|-)[a-z0-9A-Z_]+)*)"
#define OPTIONS "ht:f:ms"
#define BUFFER  1024

// Prints a help message.
void print_help_message(void) {
    fprintf(stderr, "SYNOPSIS\n");
    fprintf(stderr, "  A word filtering program for GPRSC.\n");
    fprintf(stderr, "  Filters out and reports bad words parsed from stdin.\n");
    fprintf(stderr, "\nUSAGE\n");
    fprintf(stderr, "  ./banhammer [-hsm] [-t size] [-f size]\n");
    fprintf(stderr, "\nOPTIONS\n");
    fprintf(stderr, "  -h           Program usage and help.\n");
    fprintf(stderr, "  -s           Print program statistics.\n");
    fprintf(stderr, "  -m           Enable move-to-front rule.\n");
    fprintf(stderr, "  -t size      Specify hash table size (default: 10000).\n");
    fprintf(stderr, "  -f size      Specify bloom filter size (default: 2^20).\n");
    return;
}

int main(int argc, char **argv) {

    int opt = 0;
    bool stats = false; // true if printing compression statistics
    uint32_t size_ht = 10000; // default size of ht
    uint32_t size_bf = 1048576; // default size of bf
    bool mtf_rule = false; // true if mtf enabled

    // parse command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': print_help_message(); return 0;
        case 't':
            sscanf(optarg, "%u", &size_ht);
            if (size_ht <= 0) {
                fprintf(stderr, "Invalid hash table size.\n");
                return 0;
            }
            break;
        case 'f':
            sscanf(optarg, "%u", &size_bf);
            if (size_bf <= 0) {
                fprintf(stderr, "Invalid bloom filter size.\n");
                return 0;
            }
            break;
        case 'm': mtf_rule = true; break;
        case 's': stats = true; break;
        default: print_help_message(); return 0;
        }
    }

    BloomFilter *bloom_filter = bf_create(size_bf);
    HashTable *hash_table = ht_create(size_ht, mtf_rule);

    // read in badspeak words
    FILE *badspeak_file = fopen("badspeak.txt", "r");
    char badspeak[BUFFER];
    while (fscanf(badspeak_file, "%s", badspeak) != EOF) {
        bf_insert(bloom_filter, badspeak);
        ht_insert(hash_table, badspeak, NULL);
    }

    // read in oldspeak/newspeak words
    FILE *newspeak_file = fopen("newspeak.txt", "r");
    char oldspeak[BUFFER];
    char newspeak[BUFFER];
    while (fscanf(newspeak_file, "%s %s", oldspeak, newspeak) != EOF) {
        bf_insert(bloom_filter, oldspeak);
        ht_insert(hash_table, oldspeak, newspeak);
    }

    // based off example program using parsing module in assignment pdf
    regex_t reg_ex;
    if (regcomp(&reg_ex, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    bool thoughtcrime = false; // true if thoughtcrime committed
    bool rightspeak_counseling = false; // true if requires rightspeak counseling

    LinkedList *badspeak_list = ll_create(mtf_rule); // list of badspeak words citizen used
    LinkedList *oldspeak_list
        = ll_create(mtf_rule); // list of oldspeak words used w/ newspeak translation

    // based off example program using parsing module in assignment pdf
    char *word = NULL;
    while ((word = next_word(stdin, &reg_ex)) != NULL) { // read in words

	for (int i = 0; word[i] != '\0'; i ++) {
	    word[i] = tolower(word[i]);  // making the word all lowercase
	}

	if (bf_probe(bloom_filter, word)) { // check is possible badspeak or oldspeak
            Node *looked_up = ht_lookup(hash_table, word); // confirm word is badspeak or oldspeak

            if (looked_up != NULL) {

                if (looked_up->newspeak == NULL) {
                    thoughtcrime = true; // citizen commited thoughtcrime
                    ll_insert(badspeak_list, word, NULL);
                } else {
                    rightspeak_counseling = true; // citizen requires counseling on rightspeak
                    ll_insert(oldspeak_list, word, looked_up->newspeak);
                }
            }
        }
    }

    if (stats) { // print statistics if command line option specified

        printf("Seeks: %lu\n", seeks);
        printf("Average seek length: %lf\n", (double) links / (double) seeks);
        printf("Hash table load: %lf%%\n",
            100.0 * ((double) ht_count(hash_table) / (double) ht_size(hash_table)));
        printf("Bloom filter load: %lf%%\n",
            100.0 * ((double) bf_count(bloom_filter) / (double) bf_size(bloom_filter)));

    } else { // print verdict messages

        if (thoughtcrime && rightspeak_counseling) {
            fprintf(stdout, "%s", mixspeak_message);
            ll_print(badspeak_list);
            ll_print(oldspeak_list);
        } else if (thoughtcrime) {
            fprintf(stdout, "%s", badspeak_message);
            ll_print(badspeak_list);
        } else if (rightspeak_counseling) {
            fprintf(stdout, "%s", goodspeak_message);
            ll_print(oldspeak_list);
        }
    }

    // close files and free memory
    fclose(badspeak_file);
    fclose(newspeak_file);
    clear_words();
    regfree(&reg_ex);
    ll_delete(&badspeak_list);
    ll_delete(&oldspeak_list);
    ht_delete(&hash_table);
    bf_delete(&bloom_filter);
}
