#include "globals.h"

/***************** Type definitions *******************/

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

typedef enum {
    NONE = -1,
    IMMEDIATE = 0,
    DIRECT = 1,
    INDEX = 2,
    REGISTER_DIRECT = 3
} addressing_method;

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
    INVALID_REGISTER_FOR_INDEX_ADDRESSING,

    /* Second pass - error in symbol references */
    UNREC_SYMBOL_FOR_ENTRY,
    SYMBOL_NOT_FOUND_FIRST_OP,
    SYMBOL_NOT_FOUND_SECOND_OP,
    EXTERNAL_ENTRY_SYMBOL

} input_status;

/*********************** Module Methods ***********************/

/* Gets a pointer to the start and end of a subtring (end exclusive), and two pointers to pointers of characters.
If the end of the substring is a colon (:), searches the next word after the substring end 
and assigns it to the pointers given.
If not a colon, assigns the start and end of the substring to the two other pointers.
Return TRUE if there was a colon, FALSE otherwise */
boolean find_opword(char *, char *, char **, char **);

/* Gets a pointer to the start and end of a substring,
compares it to given strings and assigns their opcode and funct values to two pointers given.
returns 
- UNREC_OPERATION if operation not found
- PASS otherwise */
input_status str_to_opcode_funct(char *, char *, int *, int *);

/* Gets a pointer to a pointer to somewhere along a string, 
assuming it's after a comma if there should have been one.
Assigns the pointer to the next non-whitespace character (if found) to the second argument,
and the next whitespace or comma after it to the third argument.
Repoints the pointer in the first argument to beyond the next comma if found, or to the end of string if not.
Returns:
- MULTIPLE_CONSECUTIVE_COMMAS, if found a comma before any non-whitespace characters
- MISSING_COMMA_BETWEEN_OPERANDS, if found a non-whitespace characer before a comma in the repointing sequence,
- not found status, the fourth parameter, if not found a non-whitespace parameter 
- PASS, in any other case */
input_status find_operand(char **, char **, char **, input_status );

/* Gets two pointers to the start and end of a substring (end exclusive),
assuming it had no whitespace characters in its start and end.
Find the corresponding addressing method of the substring
*/
input_status find_addressing_method(char *, char *, addressing_method *);

/* Gets a pointer to a string in the form of "symbol[index]"
and four pointer to pointers to characters:
- symbol_start
- symbol_end
- index_start,
- index_end
points symbol_start and symbol_end to the start and end of the symbol char sequence (end exclusive), 
and index_start and index_end to the start and end of the index char sequence (end exclusive).
returns TRUE if everything went fine, FALSE if couldn't find characters from the pattern mentioned above */
boolean split_symbol_index(char *, char **, char **, char **, char **);

/* Gets two pointers to the start and end of a substring (end exclusive)
and returns the register code matching to it "r0" will return 0, etc.
if not found, will return NONE_REG */
reg str_to_reg(char *, char *);

/* Gets a pointer to the first desired whitespace character in a sequence of white chars ending a string, 
and searches for non-whitespace characters after it.
returns:
- EXTRANEOUS_TEXT if found a non-white char or if the pointer given points to a non-whitespace character
- PASS otherwise */
input_status end_of_command(char *);

