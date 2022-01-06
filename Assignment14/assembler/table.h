#ifndef _TABLE
#define _TABLE
#include "globals.h"
#include "symbols.h"
#include "macro.h"

/***** Table type definition ********/

typedef union row_data_union {
    symbol_attr symbol;
    macro_attr macro;
} row_data;

typedef struct row *table;
typedef struct row {
    char *key;
    table next;
    row_data data;
} table_row;

/******** Function definitions ********/

/* Return pointer to a row with the last key that comes before the given key alphabetically,
or NULL if table is NULL or if given key is alphabetically before the key of the head */
table find_last_row_before(table *, char *);

/* Adds a new item to the table, or create a new table with the item if needed.
Add it in the corresponding spot alphabetically (sort by key) to save time when searching for the element.
Return TRUE if a row with the key specified didn't exist already, FALSE otherwise */
boolean add_item(table *, char *, row_data);

/* Return a pointer to a row with a given key in a given table,
NULL if not found */
table find_item(table *, char *);

/* Free every row in the table. */
void free_table(table *);

/* Create a new row in the table. Give it (a copy of) the key given,
the row data given and a pointer to the next row given 
Return pointer to new row */
table new_row(char *key, row_data data, table next);

#endif