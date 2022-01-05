#ifndef _MACRO
#define _MACRO
#include "globals.h"
#include <stdio.h>

/********************** Macro table type definitions *********************/

typedef struct macro_attributes {
    unsigned int lines;
    fpos_t *position;
} macro_attr;

#endif