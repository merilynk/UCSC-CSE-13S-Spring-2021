// Merilyn Kuo
// CSE 13S Spring 2021
// linked list

#include "ll.h"

#include "node.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct definition from assignment pdf
struct LinkedList {
    uint32_t length;  // num nodes in list
    Node *head;  // head sentinel node
    Node *tail;  // tail sentinel node
    bool mtf;  // move-to-front
};

uint64_t seeks = 0;
uint64_t links = 0;

// Constructs a linked list.
LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) calloc(1, sizeof(LinkedList));
    assert(ll != NULL);
    if (ll) {
        ll->length = 0;
        ll->head = node_create("head", NULL);
        ll->tail = node_create("tail", NULL);
        ll->head->next = ll->tail;
        ll->tail->prev = ll->head;
        ll->mtf = mtf;
    }
    return ll;
}

// Destructs the linked list passed in.
void ll_delete(LinkedList **ll) {
    if (*ll) {
        for (Node *node = (*ll)->head->next; node != NULL; node = node->next) {
            node_delete(&(node->prev));
        }
        node_delete(&((*ll)->tail));
        free(*ll);
        *ll = NULL;
    }
    return;
}

// Returns the length of the linked list.
uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

// Looks for a node containing the oldspeak in the linked list.
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    seeks++;
    for (Node *node = ll->head->next; node != ll->tail; node = node->next, links++) {
        if (strcmp(node->oldspeak, oldspeak) == 0) {
	    // a node was found
            if (ll->mtf) {
                node->prev->next = node->next;
                node->next->prev = node->prev;
                node->next = ll->head->next;
                node->prev = ll->head;
                ll->head->next->prev = node;
                ll->head->next = node;
            }
            return node;
        }
    }
    return NULL;  // node was not found
}

// Inserts a node containing the oldspeak and newspeak into the linked list.
void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (ll_lookup(ll, oldspeak) == NULL) {
        Node *new = node_create(oldspeak, newspeak);
        new->next = ll->head->next;
        new->prev = ll->head;
        ll->head->next->prev = new;
        ll->head->next = new;
        ll->length += 1;
    }
    return;
}

// Prints all the nodes in the linked list.
void ll_print(LinkedList *ll) {
    for (Node *node = ll->head->next; node != ll->tail; node = node->next) {
        node_print(node);
    }
}
