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
#include <unistd.h>

#define WORD    "[a-zA-Z0-9'\\-_]+"
#define OPTIONS "ht:f:ms"
#define BUFFER  1024

//#define __DEBUG__

int main(int argc, char **argv) {

    int opt = 0;
    bool stats = false; // true if printing compression statistics
    uint32_t size_ht = 10000; // default size of ht
    uint32_t size_bf = 2 << 20; // default size of bf
    bool mtf_rule = false; // true if mtf enabled

    // parse command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            // print help
            return 0;
        case 't': sscanf(optarg, "%u", &size_ht); break;
        case 'f': sscanf(optarg, "%u", &size_bf); break;
        case 'm': mtf_rule = true; break;
        case 's': stats = true; break;
        default:
            // print help
            return 0;
        }
    }
#ifdef __DEBUG__
    fprintf(stderr, "Initializing bf and ht...");
#endif
    BloomFilter *bloom_filter = bf_create(size_bf);
    HashTable *hash_table = ht_create(size_ht, mtf_rule);
#ifdef __DEBUG__
    ht_test(hash_table);
    fprintf(stderr, "done.\n");
    fprintf(stderr, "Reading in badspeak words...");
#endif
    FILE *badspeak_file = fopen("badspeak.txt", "r");
    char badspeak[BUFFER];
    int scanned = 0;
    while ((scanned = fscanf(badspeak_file, "%s", badspeak)) != EOF) {
#ifdef __DEBUG__
        fprintf(stderr, ".%s\n", badspeak);
#endif
        bf_insert(bloom_filter, badspeak);

#ifdef __DEBUG__
        fprintf(stderr, ".");
#endif
        ht_insert(hash_table, badspeak, NULL);

#ifdef __DEBUG__
        fprintf(stderr, ".");
#endif
    }

#ifdef __DEBUG__
    fprintf(stderr, "done.\n");
    fprintf(stderr, "Reading in newspeak words...");
#endif

    FILE *newspeak_file = fopen("newspeak.txt", "r");
    char oldspeak[BUFFER];
    char newspeak[BUFFER];
    scanned = 0;
    while ((scanned = fscanf(newspeak_file, "%s %s", oldspeak, newspeak)) != EOF) {
        bf_insert(bloom_filter, oldspeak);
        ht_insert(hash_table, oldspeak, newspeak);
    }

#ifdef __DEBUG__
    fprintf(stderr, "done.\n");
    fprintf(stderr, "Reading in from stdin...");
#endif
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

        if (bf_probe(bloom_filter, word)) { // check if word is badspeak or oldspeak
            Node *looked_up = ht_lookup(hash_table, word);
            if (looked_up == NULL) {
                // false positive
            } else if (looked_up != NULL) {
                if (looked_up->newspeak == NULL) {
                    // thoughtcrime
                    thoughtcrime = true;
                    ll_insert(badspeak_list, word, NULL);
                } else {
                    rightspeak_counseling = true; // citizen requires counseling on rightspeak
                    ll_insert(oldspeak_list, word, looked_up->newspeak);
                }
            }
        }
    }

#ifdef __DEBUG__
    fprintf(stderr, "done.\n");
    fprintf(stderr, "Printing messages...");
#endif

    if (stats) {
        printf("Seeks: %lu\n", seeks);
        printf("Average seek length: %lf\n", (double) links / seeks);
        printf("Hash table load: %lf%%\n",
            (double) (100.0 * ht_count(hash_table)) / ht_size(hash_table));
        printf("Bloom filter load: %lf%%\n",
            (double) (100.0 * bf_count(bloom_filter)) / bf_size(bloom_filter));
    } else {
        // print verdict messages
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
#ifdef __DEBUG__
    fprintf(stderr, "done.\n");
    fprintf(stderr, "Finializing...");
#endif
    clear_words();
    regfree(&reg_ex);
    ll_delete(&badspeak_list);
    ll_delete(&oldspeak_list);
    ht_delete(&hash_table);
    bf_delete(&bloom_filter);
}
