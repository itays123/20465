#include "globals.h" /* For bool, input_status */

/* Returns a pointer to the next non-white character in a given string
* or to the end of the string if not found */
char *next_nonwhite(char *);

/* Returns a pointer to the next white character in a given string
* or to the end of string if not found */
char *next_white(char *);

/* Returns a pointer to the next white character or comma in a given string
* or to the end of string if not found */
char *next_white_or_comma(char *);

/* Returns a pointer to the next white character or colon in a given string
or to the end of string if not found */
char *next_white_or_colon(char *);

/* Returns a pointer to the next character that is not a digit
or to the end of string if not found */
char *next_non_digital(char *);

/* Returns a pointer to the next character that is not a digit or a letter
or to the end of string if not found */
char *next_non_alnum(char *);

/* Returns a pointer to the next character in a given string that is equal to a given character,
ot to the end of string if not found  */
char *next(char, char *);

/* Gets a pointer to the start of a substring, and a pointer to the end of it(end exclusive), 
and compares it with a given string.
Return true if equal, false otherwise */
boolean str_equal(char *, char *, char *);

/* Gets a pointer to the start of a substring, and a pointer to the end of it (end exclusive),
and parses it to an integer if a valid integer (optional sign + decimal digits)
assigns the result to the pointer given to it.
Returns an input status PASS or INVALID_OPERAND_NOT_A_NUMBER */
input_status str_to_int(char *, char *, int *);

/* Gets a pointer to the start and end of a subtring (end exclusive), and two pointers to pointers of characters.
If the end of the substring is a colon (:), searches the next word after the substring end 
and assigns it to the pointers given.
If not a colon, assigns the start and end of the substring to the two other pointers.
Return TRUE if there was a colon, FALSE otherwise */
boolean find_opword(char *, char *, char **, char **);

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

/* Gets a pointer to a string in the form of "symbol[index]"
and four pointer to pointers to characters:
- symbol_start
- symbol_end
- index_start,
- index_end
points symbol_start and symbol_end to the start and end of the symbol char sequence (end exclusive), 
and index_start and index_end to the start and end of the index char sequence (end exclusive).
returns TRUE if everything went fine, FLASE if couldn't find characters from the pattern mentioned above */
boolean split_symbol_index(char *str, char **symbol_start, char **symbol_end,
                            char **index_start, char **index_end);

/* Gets a pointer to the first desired whitespace character in a sequence of white chars ending a string, 
and searches for non-whitespace characters after it.
returns:
- EXTRANEOUS_TEXT if found a non-white char or if the pointer given points to a non-whitespace character
- PASS otherwise */
input_status end_of_command(char *str);

