#include <stdio.h>
#include <unistd.h>
#include "mathlib.h"

#define OPTIONS "asctl"

static void printTableHeader(char name[]) {
    printf("  x          %s          Library        Difference \n", name);
    printf("-----        --------    -------        ---------- \n");
}

int main(int argc, char **argv) {
    int opt = 0, arcsin = 0, arccos = 0, arctan = 0, log = 0;

    while (opt = getopt(argc, argv, OPTIONS) != -1) {
	switch(opt) {
	    case 'a':
		arcsin = 1;
		arccos = 1;
		arctan = 1;
		log = 1;
	    case 's':
		arcsin = 1;
	    case 'c':
		arccos = 1;
	    case 't':
		arctan = 1;
	    case 'l':
		log = 1;
	    default:
		return 1;
	}

    }
}
