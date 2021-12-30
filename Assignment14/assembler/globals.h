#ifndef _GLOBALS
#define _GLOBALS

/* Global Type Definitions */
#define IC_INIT_VALUE 100
#define MAX_LINE_LENGTH 82 /* 80 chars + \n + \0 */
#define BITS_IN_WORD 20
#define BITS_IN_HEXBIT 4
#define HEXBITS_IN_WORD BITS_IN_WORD / BITS_IN_HEXBIT
#define MAX_CODE_IMAGE_SIZE 8192 /* Assumption - change if needed */
#define ASSEMBLY_POSTFIX ".as"
#define ASSEMBLY_POST_MACRO_POSTFIX ".am"
#define ENTRY_POSTFIX ".ent"
#define EXTERN_POSTFIX ".ext"
#define OBJECT_POSTFIX ".ob"

typedef enum { FALSE = 0, TRUE = 1 } boolean;

/**************** WORD TYPE DEFINITONS ***********************/

typedef unsigned int hexbits[HEXBITS_IN_WORD];

enum word_type {
    OPWORD,
    OPERANDS,
    DATA
};

typedef enum opcodes {
	MOV_OP = 0,
	CMP_OP = 1,

	ADD_OP = 2,
	SUB_OP = 2,

	LEA_OP = 4,

	CLR_OP = 5,
	NOT_OP = 5,
	INC_OP = 5,
	DEC_OP = 5,

	JMP_OP = 9,
	BNE_OP = 9,
	JSR_OP = 9,

	RED_OP = 12,
	PRN_OP = 13,

	RTS_OP = 14,
	STOP_OP = 15,

	NONE_OP = -1
} opcode;

typedef enum functs {
    /* Opcode 2 */
    ADD_FUNCT = 10,
    SUB_FUNCT = 11,

    /* Opcode 5 */
    CLR_FUNCT = 10,
    NOT_FUNCT = 11,
    INC_FUNCT = 12,
    DEC_FUNCT = 13,

    /* Opcode 9 */
    JMP_FUNCT = 10,
    BNE_FUNCT = 11,
    JSR_FUNCT = 12,

    NONE_FUNCT = -1
} funct;

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

#endif