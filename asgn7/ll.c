// Merilyn Kuo
// CSE 13S Spring 2021
// linked list

#include "ll.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Struct definition from assignment pdf
struct LinkedList {
    uint32_t length;  // num nodes in list
    Node *head;  // head sentinel node
    Node *tail;  // tail sentinel node
    bool mtf;  // move-to-front
};

LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) calloc(1, sizeof(LinkedList));
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

void ll_delete(LinkedList **ll) {
    if (*ll) {
	for (Node *node = (*ll)->head; node != (*ll)->tail; node = node->next) {
	    node_delete(&node);
	}
	node_delete(&((*ll)->tail));
	*ll = NULL;
    }
    return;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    for (Node *node = ll->head->next; node != ll->tail; node = node->next) {
	if (strcmp(node->oldspeak, oldspeak) == 0) {
	    if (ll->mtf) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		node->next = ll->head->next;
		ll->head->next->prev = node;
		ll->head->next = node;
		node->prev = ll->head;
	    }
	    return node;
	}
    }
    Node *node = NULL;
    return node;
}

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

void ll_print(LinkedList *ll) {
    for (Node *node = ll->head->next; node != ll->tail; node = node->next) {
	node_print(node);
    }
    printf("Length: %u\n", ll->length);
}
