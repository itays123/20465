/* Symbols.c - dealing with the symbols table and the external words table */
#include "symbols.h"
#include <string.h> /* Temp - remove!! */

static void make_symbol_attr(row_data *, symbol_purpose, int);

input_status add_symbol(table *tab, char *start, char *end, symbol_purpose purpose, int addr)
{
    input_status status;
    boolean key_exists;
    char temp;
    row_data symb_data;
    if ((status = validate_symbol_name(start, end)) != PASS)
        return status;
    
    make_symbol_attr(&symb_data, purpose, addr);

    temp = *end;
    *end = '\0';

    key_exists = !add_item(tab, start, symb_data);

    *end = temp;

    if (key_exists)
        return SYMBOL_ALREADY_DEFINED;
    return PASS;
}

input_status add_extern_symbol(table *tab, char *start, char *end)
{
    input_status status;
    table prev_row, next_row;
    char temp;
    row_data symb_data;
    if ((status = validate_symbol_name(start, end)) != PASS)
        return status;
    
    make_symbol_attr(&symb_data, EXTERN, ADDR_EXTERN);
    
    temp = *end;
    *end = '\0';

    prev_row = find_last_row_before(tab, start);
    if (!prev_row) 
        /* table is null, or symbol comes first, therefore doesn't exist already */
        add_item(tab, start, symb_data);
    else /* There is a symbol beofre. Chect next symbol */
    {
        next_row = prev_row->next;
        if (!next_row || strcmp(next_row->key, start))
            /* Symbol not defined already */
            prev_row->next = new_row(start, symb_data, next_row);
        else {
            /* Symbol is defined, check extern or not */
            if (!((next_row->data).symbol.is_extern))
                return SYMBOL_ALREADY_DEFINED;
            /* Symbol already defined as extern. Do nothing. */
        }
    }

    *end = temp;

    return PASS;
}

int find_symbol_addr(table tab, char *start, char *end)
{
    table target_row;
    char temp = *end;
    *end = '\0';
    
    target_row = find_item(&tab, start);
    *end = temp;

    if (!target_row)
        return ADDR_NOT_FOUND;
    return (target_row->data).symbol.data;
}

input_status mark_entry_symbol(table tab, char *start, char *end)
{
    table target_row;
    char temp = *end;
    *end = '\0';

    target_row = find_item(&tab, start);
    if (!target_row)
        return UNREC_SYMBOL_FOR_ENTRY;
    
    if ((target_row->data).symbol.is_extern)
        return EXTERNAL_ENTRY_SYMBOL;
    
    (target_row->data).symbol.is_entry = TRUE;
    return PASS;
}

void relocate_data_symbols(table tab, int ic)
{
    table current_row = tab;
    int prev_value;
    while (current_row != NULL)
    {
        prev_value = (current_row->data).symbol.data;
        (current_row->data).symbol.data = prev_value + ic;
    }
}

void add_extern_reference_word(table *tab, char *start, char *end, int base_addr)
{
    table prev_row;
    row_data word_data;
    char temp = *end;
    *end = '\0';

    make_symbol_attr(&word_data, EXTERN, base_addr);
    
    prev_row = find_last_row_before(tab, start);
    if (!prev_row) /* Symbol comes first or table is empty */
        add_item(tab, start, word_data);
    else /* Add word */
        prev_row->next = new_row(start, word_data, prev_row->next);
}

