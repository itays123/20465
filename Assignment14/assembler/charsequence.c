/* Charsequence.c - working with strings and pointers */
#include <ctype.h>
#include "globals.h" /* For input_status */
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