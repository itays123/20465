#ifndef _SYMBOLS
#define _SYMBOLS
#include "globals.h"

/************** SYmbol type definitions *************************/

typedef enum symbol_purposes { CODE, DATA, EXTERN } symbol_purpose;

typedef struct symbol_attributes {
    unsigned int is_code: 1;
    unsigned int is_data: 1;
    unsigned int is_extern: 1;
    unsigned int is_entry: 1;
    unsigned int data: 16;
} symbol_attr;

#endif