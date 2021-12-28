/* Global Type Definitions */
#define IC_INIT_VALUE 100
#define MAX_LINE_LENGTH 82 /* 80 chars + \n + \0 */
#define BITS_IN_WORD 20
#define BITS_IN_HEXBIT 4
#define MAX_CODE_IMAGE_SIZE 8192 /* Assumption - change if needed */
#define ASSEMBLY_POSTFIX ".as"
#define ASSEMBLY_POST_MACRO_POSTFIX ".am"
#define ENTRY_POSTFIX ".ent"
#define EXTERN_POSTFIX ".ext"
#define OBJECT_POSTFIX ".ob"

typedef enum { FALSE = 0, TRUE = 1 } boolean;

/**************** WORD TYPE DEFINITONS ***********************/

typedef unsigned int hexbits[BITS_IN_WORD / BITS_IN_HEXBIT];

enum word_type {
    OPWORD,
    OPERANDS,
    DATA
};

enum ARE {
    Absolute = 4, /* 100 */
    Relocatable = 2, /* 010 */
    Extern = 1 /* 001 */
};

typedef struct {
    unsigned int funct: 4;
    unsigned int src_reg: 4;
    unsigned int src_adrs: 2;
    unsigned int dest_reg: 4;
    unsigned int dest_adrs: 2;
} operand_data;

typedef struct {
    unsigned int ARE: 3;
    unsigned int length: 3; /* For OPWORD words, to store their length (1-6, 3 bytes at most) */
    unsigned int type: 2; /* use the word_type enum */
    union data {
        operand_data opdata;
        int integer_data;
    } data; /* Occupies sizeof(int) bytes */
} word;

