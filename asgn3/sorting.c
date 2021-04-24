// Sorting
// Merilyn Kuo
// CSE 13S Spring 2021

#include "bubble.h"
#include "helper.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>

#define OPTIONS "absqQr:n:p:"

uint32_t seed = 13341453;
uint32_t size = 100;
uint32_t elements = 100;

// Parts of this code was refernced from the text harness example Eugene demoed in his section.

typedef enum sort_types { BUBBLE, SHELL, STACKSORT, QUEUESORT } sort_types;

int main(int argc, char **argv) {
    int opt = 0;
    Set sorts = set_empty();

    void (*sorting_functions[4])(uint32_t*, uint32_t)
        = { bubble_sort, shell_sort, quick_sort_stack, quick_sort_queue };
    char *sort_names[4] = { "Bubble Sort", "Shell Sort", "Quick Sort (Stack)", "Quick Sort (Queue)" };

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
	    sorts = set_insert(sorts, BUBBLE);
	    sorts = set_insert(sorts, SHELL);
	    sorts = set_insert(sorts, STACKSORT);
	    sorts = set_insert(sorts, QUEUESORT);
	    break;
        case 'b':
	    sorts = set_insert(sorts, BUBBLE);
	    break;
        case 's':
	    sorts = set_insert(sorts, SHELL);
	    break;
        case 'q':
	    sorts = set_insert(sorts, STACKSORT);
	    break;
        case 'Q':
	    sorts = set_insert(sorts, QUEUESORT);
	    break;
        case 'r':
	    seed = strtoul(optarg, NULL, 10);
	    break;
        case 'n':
	    size = strtoul(optarg, NULL, 10);
	    break;
        case 'p':
	    elements = strtoul(optarg, NULL, 10);
	    if (elements > size) {
		elements = size;
	    }
	    break;
        default:
	    break;
        }
    }
    printf("%d %d %d \n", seed, size, elements);
    srandom(seed);
    uint32_t *a = (uint32_t *) calloc(size, sizeof(uint32_t));
    for (uint32_t i = 0; i < size; i += 1) {
	a[i] = random();
	// printf("%d\n", a[i]);
    }
    for (int i = 0; i < 4; i += 1) {
	printf("%d\n", i);
	if (set_member(sorts, i)) {
	    printf("argument was entered\n");
	    sorting_functions[i](a, size);
	    printf("i did the sort\n");
	    // print statistics
	    printf("%s\n", sort_names[i]);
	    printf("%d elements, x moves, y compares\n", elements);
	    // print elements
	    for(uint32_t i = 0; i < elements; i += 1) {
		printf("%13" PRIu32, a[i]);
	    }
	    printf("\n");
	}
    }
}
