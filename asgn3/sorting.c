// Sorting
// Merilyn Kuo
// CSE 13S Spring 2021

#include "bubble.h"
#include "helper.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "absqQr:n:p:"

uint32_t seed = 13371453;
uint32_t size = 100;
uint32_t elements = 100;

// Parts of this code was refernced from the text harness example Eugene demoed in his section.

// Enumerating sort types. BUBBLE = 0 ... QUEUESORT = 3
typedef enum sort_types { BUBBLE, SHELL, STACKSORT, QUEUESORT } sort_types;

int main(int argc, char **argv) {

    int opt = 0;
    int args_entered = 0; // Remains 0 if no arguments entered in command line

    Set sorts = set_empty(); // create an empty set

    // Array of sorting functions
    void (*sorting_functions[4])(uint32_t *, uint32_t)
        = { bubble_sort, shell_sort, quick_sort_stack, quick_sort_queue };

    // Array of names of sorts.
    char *sort_names[4]
        = { "Bubble Sort", "Shell Sort", "Quick Sort (Stack)", "Quick Sort (Queue)" };

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) { // loops through command line options

        switch (opt) {
        case 'a':
            sorts = set_insert(sorts, BUBBLE);
            sorts = set_insert(sorts, SHELL);
            sorts = set_insert(sorts, STACKSORT);
            sorts = set_insert(sorts, QUEUESORT);
            args_entered = 1;
            break;

        case 'b':
            sorts = set_insert(sorts, BUBBLE);
            args_entered = 1;
            break;

        case 's':
            sorts = set_insert(sorts, SHELL);
            args_entered = 1;
            break;

        case 'q':
            sorts = set_insert(sorts, STACKSORT);
            args_entered = 1;
            break;

        case 'Q':
            sorts = set_insert(sorts, QUEUESORT);
            args_entered = 1;
            break;

        case 'r': seed = strtoul(optarg, NULL, 10); break;

        case 'n': size = strtoul(optarg, NULL, 10); break;

        case 'p':
            elements = strtoul(optarg, NULL, 10);
            if (elements > size) {
                elements = size; // check if elements > size, if so elements = size
            }
            break;

        default:
            args_entered = 1;

            // error message
            printf("Select at least one sort to perform.\n"
                   "SYNOPSIS\n"
                   "   A collection of comparison-based sorting algorithms.\n\n"
                   "USAGE\n"
                   "   ./sorting [-absqQ] [-r seed] [-n length] [-p elements]\n\n"
                   "OPTIONS\n"
                   "   -a              Enable all sorts.\n"
                   "   -b              Enable Bubble Sort.\n"
                   "   -s              Enable Shell Sort.\n"
                   "   -q              Enable Quick Sort (Stack).\n"
                   "   -Q              Enable Quick Sort (Queue).\n"
                   "   -r seed         Specify random seed\n"
                   "   -n length       Specify number of array elements.\n"
                   "   -p elements     Specify number of elements to print.\n");
            break;
        }
    }

    // If no arguments were entered in command line, print message.
    if (args_entered == 0) {
        printf("Select at least one sort to perform.\n"
               "SYNOPSIS\n"
               "   A collection of comparison-based sorting algorithms.\n\n"
               "USAGE\n"
               "   ./sorting [-absqQ] [-r seed] [-n length] [-p elements]\n\n"
               "OPTIONS\n"
               "   -a              Enable all sorts.\n"
               "   -b              Enable Bubble Sort.\n"
               "   -s              Enable Shell Sort.\n"
               "   -q              Enable Quick Sort (Stack).\n"
               "   -Q              Enable Quick Sort (Queue).\n"
               "   -r seed         Specify random seed\n"
               "   -n length       Specify number of array elements.\n"
               "   -p elements     Specify number of elements to print.\n");
    }

    // the code below is all my own

    if (elements > size) {
        elements = size; // make sure elements isn't greater than size
    }

    uint32_t a[size]; // create array with random elements
    srandom(seed);
    for (uint32_t i = 0; i < size; i += 1) {
        a[i] = random();
    }

    //printf("%d %d %d", seed, size, elements);

    // check for outputs to print
    for (int i = 0; i < 4; i += 1) {

        uint32_t a_sort[size]; // duplicate of a[] to sort

        if (set_member(sorts, i)) {

            for (uint32_t i = 0; i < size; i += 1) {
                a_sort[i] = a[i]; // copying a[]
                //printf(" %d", a_sort[i]);
            }

            sorting_functions[i](a_sort, size); // call sorting functions

            // print statistics
            printf("%s\n", sort_names[i]);
            printf("%d elements, %d moves, %d compares", elements, moves, compares);
            if (i == 2 || i == 3) { // print if it is a quick sort function
                printf("\nMax stack size: %d", max_size);
            }

            //if (i == 0) {
            //printf("\nTime Complexity: %d", n);
            //}
            //
            // print sorted elements
            for (uint32_t i = 0; i < elements; i += 1) {
                if (i % 5 == 0) {
                    printf("\n");
                }
                printf("%13" PRIu32, a_sort[i]);
            }
            printf("\n");
        }
    }
}
