#ifndef _SYMBOLS
#define _SYMBOLS
#include "globals.h"
#include "table.h"
#include "command.h" /* For input_status */

#define ADDR_NOT_FOUND -1
#define ADDR_EXTERN 0

/************** Symbol type definitions *************************/

typedef enum symbol_purposes { CODE, DATA, EXTERN } symbol_purpose;

typedef struct symbol_attributes {
    unsigned int is_code: 1;
    unsigned int is_data: 1;
    unsigned int is_extern: 1;
    unsigned int is_entry: 1;
    unsigned int data: 16;
} symbol_attr;

/*************************** Function definitions *****************/

/* Gets a pointer to a table and two pointers to the start and end of a substring (end exclusive),
representing the symbol key, along with the symbol purpose and the symbol data.
Add the symbol to the table if not defined already,
and if symbol name is valid.
Return:
- An error returned by validate_symbol_name (command.c), being:
    - TOO_LONG_SYMBOL_NAME,
    - ILLEGAL_CHAR_IN_BEGINNING_OF_SYMBOL,
    - ILLEGAL_CHARS_IN_SYMBOL_NAME,
    - SYMBOL_NAMED_LIKE_OPERATION,
    - SYMBOL_NAMED_LIKE_REGISTER,
- SYMBOL_ALREADY_DEFINED if symbol is already defined
- PASS otherwise */
input_status add_symbol(table *, char *, char *, symbol_purpose, int);

/* Gets a pointer to a table and two pointers to the start and end of a substring (end exclusive),
representing the symbol key
Add the symbol to the table as external if name is valid.
Allow multiple extern definitions, but if defined already as not extern, do not add.
Return:
- An error returned by validate_symbol_name (command.c), being:
    - TOO_LONG_SYMBOL_NAME,
    - ILLEGAL_CHAR_IN_BEGINNING_OF_SYMBOL,
    - ILLEGAL_CHARS_IN_SYMBOL_NAME,
    - SYMBOL_NAMED_LIKE_OPERATION,
    - SYMBOL_NAMED_LIKE_REGISTER,
- SYMBOL_ALREADY_DEFINED if symbol is already defined as not extern
- PASS otherwise */
input_status add_extern_symbol(table *, char *, char *);

/* Gets a table and the start and end of a symbol key (end exclusive).
Search for the symbol and assign its value (symbol_attr.data) to the pointer given
if not found, return ADDR_NOT_FOUND. If extern, return ADDR_EXTERN. */
int find_symbol_addr(table , char *, char *);

/* Gets a table and the start and end of a symbol key (end exclusive)
Search for the symbol and attempt to mark it as entry
Return:
- UNREC_SYMBOL_FOR_ENTRY if symbol not found
- EXTERNAL_ENTRY_SYMBOL if symbol is marked as external
- PASS otherwise */
input_status mark_entry_symbol(table , char *, char *);

/* Go through each symbol in the table. 
If marked as data, add to their symbol_attr.data the given amount. */
void relocate_data_symbols(table, int);

/************ Extarnal words table - identical method *******/

/* Add a row to the external word table, 
with the key specified and the address specified */
void add_extern_reference_word(table *, char *, char *, int);


#endif