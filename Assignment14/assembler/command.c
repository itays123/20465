/* Command.h - dealing with command strings */
#include "command.h"
#include "charsequence.h"

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

input_status end_of_command(char *str)
{
    if (*next_nonwhite(str)) /* If found a non-white char in or after the one str points to */
        return EXTRANEOUS_TEXT;
    return PASS;
}

