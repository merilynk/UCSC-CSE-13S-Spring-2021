#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "asctl"

// Setup of code is based on Sahiti's code from her section.

//
// Prints the header of the table.
//
//name[]: string, name of function
//
static void printTableHeader(char name[]) {
    printf("  x            %s           Library        Difference \n", name);
    printf("  -            ------           -------        ---------- \n");
}

int main(int argc, char **argv) {
    int opt = 0;
    int arcsin = 0, arccos = 0, arctan = 0, ln = 0; // 0 means don't print output, 1 means print
    int arg_exists = 0; // remains 0 if no arguments entered, 1 if any # args entered

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            arcsin = 1;
            arccos = 1;
            arctan = 1;
            ln = 1;
            arg_exists = 1; // User entered an argument.
            break;
        case 's':
            arcsin = 1;
            arg_exists = 1;
            break;
        case 'c':
            arccos = 1;
            arg_exists = 1;
            break;
        case 't':
            arctan = 1;
            arg_exists = 1;
            break;
        case 'l':
            ln = 1;
            arg_exists = 1;
            break;
        default:
            // if incorrect arguments were entered
            arg_exists = 1;
            printf("Program usage: ./mathlib-test -[asctl]\n  -a   Runs all tests (arcsin, arccos, "
                   "arctan, log)\n  -s   Runs arcsin tests\n  -c   Runs arccos tests\n  -t   Runs "
                   "arctan "
                   "tests\n  -l   Runs log tests\n");
            break;
        }
    }

    // Print outputs based on cases.

    if (arg_exists == 0) { // User did not enter any arguments.
        printf(
            "Program usage: ./mathlib-test -[asctl]\n  -a   Runs all tests (arcsin, arccos, "
            "arctan, log)\n  -s   Runs arcsin tests\n  -c   Runs arccos tests\n  -t   Runs arctan "
            "tests\n  -l   Runs log tests\n");
    }

    if (arcsin == 1) {
        printTableHeader("arcSin");
        for (double i = -1; i <= 1; i += 0.1) {
            printf(
                " %7.4lf %16.8lf % 16.8lf % 16.10lf\n", i, arcSin(i), asin(i), arcSin(i) - asin(i));
        }
    }

    if (arccos == 1) {
        printTableHeader("arcCos");
        for (double i = -1; i <= 1; i += 0.1) {
            printf(
                " %7.4lf %16.8lf % 16.8lf % 16.10lf\n", i, arcCos(i), acos(i), arcCos(i) - acos(i));
        }
    }

    if (arctan == 1) {
        printTableHeader("arcTan");
        for (double i = 1; i <= 10; i += 0.1) {
            printf(
                " %7.4lf %16.8lf % 16.8lf % 16.10lf\n", i, arcTan(i), atan(i), arcTan(i) - atan(i));
        }
    }

    if (ln == 1) {
        printTableHeader("Log   ");
        for (double i = 1; i <= 10; i += 0.1) {
            printf(" %7.4lf %16.8lf % 16.8lf % 16.10lf\n", i, Log(i), log(i), Log(i) - log(i));
        }
    }
}
