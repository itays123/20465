#include "../../assembler/symbols.h"

static void print_symbol_row(table);

int main()
{
    input_status status;
    table symbols_table = NULL, current;

    status = add_symbol(&symbols_table, "Hello", "", CODE, 102);
    printf("Added symbol, status = %d", status);
    status = add_symbol(&symbols_table, "Another", "", DATA, 37);
    printf("Added symbol, status = %d", status);
    status = add_symbol(&symbols_table, "Hello", "", DATA, 38);
    printf("Attempted adding duplicate symbol, status = %d", status);
    status = add_extern_symbol(&symbols_table, "Extern", "");
    printf("Added extern symbol, status = %d", status);
    status = add_extern_symbol(&symbols_table, "Extern", "");
    printf("Added extern symbol again, status = %d", status);

    current = symbols_table;
    while (current != NULL)
    {
        print_symbol_row(current);
        current = current->next;
    }

    free_table(&symbols_table);
    return 0;
}

static void print_symbol_row(table row)
{
    printf("\nSymbol: {");
    printf("\n\tkey: %s,", row->key);
    printf("\n\tis_code: %d,", (row->data).symbol.is_code);
    printf("\n\tis_data: %d,", (row->data).symbol.is_data);
    printf("\n\tis_extern: %d,", (row->data).symbol.is_extern);
    printf("\n\tis_entry: %d,", (row->data).symbol.is_entry);
    printf("\n\tdata: %d,", (row->data).symbol.data);
    printf("\n}");
}
