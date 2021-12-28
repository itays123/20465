/* Charsequence.c - working with strings and pointers */
#include <ctype.h> /* For isalnum, isdigit */
#include <string.h> /* For strcmp */
#include <stdlib.h> /* For atoi */
#include "charsequence.h"

/******** NEXT FUNCTIONS DEFINITIONS */
#define WHITE(c) ((c) == ' ' || (c) == '\t' || (c) == '\n')
#define NON_WHITE(c) (!(WHITE(c)))
#define WHITE_OR_COMMA(c) (WHITE(c) || (c) == ',')
#define WHITE_OR_COLON(c) (WHITE(c) || (c) == ':')
#define NON_DIGITAL(c) (!isdigit(c))
#define NON_ALNUM(c) (!isalnum(c))

#define DEFINE_NEXT_FUNCTION(func_name, filter) \
char *func_name(char *str)\
{\
    char *p;\
    for (p = str; *p && !filter(*p); p++);\
    return p;\
}

DEFINE_NEXT_FUNCTION(next_white, WHITE)
DEFINE_NEXT_FUNCTION(next_nonwhite, NON_WHITE)
DEFINE_NEXT_FUNCTION(next_white_or_comma, WHITE_OR_COMMA)
DEFINE_NEXT_FUNCTION(next_white_or_colon, WHITE_OR_COLON)
DEFINE_NEXT_FUNCTION(next_non_digital, NON_DIGITAL)
DEFINE_NEXT_FUNCTION(next_non_alnum, NON_ALNUM)

char *next(char target, char *str)
{
    char *p;
    for (p = str; *p && *p != target; p++);
    return p;
}

/********* STRING UTILITIES FUNCTIONS ****************/

boolean str_equal(char *start, char *end, char *compare_to)
{
    int result;
    char temp = *end;
    *end = '\0';
    result = strcmp(start, compare_to);
    *end = temp;
    return result ? TRUE : FALSE;
}

input_status str_to_int(char *start, char *end, int *to_assign)
{
    char temp = *end;
    
    /* Validate numeric string */
    if ((!isdigit(*start) && *start != '-' && *start != '+') /* start can point to a sign */
        || next_non_digital(start + 1) != end) /* rest of chars in substring must be digits */
        return INVALID_OPERAND_NOT_NUMBER;
    
    *end = '\0';
    *to_assign = atoi(start);
    *end = temp;
    return PASS;
}

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

