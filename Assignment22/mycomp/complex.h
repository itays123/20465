#include <stdio.h>
#include <math.h> /* for power, square root */

typedef struct complex {
    double real, imaginary;
} complex;

complex new_comp();

complex read_comp(double, double);

void print_comp(complex );

complex add_comp(complex, complex);

complex subtract_comp(complex, complex);

complex mult_comp_real(complex, double);

complex mult_comp_img(complex, double);

complex mult_comp_comp(complex, complex);

double comp_abs(complex);