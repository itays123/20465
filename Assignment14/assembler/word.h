
enum word_type {
    OPWORD,
    OPERANDS,
    DATA
};

struct opdata_word {
    unsigned int ARE: 3;
    unsigned int type: 2; /* use the word_type enum */
    unsigned int length: 3; /* For OPWORD words, to store their length (1-6, 3 bytes at most) */
    unsigned int funct: 4;
    unsigned int src_reg: 4;
    unsigned int src_adrs: 2;
    unsigned int dest_reg: 4;
    unsigned int dest_adrs: 2;
};

struct integer_word {
    unsigned int ARE: 3;
    unsigned int type: 2; /* use the word_type enum */
    unsigned int length: 3; /* For OPWORD words, to store their length (1-6, 3 bytes at most) */
    unsigned int data: 16;
};

typedef union word_union {
    struct opdata_word opdata;
    struct integer_word integer;
} word;