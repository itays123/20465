#include "../../assembler/symbols.h"
#include "../../assembler/charsequence.h"

static void print_symbol_row(table);

int main()
{
    input_status status;
    table symbols_table = NULL, current;
    char *label1_end, *label2_end, *label3_end;
    char label1[] = "Hello";
    char label2[] = "Another";
    char label3[] = "Extern";
    label1_end = next_white(label1);
    label2_end = next_white(label2);
    label3_end = next_white(label3);

    status = add_symbol(&symbols_table, label1, label1_end, CODE, 102);
    printf("\nAdded symbol, status = %d", status);
    status = add_symbol(&symbols_table, label2, label2_end, DATA, 37);
    printf("\nAdded symbol, status = %d", status);
    status = add_symbol(&symbols_table, label2, label2_end, DATA, 38);
    printf("\nAttempted adding duplicate symbol, status = %d", status);
    status = add_extern_symbol(&symbols_table, label3, label3_end);
    printf("\nAdded extern symbol, status = %d", status);
    status = add_extern_symbol(&symbols_table, label3, label3_end);
    printf("\nAdded extern symbol again, status = %d", status);
    status = add_symbol(&symbols_table, label3, label3_end, DATA, 38);
    printf("\nAttempted adding duplicate extern symbol, status = %d", status);

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
