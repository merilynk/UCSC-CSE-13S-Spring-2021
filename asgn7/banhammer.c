// Merilyn Kuo
// CSE 13S Spring 2021
// Banhammer

#include "node.h"
#include "ll.h"
#include "bf.h"
#include "ht.h"
#include "speck.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>

#define WORD "[a-zA-Z0-9'\-]+"


int main (void) {
    LinkedList *ll = ll_create(true);
    printf("I created list...");
    assert(ll != NULL);
    printf("yes\n");
    ll_insert(ll, "hi", "greetings");
    printf("Length is one...");
    assert(ll_length(ll) == 1);
    printf("yes\n");

    ll_insert(ll, "cya", "good morrow");
    ll_insert(ll, "fun", "enjoyable");
    printf("length is now 3...");
    assert(ll_length(ll) == 3);
    printf("yes.\n");


    printf("List contains hi...");
    assert(ll_lookup(ll, "hi") != NULL);
    printf("yes\n");
    printf("List doesnt contain greetings...");
    assert(ll_lookup(ll, "greetings") == NULL);
    printf("yes\n");
    ll_print(ll);

    printf("deleting ll...");
    ll_delete(&ll);
    assert(ll == NULL);
    printf("done\n");


    HashTable *ht = ht_create(20, true);
    printf("I created a hash table...");
    assert(ht != NULL);
    printf("yes\n");

    printf("the hash table is size 20...");
    assert(ht_size(ht) == 20);
    printf("yes\n");

    ht_insert(ht, "sad", "happy");
    ht_insert(ht, "write", "papertalk");
    ht_insert(ht, "read", "papertalk");

    printf("I inserted 3 linked lists...");
    assert(ht_count(ht) == 3);
    printf("yes\n");

    printf("hi not in ht...");
    assert(ht_lookup(ht, "hi") == NULL);
    printf("yes\n");

    printf("sad is in ht...");
    assert(ht_lookup(ht, "sad") != NULL);
    printf("yes\n");

    ht_print(ht);

    printf("deleting ht...");
    ht_delete(&ht);
    assert(ht == NULL);
    printf("yes\n");

    BloomFilter *bf = bf_create(40);
    printf("I created a bloom filter...");
    assert(bf != NULL);
    printf("yes\n");

    printf("Size is 40...");
    assert(bf_size(bf) == 40);
    printf("yes\n");

    printf("count: %d\n", bf_count(bf));

    printf("insert 1\n");
    bf_insert(bf, "sad");
    printf("count: %d\n", bf_count(bf));

    printf("insert 2nd\n");
    bf_insert(bf, "write");
    printf("count: %d\n", bf_count(bf));

    printf("insert 3rd\n");
    bf_insert(bf, "read");
    printf("count: %d\n", bf_count(bf));

    printf("insert 4th\n");
    bf_insert(bf, "hi");
    printf("count: %d\n", bf_count(bf));


    printf("Sad is in bf...");
    assert(bf_probe(bf, "sad") == true);
    printf("yes\n");

    printf("java is not in bf...");
    assert(bf_probe(bf, "java") == false);
    printf("yes\n");

    printf("count: %d\n", bf_count(bf));

    bf_print(bf);

    printf("deleting bf...");
    bf_delete(&bf);
    assert(bf == NULL);
    printf("yes\n");

}
