/* Word.h - dealing with the word structure */
#include "word.h"
#include "utils.h" /* For malloc_safe, get_integer_hexbits */
#include <stdlib.h> /* For free */

/* Allocates a word according to the type given.
ARE will be set to the memory_status given */
static word *new_word(word_type, memory_status);

word *new_opcode_word(opcode op)
{
    word *result = new_word(OPCODE, Absolute);
    (result->integer).data = op;
    return result;
}

word *new_opdata_word(funct ft, reg src_reg, addressing_method src_adrs,
                    reg dest_reg, addressing_method dest_adrs)
{
    word *result = new_word(OPDATA, Absolute);
    (result->opdata).funct = ft;
    (result->opdata).src_reg = src_reg;
    (result->opdata).src_adrs = src_adrs;
    (result->opdata).dest_reg = dest_reg;
    (result->opdata).dest_adrs = dest_adrs;
    return result;
}

word *new_data_word(int data)
{
    word *result = new_word(DATA, Absolute);
    (result->integer).data = data;
    return result;
}

void alloc_address_words(word **base_word, word **offset_word, int address, memory_status ARE)
{
    int base, offset;
    GET_BASE_OFFSET(address, base, offset)
    *base_word = new_word(DATA, ARE);
    ((*base_word)->integer).data = base;
    *offset_word = new_word(DATA, ARE);
    ((*offset_word)->integer).data = offset;
}

void get_bits(hexbits bits, word *source)
{
    opcode op;
    addressing_method src_adrs, dest_adrs;
    reg dest_reg;
    word_type type = (source->integer).type;
    bits[0] = (source->integer).ARE;

    switch (type)
    {
        case OPCODE:
            op = (source->integer).data;
            get_integer_hexbits(bits, 1 << op);
            break;
        
        case DATA:
            get_integer_hexbits(bits, (source->integer).data);
            break;
        
        case OPDATA:
            bits[1] = (source->opdata).funct;
            bits[2] = (source->opdata).src_reg;
            /* The next hexbit is the two bits of src_adrs and the first two of dest_reg */
            src_adrs = (source->opdata).src_adrs;
            dest_reg = (source->opdata).dest_reg;
            bits[3] = (src_adrs << 4 | dest_reg) >> 2;
            /* The next hexbit is the last two bits of dest_reg and the two of dest_adrs */
            dest_adrs = (source->opdata).dest_adrs;
            bits[4] = (dest_reg << 2 | dest_adrs) & HEXBIT_MASK;
            break;
    }
    
}

void free_word_arr(word **words, int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        free(words[i]);
    }
}

static word* new_word(word_type type, memory_status ARE)
{
    word *result = malloc_safe(sizeof(word));
    /* In both structs, type and ARE are in the same location. */
    (result->integer).type = type;
    (result->integer).ARE = ARE;
    return result;
}