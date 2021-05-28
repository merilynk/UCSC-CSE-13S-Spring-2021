// Merilyn Kuo
// CSE 13S Sprint 2021
// node.c

#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char *str_dup(char *og_str) {
    int c = 0;
    int str_len = 0;
    while (og_str[c] != '\0') {
	str_len += 1;
	c ++;
    }
    str_len += 1;
    char *dup_str = (char *) malloc (str_len);
    for (c = 0; c < str_len; c++) {
	dup_str[c] = og_str[c];
    }
    return dup_str;
}

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    if (n) {
	n->oldspeak = oldspeak ? str_dup(oldspeak) : NULL;
	n->newspeak = newspeak ? str_dup(newspeak) : NULL;
    }
    return n;
}

void node_delete(Node **n) {
    if (*n) {
	free((*n)->oldspeak);
	free((*n)->newspeak);
	free(*n);
	*n = NULL;
    }
    return;
}

void node_print(Node *n) {
    if (n->oldspeak && n->newspeak) {
	printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
    else if (n->newspeak == NULL) {
	printf("%s\n", n->oldspeak);  // node only contains oldspeak
    }
    return;
}

