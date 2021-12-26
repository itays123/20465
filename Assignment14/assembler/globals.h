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

typedef enum {
    r0,
    r1,
    r2,
    r3,
    r4,
    r5,
    r6,
    r7,
    r8,
    r9,
    r10,
    r11,
    r12,
    r13,
    r14,
    r15,
    NON_REG = -1
} reg;

/**************** WORD TYPE DEFINITONS ***********************/

typedef unsigned int hexbits[BITS_IN_WORD / BITS_IN_HEXBIT];

enum word_type {
    OPWORD,
    OPERANDS,
    DATA
};

enum addressing_method {
    NONE = -1,
    IMMEDIATE = 0,
    DIRECT = 1,
    INDEX = 2,
    REGISTER_DIRECT = 3
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

/***************** Input errors enum*******************/

typedef enum {
    PASS,
    /* Warnings */
    WARN_LABEL_TO_ENTRY,
    WARN_LABEL_TO_EXTERN,

    /* Label name errors */
    TOO_LONG_LABEL_NAME,
    ILLEGAL_CHAR_IN_BEGINNING_OF_LABEL,
    ILLEGAL_CHARS_IN_LABEL_NAME,
    SYMBOL_ALREADY_DEFINED,
    SYMBOL_NAMED_LIKE_OPERATION,
    SYMBOL_NAMED_LIKE_REGISTER,

    /* First pass - structure of line errors */
    LABEL_TO_EMPTY_LINE,
    MULTIPLE_CONSECUTIVE_COMMAS,
    MISSING_COMMA_BETWEEN_OPERANDS,
    EXTRANEOUS_TEXT,
    INVALID_OPERAND_NOT_NUMBER,

    /* First pass - instruction structure */
    UNREC_INSTRUCTION,
    ILLEGAL_COMMA_AFTER_INST,
    STRING_INST_EXPECTS_OPERAND,
    STRING_MUST_BEGIN_WITH_QUOT,
    STRING_MUST_END_WITH_QUOT,
    NO_NUMBERS_FOR_DATA_INST,
    EXPECTED_NUMBER_AFTER_COMMA,

    /* First pass - operation structure */
    UNREC_OPERATION,
    MISSING_OPERAND_REQUIRED_1,
    MISSING_OPERAND_REQUIRED_2,
    TOO_MANY_OPERANDS,
    OPERATION_REQ_NO_OPERANDS,
    INVALID_ADRS_METHOD_FIRST_OP,
    INVALID_ADRS_METHOD_SECOND_OP,

    /* Second pass - error in symbol references */
    UNREC_SYMBOL_FOR_ENTRY,
    SYMBOL_NOT_FOUND_FIRST_OP,
    SYMBOL_NOT_FOUND_SECOND_OP,
    EXTERNAL_ENTRY_SYMBOL

} input_status;