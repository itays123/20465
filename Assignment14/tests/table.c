#include "../assembler/table.h"

void print_row(table_row row);

int main()
{
    table head = NULL;
    row_data default_row_data;
    default_row_data.symbol.is_code = 0; 
    default_row_data.symbol.is_data = 0; 
    default_row_data.symbol.is_entry = 0; 
    default_row_data.symbol.is_extern = 0; 
    default_row_data.symbol.data = 0; 
    printf("Adding row - ('hello', {0,0,0,0,0}): %d\n", add_item(&head, "hello", default_row_data));
    printf("Adding row - ('a slightly key before', {0,0,0,0,0}): %d\n", add_item(&head, "a slightly key before", default_row_data));
    printf("Adding row - ('third row', {0,0,0,0,0}): %d\n", add_item(&head, "third row", default_row_data));
    printf("Adding row - ('hello', {0,0,0,0,0}): %d\n", add_item(&head, "hello", default_row_data));
    

    return 0;
}