#include "mathlib.h"

#include <math.h>
#include <stdio.h>

#define EPSILON 1e-10

static double AbsVal(double x) {
    if (x < 0) {
        x = x * -1;
    }
    return x;
}

// The code for this function is from sqrt.c posted by Prof Long on Piazza.
static double Sqrt(double x) {
    double y = 1.0;
    for (double guess = 0.0; AbsVal(y - guess) > EPSILON; y = (y + x / y) / 2.0) {
        guess = y;
    }
    return y;
}

// The code for this function is from exp.c posted by Prof. Long on Piazza.
static double Exp(double x) {
    double term = 1, sum = 1;
    for (int k = 1; AbsVal(term) > EPSILON; k += 1) {
        term *= x / k;
        sum += term;
    }
    return sum;
}

double arcSin(double x) {
    double yk = 0, yk_1 = x;
    while (AbsVal(yk_1 - yk) > EPSILON) {
        yk = yk_1; // set last value to new guess
        yk_1 = yk - (sin(yk) - x) / cos(yk);
    }
    return yk_1;
}

double arcCos(double x) {
    return M_PI_2 - arcSin(x);
}

double arcTan(double x) {
    return arcSin(x / Sqrt((x * x) + 1));
}

double Log(double x) {
    double yk = 0, yk_1 = 1;
    while (AbsVal(yk_1 - yk) > EPSILON) {
        yk = yk_1;
        yk_1 = yk + (x - Exp(yk)) / Exp(yk);
    }
    return yk_1;
}
