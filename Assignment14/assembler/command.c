/* Command.h - dealing with command strings */
#include "command.h"
#include "charsequence.h"
#include <ctype.h>

boolean find_opword(char *label_start_maybe, char *label_end_maybe,
                char **opstart, char **opend)
{
    if (*label_end_maybe == ':')
    {
        *opstart = next_nonwhite(label_end_maybe + 1);
        *opend = next_white(opstart);
        return TRUE;
    }
    
    *opstart = label_start_maybe;
    *opend = label_end_maybe;
    return FALSE;
}

/**
 * A single lookup table element
 */
struct cmd_lookup_element {
	char *cmd;
	opcode op;
	funct fun;
};
/**
 * A lookup table for opcode & funct by command name
 */
static struct cmd_lookup_element lookup_table[] = {
		{"mov", MOV_OP, NONE_FUNCT},
		{"cmp",CMP_OP, NONE_FUNCT},
		{"add",ADD_OP, ADD_FUNCT},
		{"sub",SUB_OP, SUB_FUNCT},
		{"lea",LEA_OP, NONE_FUNCT},
		{"clr",CLR_OP, CLR_FUNCT},
		{"not",NOT_OP, NOT_FUNCT},
		{"inc",INC_OP, INC_FUNCT},
		{"dec",DEC_OP, DEC_FUNCT},
		{"jmp",JMP_OP, JMP_FUNCT},
		{"bne",BNE_OP, BNE_FUNCT},
		{"jsr",JSR_OP, JSR_FUNCT},
		{"red",RED_OP, NONE_FUNCT},
		{"prn",PRN_OP, NONE_FUNCT},
		{"rts",RTS_OP, NONE_FUNCT},
		{"stop",STOP_OP, NONE_FUNCT},
		{"", NONE_OP, NONE_FUNCT}
};

input_status str_to_opcode_funct(char *start, char *end, opcode *op_out, funct *ft_out)
{
    struct cmd_lookup_element *row;
    *op_out = NONE_OP;
    *ft_out = NONE_FUNCT;

    /* Save a lot of worst-case executions by checking length */
    if (end - start < MIN_OPERATION_LENGTH || end - start > MAX_OPERATION_LENGTH)
        return UNREC_OPERATION;

    for (row = lookup_table; *(row->cmd); row++)
        if (str_equal(start, end, row->cmd))
        {
            *op_out = row->op;
            *ft_out = row->fun;
            return PASS;
        }
    
    /* Did not recognize operation */
    return UNREC_OPERATION;
}


input_status find_operand(char **str, char **start, char **end, input_status not_found_status)
{
    /* Point start. Look for errors in input */
    *start = next_nonwhite(*str);
    if (!(**start))
        return not_found_status;
    if ((**start) == ',')
        return MULTIPLE_CONSECUTIVE_COMMAS;
    
    /* Point end and repoint str. Look for errors in input */
    *end = next_white_or_comma(*start);
    *str = next_nonwhite(*end);

    if (!(**str)) /* No non-white chars after end */
        return PASS;
    if ((**str) == ',') /* Str point to comma, point to one character beyond it */
    {
        (*str)++; 
        return PASS;
    }

    /* Found a non-white char before comnma */
    return MISSING_COMMA_BETWEEN_OPERANDS;
    
}

int num_of_operands(opcode op)
{
    /* Opcodes 0-4 - mov, cmp, add, sub, lea - 2 operands. */
    if (op >= MOV_OP && op <= LEA_OP)
        return 2;
    
    /* Opcodes 5-13 - clr, not, inc, dec, jmp, bne
    * jsr, red, prn - 1 operand */
    if (op >= CLR_OP && op <= PRN_OP)
        return 1;
    
    /* Else, no operands */
    return 0;
}

input_status get_operand_data(char *start, char *end, addressing_method *addr_out, reg *reg_out, int *int_out)
{
    char *symb_start, *symb_end, *index_start, *index_end;
    reg temp_reg;
    /* We assume there are no whitespaces in the beginning and end of the substring 
    For immediate addressing, check start is # and validate rest of substring is number. */
    if (*start == '#')
    {
        *addr_out = IMMEDIATE;
        return str_to_int(start + 1, end, int_out) ? PASS : INVALID_NUMBER_FOR_IMMD_ADDRESSING;
    }

    /* Check register direct addressing method */
    if ((temp_reg = str_to_reg(start, end)) != NON_REG)
    {
        *addr_out = REGISTER_DIRECT;
        *reg_out = temp_reg;
        return PASS;
    }

    /* Check index addressing method */
    if (split_symbol_index(start, &symb_start, &symb_end, &index_start, &index_end))
    {
        *addr_out = INDEX;
        if ((temp_reg = str_to_reg(symb_start, symb_end)) == NON_REG || temp_reg < r10)
            return INVALID_REGISTER_FOR_INDEX_ADDRESSING;
        *reg_out = temp_reg;
        if (validate_symbol_name(symb_start, symb_end) != PASS)
            return INVALID_REGISTER_FOR_INDEX_ADDRESSING;
        return PASS;
    }

    /* Direct addressing is remained */
    *addr_out = DIRECT;
    if (validate_symbol_name(start, end) != PASS)
        return INVALID_SYMBOL_REFERENCE;
    return PASS;
}

