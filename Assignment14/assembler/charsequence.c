/* Charsequence.c - working with strings and pointers */
#include <ctype.h>
#include "charsequence.h"

/* Next functions definitions */
#define WHITE(c) ((c) == ' ' || (c) == '\t' || (c) == '\n')
#define NON_WHITE(c) (!(WHITE(c)))
#define WHITE_OR_COMMA(c) (WHITE(c) || (c) == ',')
#define WHITE_OR_COLON(c) (WHITE(c) || (c) == ':')
#define DIGITAL(c) (isdigit(c) || (c) == '+' || (c) == '-')
#define NON_DIGITAL(c) (!DIGITAL(c))
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