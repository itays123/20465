#ifndef _WORD
#define _WORD
#include "globals.h"

typedef enum word_types {
    OPCODE,
    OPDATA,
    DATA
} word_type;

struct opdata_word {
    unsigned int ARE: 3;
    unsigned int type: 2; /* use the word_type enum */
    unsigned int length: 3; /* For OPCODE words, to store their length (1-6, 3 bytes at most) */
    unsigned int funct: 4;
    unsigned int src_reg: 4;
    unsigned int src_adrs: 2;
    unsigned int dest_reg: 4;
    unsigned int dest_adrs: 2;
};

struct integer_word {
    unsigned int ARE: 3;
    unsigned int type: 2; /* use the word_type enum */
    unsigned int length: 3; /* For OPCODE words, to store their length (1-6, 3 bytes at most) */
    unsigned int data: 16;
};

typedef union word_union {
    struct opdata_word opdata;
    struct integer_word integer;
} word;

/******************** Method Definitions **************************/

/* Creates and allocates memory to a new integer word. 
Sets all values to 0, except for data which will be set to the value of op, 
and the type which will be set to OPCODE */
word *new_opcode_word(opcode);

/* Creates and allocates memory to a new opdata word. 
Sets values according to the arguments given 
and the type which will be set to OPDATA */
word *new_opdata_word(funct, reg, addressing_method, reg, addressing_method);

/* Creates and allocates memory to a new integer word. 
Sets all values to 0, except for data which will be set to the value of the argument given, 
and the type which will be set to DATA */
word *new_data_word(int);

/* Creates and allocates two words set to DATA type,
with values of the base and offset of the address given,
and the memory status given in the arguments.
Sets the pointers of the words given to the words created. */
void alloc_address_words(word **, word **, int, memory_status);

/* Checks the type of the word, and fills the hexbit array accordingly. */
void get_bits(hexbits, word *);

/* Goes through each word in the array, according to the count specified by the second argument, 
and frees it from memory */
void free_word_arr(word **, int);

#endif