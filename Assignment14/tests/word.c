#include "../assembler/word.h"
#include "../assembler/utils.h"
#include <stdio.h>

static void print_data_word(word *);
static void print_opdata_word(word *);

int main()
{
    word *word_arr[5];
    hexbits bits;
    int i;
    printf("\nSize of word - %ld", sizeof(word));
    word_arr[0] = new_opcode_word(ADD_OP, 5);
    printf("\nnew_opcode_word(ADD_OP):");
    print_data_word(word_arr[0]);
    printf("\nnew_opdata_word(ADD_FUNCT, 0, IMMEDIATE, 6, INDEX):");
    word_arr[1] = new_opdata_word(ADD_FUNCT, 0, IMMEDIATE, 6, INDEX);
    print_opdata_word(word_arr[1]);
    printf("\nnew_data_word(STORABLE(32)):");
    word_arr[2] = new_data_word(STORABLE(32));
    print_data_word(word_arr[2]);
    printf("\nalloc_address_words(33, Relocateable)");
    alloc_address_words(&word_arr[3], &word_arr[4], 33, Relocatable);
    print_data_word(word_arr[3]);
    print_data_word(word_arr[4]);
    
    for(i = 0; i < 5; i++)
    {
        get_bits(bits, word_arr[i]);
        printf("\n%x, %x, %x, %x, %x", bits[0], bits[1], bits[2], bits[3], bits[4]);
    }

    free_word_arr(word_arr, 5);
    return 0;
}

static void print_data_word(word *source)
{
    struct integer_word source_data = source->integer;
    printf("\nWord {");
    printf("\n\tARE: %d,", source_data.ARE);
    printf("\n\ttype: %d,", source_data.type);
    printf("\n\tlength: %d,", source_data.length);
    printf("\n\tdata: %d", source_data.data);
    printf("\n}");
}

static void print_opdata_word(word *source)
{
    struct opdata_word source_data = source->opdata;
    printf("\nWord {");
    printf("\n\tARE: %d,", source_data.ARE);
    printf("\n\ttype: %d,", source_data.type);
    printf("\n\tlength: %d,", source_data.length);
    printf("\n\tfunct: %d,", source_data.funct);
    printf("\n\tsrc_reg: %d,", source_data.src_reg);
    printf("\n\tsrc_adrs: %d,", source_data.src_adrs);
    printf("\n\tdest_reg: %d,", source_data.dest_reg);
    printf("\n\tdest_adrs: %d", source_data.dest_adrs);
    printf("\n}");
}

