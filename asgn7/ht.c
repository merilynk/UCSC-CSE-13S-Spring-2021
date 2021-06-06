// Merilyn Kuo
// CSE 13S Spring 2021
// Hash Table

#include "ht.h"

#include "ll.h"
#include "node.h"
#include "speck.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Code from assignment pdf
struct HashTable {
    uint64_t salt[2];  // for the hash function
    uint32_t size;  // size of hash table
    bool mtf;  // move to front rule
    LinkedList **lists;  // array of linked lists
};

// Code from assignment pdf
// Constructs a hash table.
HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

// Deconstructs the hash table passed in.
void ht_delete(HashTable **ht) {
    if (*ht && (*ht)->lists) {
        for (uint32_t l = 0; l < (*ht)->size; l++) {
            // loop through hash table to delete ll if it exists
	    if ((*ht)->lists[l]) {
                ll_delete(&((*ht)->lists[l]));
            }
        }
        free((*ht)->lists);
        free(*ht);
        *ht = NULL;
    }
}

// Returns the size of the hash table.
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

// Looks for a node containing the oldspek in the hash table.
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    if (oldspeak == NULL) {
        return NULL;  // make sure oldspeak isn't null
    }
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    // look for linked list at index
    if (!(ht->lists[index])) {
        return NULL;
    } else {
        return ll_lookup(ht->lists[index], oldspeak);
    }
}

// Adds a node containing the oldspeak and newspeak into the hash table at the right index.
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    if (ht->lists[index] == NULL) {
        ht->lists[index] = ll_create(ht->mtf);
    }
    ll_insert(ht->lists[index], oldspeak, newspeak);
    return;
}

// Returns the number of linked lists in the hash table.
uint32_t ht_count(HashTable *ht) {
    int count = 0;
    for (uint32_t l = 0; l < ht->size; l++) {
        if (ht->lists[l]) {
            count++;
        }
    }
    return count;
}

// Prints the hash table.
void ht_print(HashTable *ht) {
    for (uint32_t l = 0; l < ht->size; l++) {
        printf("%d: ", l);
        if (ht->lists[l]) {
            ll_print(ht->lists[l]);
        } else {
            printf("\n");
        }
    }
    return;
}
