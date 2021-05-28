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
    printf("List contains hi...");
    assert(ll_lookup(ll, "hi") != NULL);
    printf("yes\n");
    printf("List doesnt contain greetings...");
    assert(ll_lookup(ll, "greetings") == NULL);
    printf("yes\n");

}
