/* Table.c - deal with dynamic tables */
#include "table.h"
#include "utils.h"
#include "string.h" /* For strcmp */
#include "stdlib.h"

table find_last_row_before(table *tab, char *key)
{
    table curr, prev = NULL;
    
    /* Edge case: empty table or key comes before the key of the head. 
    Return NULL */
    if ((*tab) == NULL || strcmp(key, (*tab)->key) < 0)
        return NULL;


    /* Point curr to the first node with a key coming after the new key */
    curr = *tab;
    while (curr && strcmp(key, (curr->key)) > 0)
    {
        prev = curr;
        curr = curr->next;
    }

    /* Prev is pointing to the desired node */
    return prev;
}

static table new_row(char *key, row_data data, table next);

boolean add_item(table *tab, char *key, row_data data)
{
    table prev, next_node;
    
    /* Edge case: empty table or key comes before the key of the head. 
    Add the new row on the spot */
    if ((*tab) == NULL || strcmp(key, (*tab)->key) < 0)
    {
        *tab = new_row(key, data, tab ? *tab : NULL);
        return TRUE;
    }

    /* Find position to add. Prev is not null since we checked the edge cases before */
    prev = find_last_row_before(tab, key);
    next_node = prev->next;

    /* Check the key of the next node. If equals to this key, do not add and return FALSE */
    if (next_node && !strcmp(key, next_node->key))
        return FALSE;

    /* Add node */
    prev->next = new_row(key, data, next_node);
    return TRUE;
}

table find_item(table *tab, char *key)
{
    table prev, target;
    prev = find_last_row_before(tab, key);

    /* Check: Target node or the one before it are NULL => node not found! */
    if (prev == NULL || prev->next == NULL) 
        return NULL;
    
    target = prev->next;

    /* Compare the key of target and the key given */
    if (!strcmp(target->key, key))
        return target;
    
    return NULL;
}

void free_table(table *tab)
{
    table head, temp;
    if (tab == NULL)
        return;

    head = *tab;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

static table new_row(char *key, row_data data, table next)
{
    table result = (table) malloc_safe(sizeof(table_row));
    result->key = key;
    result->data = data;
    result->next = next;
    return result;
}