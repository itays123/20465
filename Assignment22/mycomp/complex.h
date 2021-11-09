

typedef struct complex {
    double real, imaginary;
} complex;

complex* new_comp();

void read_comp(complex*, double, double);

void print_comp(complex* );

void add_comp(complex*, complex*);

void subtract_comp(complex*, complex*);

void mult_comp_real(complex*, double);

void mult_comp_img(complex*, double);

void mult_comp_comp(complex*, complex*);

void abs_comp(complex*);