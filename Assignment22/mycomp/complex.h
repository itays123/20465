#include <stdio.h>
#include <math.h> /* for power, square root */

typedef struct complex {
    double real, imaginary;
} complex;

complex new_comp();

complex read_comp(double, double);

void print_comp(complex );

void add_comp(complex, complex);

void subtract_comp(complex, complex);

void mult_comp_real(complex, double);

void mult_comp_img(complex, double);

void mult_comp_comp(complex, complex);

void abs_comp(complex);