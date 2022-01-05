#include "../assembler/table.h"

void print_row(table row);

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
    
    printf("Last row before 'hello': \n");
    print_row(find_last_row_before(&head, "hello"));
    printf("Last row before 'a slightly key before': \n");
    print_row(find_last_row_before(&head, "a slightly key before"));
    printf("Last row before 'third row': \n");
    print_row(find_last_row_before(&head, "third row"));
    printf("Last row before 'not found': \n");
    print_row(find_last_row_before(&head, "not found"));
    
    printf("Searching row: 'hello'\n");
    print_row(find_item(&head, "hello"));
    printf("Searching row: 'a slightly key before'\n");
    print_row(find_item(&head, "a slightly key before"));
    printf("Searching row: 'not found'\n");
    print_row(find_item(&head, "not found"));

    return 0;
}

void print_row(table row)
{
    if (row)
        printf("Row (%s)\n", row->key);
    else
        printf("Nullish Row\n");
}