input_status validate_symbol_name(char *start, char *end)
{
    opcode op; 
    funct ft;
    /* Check length */
    if (end - start > MAX_SYMBOL_LENGTH)
        return TOO_LONG_SYMBOL_NAME;
    
    /* Check starts with letter */
    if (!isalpha(*start))
        return ILLEGAL_CHAR_IN_BEGINNING_OF_SYMBOL;
    
    /* Check contains only digits and letters */
    if (next_non_alnum(start) < end)
        return ILLEGAL_CHARS_IN_SYMBOL_NAME;
    
    /* Check name of register */
    if (str_to_reg(start, end) != NON_REG)
        return SYMBOL_NAMED_LIKE_REGISTER;
    
    /* Check name of operation */
    if (str_to_opcode_funct(start, end, &op, &ft) != UNREC_OPERATION)
        return SYMBOL_NAMED_LIKE_OPERATION;
    
    return PASS;
}

boolean split_symbol_index(char *str, char **symbol_start, char **symbol_end,
                            char **index_start, char **index_end)
{
    /* Got a string in the form of symbol[index] */
    char *next_space;
    *symbol_start = next_nonwhite(str);
    *symbol_end = next('[', *symbol_start);
    next_space = next_white(*symbol_start);

    if (!(**symbol_end) || (next_space < *symbol_end)) /* '[' not found or space before '[' */
        return FALSE;
    
    *index_start = next_nonwhite((*symbol_end) + 1);
    if ((*index_start) != (*symbol_end) + 1) /* Chars between '[' and index */
        return FALSE;
    
    next_space = next_white(*index_start);
    *index_end = next(']', *index_start);

    if (!(**index_end) || (next_space < *index_end)) /* ']' not found or space before ']' */
        return FALSE;
    
    return TRUE;
}

/**
 * A single lookup table element
 */
struct reg_lookup_element {
	char *name;
	reg rg;
};
/**
 * A lookup table for registers by name
 */
static struct reg_lookup_element reg_lookup_table[] = {
		{"r0", r0},
        {"r1", r1},
        {"r2", r2},
        {"r3", r3},
        {"r4", r4},
        {"r5", r5},
        {"r6", r6},
        {"r7", r7},
        {"r8", r8},
        {"r9", r9},
        {"r10", r10},
        {"r11", r11},
        {"r12", r12},
        {"r13", r13},
        {"r14", r14},
        {"r15", r15},
        {"", r0},
};

reg str_to_reg(char *start, char *end)
{
    struct reg_lookup_element *row;

    /* Save a lot of worst-case runs with this check */
    if (end - start != REGISTER_NAME_LENGTH)
        return NON_REG; 

    for (row = lookup_table; *(row->name); row++)
        if (str_equal(start, end, row->name))
        {
            return row->rg;
        }
    
    /* Did not recognize register */
    return NON_REG;
}

input_status check_addressing_methods(opcode op, addressing_method src_addr, addressing_method dest_addr)
{
    /* Validate source address for opcodes 0-4
    For mov, cmp, add: src can be anything */
    if (op == LEA_OP && src_addr != DIRECT && src_addr != INDEX)
        return INVALID_ADRS_METHOD_FIRST_OP;
    
    /* Validate destination address for opcodes 0-4 
    For cmp - dest can be anything*/
    if (op >= MOV_OP && op <= LEA_OP && op != CMP_OP && dest_addr == IMMEDIATE)
        return INVALID_ADRS_METHOD_SECOND_OP;
    
    /* Validate destination address for opcodes 5-13
    For prn - dest can be anything */
    if (op == CLR_OP && dest_addr == IMMEDIATE) /* All opcode 5 group */
        return INVALID_ADRS_METHOD_FIRST_OP;
    
    if (op == JMP_OP && dest_addr != DIRECT && dest_addr != INDEX) /* All opcode 9 group */
        return INVALID_ADRS_METHOD_FIRST_OP;
}

int words_by_addr(addressing_method addr)
{
    if (addr == REGISTER_DIRECT)
        return 0;
    if (addr == IMMEDIATE)
        return 1;
    return 2;
}

input_status end_of_command(char *str)
{
    if (*next_nonwhite(str)) /* If found a non-white char in or after the one str points to */
        return EXTRANEOUS_TEXT;
    return PASS;
}

